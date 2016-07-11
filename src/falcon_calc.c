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

int parse_numeral(char, roman *);
int parse_numeral_lookahead(char, char, roman *);
void shift_numeral(roman *);


roman *ator(char *str) {
    roman *r = calloc(1, sizeof(roman));

    //TODO: Look into safer string ops, this method is banking on the fact that there is a null terminated string.
    //TODO: 25 characters looks to be a valid range, but need to check expanded numerals.
    size_t length = strlen(str);
    for (int i = 0; i < length; i++) {
        i += parse_numeral_lookahead(str[i], str[i + 1], r);
    }

    return r;
}

roman *add(roman *left, roman *right) {
    roman_convert _left, _right;
    roman_convert *sum = calloc(1, sizeof(roman_convert));
    _left.original = *left;
    _right.original = *right;

    sum->merged = _left.merged | _right.merged;

    return &sum->original;
}

roman *subtract(roman *left, roman *right) {
    roman_convert _left, _right;
    roman_convert *difference = calloc(1, sizeof(roman_convert));
    _left.original = *left;
    _right.original = *right;

    difference->merged = _left.merged ^ _right.merged;
    shift_numeral(&difference->original);

    return &difference->original;
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
        r->V = 0b1;
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
            r->I++;
            break;
        case 'V':
            r->V++;
            break;
        case 'X':
            r->X <<= 1;
            r->X++;
            break;
        case 'L':
            r->L++;
            break;
        case 'C':
            r->C <<= 1;
            r->C++;
            break;
        case 'D':
            r->D++;
            break;
        case 'M':
            r->M <<= 1;
            r->M++;
            break;
        case 'N':
            memset(r, 0, sizeof(roman));
            break;
    }
    return 0;
}

void shift_numeral(roman *r) {
    while (r->I > 0 && (r->I & 0x1) != 1) {
        r->I >>= 1;
    }
}

