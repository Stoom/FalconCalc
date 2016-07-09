//
// Created by James Stumme on 7/8/16.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "falcon_calc.h"

int parse_numeral_lookahead(char, char, roman *);

roman *strtoroman(char *str) {
    roman *r = calloc(1, sizeof(roman));

    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        i += parse_numeral_lookahead(str[i], str[i+1], r);
    }

    return r;
}

int parse_numeral_lookahead(char numeral, char lookahead, roman *r) {
    if (numeral == 'I' && lookahead == 'V') {
        r->I += 4;
    }
    else {
        switch (numeral) {
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
        return 0;
    }
    return 1;
}