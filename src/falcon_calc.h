//
// Created by James Stumme on 7/8/16.
//

#ifndef FALCON_CALC_H
#define FALCON_CALC_H

typedef struct {
    unsigned int I : 4;
    unsigned int V : 1;
    unsigned int X : 4;
    unsigned int L : 1;
    unsigned int C : 4;
    unsigned int D : 1;
    unsigned int M : 4;
} roman;

roman *ator(char *str);
roman *add(roman *left, roman *right);

#endif //FALCON_CALC_H
