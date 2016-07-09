//
// Created by James Stumme on 7/8/16.
//

#ifndef FALCON_CALC_H
#define FALCON_CALC_H

typedef struct {
    unsigned int I : 4;
} roman;

roman *strtoroman(char *str);

#endif //FALCON_CALC_H
