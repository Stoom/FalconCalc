//
// Created by James Stumme on 7/8/16.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "falcon_calc.h"

int parse_numeral(char, roman *);

int parse_numeral_lookahead(char, char, roman *);


roman *ator(char *str) {
    roman *r = calloc(1, sizeof(roman));

    //TODO: Look into safer string ops, this method is banking on the fact that there is a null terminated string.
    //TODO: 25 characters looks to be a valid range, but need to check expanded numerals.
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        i += parse_numeral_lookahead(str[i], str[i + 1], r);
    }

    return r;
}

int parse_numeral_lookahead(char numeral, char lookahead, roman *r) {
    if (numeral == 'I' && lookahead == 'V') {
        r->I = 0b1000;
    }
    else if (numeral == 'I' && lookahead == 'X') {
        r->I = 0b1000;
        r->V = 0b1;
    }
    else if (numeral == 'X' && lookahead == 'L') {
        r->X = 0b1000;
    }
    else if (numeral == 'X' && lookahead == 'C') {
        r->X = 0b1000;
        r->V = 0b1;
    }
    else if (numeral == 'C' && lookahead == 'D') {
        r->C = 0b1000;
    }
    else if (numeral == 'C' && lookahead == 'M') {
        r->C = 0b1000;
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
            if (r->I == 0) r->I++;
            break;
        case 'V':
            r->V++;
            break;
        case 'X':
            r->X <<= 1;
            if (r->X == 0) r->X++;
            break;
        case 'L':
            r->L++;
            break;
        case 'C':
            r->C <<= 1;
            if (r->C == 0) r->C++;
            break;
        case 'D':
            r->D++;
            break;
        case 'M':
            r->M <<= 1;
            if (r->M == 0) r->M++;
            break;
    }
    return 0;
}