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
    parse_numeral(str[length - 1], r);

    return r;
}

void parse_numeral(char numeral, roman *r) {
    if (numeral == 'I') {
        r->I++;
    }
}