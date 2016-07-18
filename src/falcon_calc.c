//
// Created by James Stumme on 7/8/16.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "falcon_calc.h"

typedef union {
    roman original;
    unsigned int merged;
} roman_convert;
unsigned int mask_numerals[] = {0b01111000000000000000, 0b00000100000000000000,
                                0b00000011110000000000, 0b00000000001000000000,
                                0b00000000000111100000, 0b00000000000000010000,
                                0b00000000000000001111};
int mask_len = 7;
size_t longest_numeral = 20;

void shift_add(unsigned int *, unsigned int *, unsigned int *, unsigned int, unsigned int);
unsigned int borrow(int, roman_convert *, roman_convert *);
int parse_numeral(char, roman *);
int parse_numeral_lookahead(char, char, roman *);
void shift_numeral(roman *);

roman *ator(char *str) {
    roman *r = calloc(1, sizeof(roman));

    size_t length = strnlen(str, longest_numeral);
    for (int i = 0; i < length; i++) {
        i += parse_numeral_lookahead(str[i], str[i + 1], r);
    }

    return r;
}

roman *add(roman *left, roman *right) {
    roman_convert _right;
    roman_convert *sum = malloc(sizeof(roman_convert));
    unsigned int sum_l, sum_r, carry;
    sum->original = *left;
    _right.original = *right;
    carry = 0;

    for (int current = mask_len - 1; current >= 0; current--) {
        int next = current - 1;

        unsigned int current_mask = mask_numerals[current];
        unsigned int comp_mask = (current)
                                 ? mask_numerals[next] | current_mask
                                 : current_mask;

        sum_l = sum->merged & current_mask;
        sum_r = _right.merged & current_mask;

        shift_add(&sum_l, &carry, &carry, current_mask, comp_mask);
        shift_add(&sum_l, &sum_r, &carry, current_mask, comp_mask);

        sum->merged = (sum->merged & ~current_mask) | (sum_l & current_mask);
    }

    return &sum->original;
}

void shift_add(unsigned int *x, unsigned int *y, unsigned int *c, unsigned int cur_mask, unsigned int comp_mask) {
    while ((*y & cur_mask) > 0) {
        unsigned int before = *x;

        *y &= (*y >> 1) & cur_mask;
        *x |= ((*x | ~comp_mask) << 1 | 1) & comp_mask;

        if (before == (*x & cur_mask)) {
            *x &= ~cur_mask;
            *c = *x;
        }
    }
}

roman *subtract(roman *left, roman *right) {
    roman_convert _left, _right;
    roman_convert *diff = malloc(sizeof(roman_convert));
    roman_convert diff_l, diff_r;

    _left.original = *left;
    _right.original = *right;
    diff->merged = 0;

    diff->merged = _left.merged ^ _right.merged;
    diff_l.merged = _left.merged & diff->merged;
    diff_r.merged = _right.merged & diff->merged;

    shift_numeral(&diff->original);
    shift_numeral(&diff_l.original);
    shift_numeral(&diff_r.original);

    unsigned int mask = 0x0;
    for (int current = mask_len - 1; current > 0; current--) {
        unsigned int current_mask = mask_numerals[current];
        if ((diff_r.merged & current_mask) > (diff_l.merged & current_mask)) {
            mask = borrow(current, &diff_l, &diff_r);
            diff_l.merged |= mask;
            diff_r.merged &= (diff_r.merged & mask_numerals[current]) >> 1 | ~mask_numerals[current];
        }
    }
    if (mask > 0x0) {
        diff->merged = diff_l.merged ^ diff_r.merged;
        shift_numeral(&diff->original);
    }

    return &diff->original;
}

unsigned int borrow(int current, roman_convert *left, roman_convert *right) {
    int next = current - 1;
    unsigned int next_numeral = left->merged & mask_numerals[next];
    unsigned int current_mask = mask_numerals[current];
    if (next_numeral > 0) {
        next_numeral >>= 1;
        left->merged &= next_numeral | ~mask_numerals[next];
        return current_mask;
    }
    else {
        return borrow(next, left, right) | current_mask;
    }
}

int parse_numeral_lookahead(char numeral, char lookahead, roman *r) {
    if (numeral == 'I' && lookahead == 'V') {
        r->I = 0b1111;
    }
    else if (numeral == 'I' && lookahead == 'X') {
        r->I = 0b1111;
        r->V = 0b1;
    }
    else if (numeral == 'X' && lookahead == 'L') {
        r->X = 0b1111;
    }
    else if (numeral == 'X' && lookahead == 'C') {
        r->X = 0b1111;
        r->L = 0b1;
    }
    else if (numeral == 'C' && lookahead == 'D') {
        r->C = 0b1111;
    }
    else if (numeral == 'C' && lookahead == 'M') {
        r->C = 0b1111;
        r->D = 0b1;
    }
    else {
        parse_numeral(numeral, r);
        return 0;
    }
    return 1;
}

int parse_numeral(char numeral, roman *r) {
    switch (numeral) {
        case 'I':
            r->I <<= 1;
            r->I |= 1;
            break;
        case 'V':
            r->V++;
            break;
        case 'X':
            r->X <<= 1;
            r->X |= 1;
            break;
        case 'L':
            r->L++;
            break;
        case 'C':
            r->C <<= 1;
            r->C |= 1;
            break;
        case 'D':
            r->D++;
            break;
        case 'M':
            r->M <<= 1;
            r->M |= 1;
            break;
        case 'N':
            memset(r, 0, sizeof(roman));
            break;
    }
    return 0;
}

void shift_numeral(roman *r) {
    while (r->M > 0 && (r->M & 0x1) != 1) {
        r->M >>= 1;
    }
    while (r->C > 0 && (r->C & 0x1) != 1) {
        r->C >>= 1;
    }
    while (r->X > 0 && (r->X & 0x1) != 1) {
        r->X >>= 1;
    }
    while (r->I > 0 && (r->I & 0x1) != 1) {
        r->I >>= 1;
    }
}

