//
// Created by James Stumme on 7/8/16.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "falcon_calc.h"

void parse_numeral(char, roman *);

roman *strtoroman(char *str) {
    roman *r = calloc(1, sizeof(roman));
    bzero(r, sizeof(roman));

    int length = strlen(str);
    for (int i = 0; i < length - 1; i++) {
        parse_numeral(str[i], r);
    }
    parse_numeral(str[length - 1], r);

    return r;
}

void parse_numeral(char numeral, roman *r) {
    switch(numeral)
    {
        case 'I':
            r->I++;
            break;
        case 'V':
            r->V++;
            break;
        case 'X':
            r->X++;
            break;
        case 'L':
            r->L++;
            break;
        case 'C':
            r->C++;
            break;
        case 'D':
            r->D++;
            break;
        case 'M':
            r->M++;
            break;
    }
}