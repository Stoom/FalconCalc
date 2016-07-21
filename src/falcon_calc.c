//
// Created by James Stumme on 7/8/16.
//
#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "falcon_calc.h"

#define MAX_NUMERAL_LENGTH 19

typedef struct {
    unsigned int IV: 4;
    unsigned int _1: 1;
    unsigned int XL: 4;
    unsigned int _2: 1;
    unsigned int CD: 4;
    unsigned int _3: 1;
} roman_fours;

typedef struct {
    unsigned int IX: 5;
    unsigned int XC: 5;
    unsigned int CM: 5;
    unsigned int _: 4;
} roman_nines;

typedef union {
    roman original;
    roman_fours fours;
    roman_nines nines;
    unsigned int merged;
} roman_convert;

unsigned int mask_numerals[] = {0b01111000000000000000, 0b00000100000000000000,
                                0b00000011110000000000, 0b00000000001000000000,
                                0b00000000000111100000, 0b00000000000000010000,
                                0b00000000000000001111};
int mask_len = 7;

unsigned int mask_reduced[] = {0b01111000000000000000,
                               0b00000110000000000000, 0b00000100000000000000,
                               0b00000010000000000000, 0b00000001110000000000,
                               0b00000000001100000000, 0b00000000001000000000,
                               0b00000000000100000000, 0b00000000000011100000,
                               0b00000000000000011000, 0b00000000000000010000,
                               0b00000000000000001000, 0b00000000000000000111};
char *reduced_numeral[] = {"M",
                           "CM", "D", "CD", "C",
                           "XC", "L", "XL", "X",
                           "IX", "V", "IV", "I"};
int mask_reduced_len = 13;

void reduce_plus(char *, char *, unsigned int *, unsigned int, unsigned int, bool);
void shift_add(unsigned int *, unsigned int *, unsigned int *, unsigned int, unsigned int);
unsigned int borrow(int, roman_convert *, roman_convert *);
void shift_numeral(roman *);
int parse_numeral(char, roman *);
int parse_numeral_lookahead(char, char, roman_convert *);
int check_overflow(unsigned int, bool);
int check_overflow_look_ahead(unsigned int);


roman *ator(char *str) {
    if (str == NULL) {
        return NULL;
    }

    roman_convert *r = calloc(1, sizeof(roman_convert));

    size_t length = strnlen(str, MAX_NUMERAL_LENGTH);
    for (int i = 0; i < length; i++) {
        int ii = parse_numeral_lookahead(str[i], str[i + 1], r);

        if (ii < 0) {
            free(r);
            r = NULL;
            break;
        }

        i += ii;
    }

    return &r->original;
}

char *rtoa(roman *numeral) {
    if (numeral == NULL) {
        return NULL;
    }

    char *reduced = calloc(MAX_NUMERAL_LENGTH, sizeof(char));
    roman_convert _numeral;
    _numeral.original = *numeral;

    for (int current = 0; current < mask_reduced_len; current = current + 4) {
        unsigned int current_mask = mask_reduced[current];
        unsigned int nines_mask = 0x0;
        unsigned int fives_mask = 0x0;
        unsigned int fours_mask = 0x0;
        unsigned int ones_mask = 0x0;
        if (current < mask_reduced_len - 4) {
            nines_mask = mask_reduced[current + 1];
            fives_mask = mask_reduced[current + 2];
            fours_mask = mask_reduced[current + 3];
            ones_mask = mask_reduced[current + 4];
        }

        unsigned int current_numeral = _numeral.merged & current_mask;

        while (current_numeral & current_mask) {
            current_numeral >>= 1;
            strncat(reduced, reduced_numeral[current], MAX_NUMERAL_LENGTH);
        }

        reduce_plus(reduced, reduced_numeral[current + 1], &_numeral.merged, nines_mask, ones_mask, true);
        reduce_plus(reduced, reduced_numeral[current + 2], &_numeral.merged, fives_mask, ones_mask, false);
        reduce_plus(reduced, reduced_numeral[current + 3], &_numeral.merged, fours_mask, ones_mask, true);
    }

    return reduced;
}

void reduce_plus(char *str, char *numeral, unsigned int *n, unsigned int n_mask, unsigned int o_mask, bool wipe_ones) {
    if (n_mask > 0 && (*n & n_mask) == n_mask) {
        if (wipe_ones) {
            *n &= (~n_mask & ~o_mask);
        }
        strncat(str, numeral, MAX_NUMERAL_LENGTH);
    }
}

roman *add(roman *left, roman *right) {
    if (left == NULL || right == NULL) {
        return NULL;
    }

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
    if (left == NULL || right == NULL) {
        return NULL;
    }

    roman_convert _left, _right;
    roman_convert *diff = malloc(sizeof(roman_convert));
    roman_convert diff_l, diff_r;

    _left.original = *left;
    _right.original = *right;
    diff->merged = 0;

    if (_right.merged > _left.merged) {
        free(diff);
        return NULL;
    }

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

int parse_numeral_lookahead(char numeral, char lookahead, roman_convert *r) {
    int ret = 1;
    if (numeral == 'I' && lookahead == 'V') {
        ret = check_overflow_look_ahead(r->fours.IV);
        r->fours.IV = 0b1111;
    }
    else if (numeral == 'I' && lookahead == 'X') {
        ret = check_overflow_look_ahead(r->nines.IX);
        r->nines.IX = 0b11111;
    }
    else if (numeral == 'X' && lookahead == 'L') {
        ret = check_overflow_look_ahead(r->fours.XL);
        r->fours.XL = 0b1111;
    }
    else if (numeral == 'X' && lookahead == 'C') {
        ret = check_overflow_look_ahead(r->nines.XC);
        r->nines.XC = 0b11111;
    }
    else if (numeral == 'C' && lookahead == 'D') {
        ret = check_overflow_look_ahead(r->fours.CD);
        r->fours.CD = 0b1111;
    }
    else if (numeral == 'C' && lookahead == 'M') {
        ret = check_overflow_look_ahead(r->nines.CM);
        r->nines.CM = 0b11111;
    }
    else {
        ret = parse_numeral(numeral, &r->original);
    }
    return ret;
}

int parse_numeral(char numeral, roman *r) {
    int ret = 0;
    switch (numeral) {
        case 'I':
            ret = check_overflow(r->I, false);
            r->I <<= 1;
            r->I |= 1;
            break;
        case 'V':
            ret = check_overflow(r->V, true);
            r->V |= 1;
            break;
        case 'X':
            ret = check_overflow(r->X, false);
            r->X <<= 1;
            r->X |= 1;
            break;
        case 'L':
            ret = check_overflow(r->L, true);
            r->L |= 1;
            break;
        case 'C':
            ret = check_overflow(r->C, false);
            r->C <<= 1;
            r->C |= 1;
            break;
        case 'D':
            ret = check_overflow(r->D, true);
            r->D |= 1;
            break;
        case 'M':
            ret = check_overflow(r->M, false);
            r->M <<= 1;
            r->M |= 1;
            break;
        case 'N':
            memset(r, 0, sizeof(roman));
            break;
        default:
            ret = -1;
    }
    return ret;
}

int check_overflow(unsigned int numeral, bool single) {
    unsigned int max = (single) ? 0b1 : 0b1111;
    if (numeral == max) {
        return -1;
    }
    return 0;
}

int check_overflow_look_ahead(unsigned int numeral) {
    if (numeral > 0) {
        return -1;
    }
    return 1;
}
