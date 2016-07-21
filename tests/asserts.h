//
// Created by James Stumme on 7/9/16.
//

#ifndef FALCONCALC_ASSERTS_H
#define FALCONCALC_ASSERTS_H

#include <check.h>

#include "falcon_calc.h"


#define _ck_assert_roman(cX, OP, cY) do { \
  ck_assert_not_null(cX); \
  ck_assert_not_null(cY); \
  \
  roman *_ck_x = (cX); \
  roman *_ck_y = (cY); \
  char _ck_x_b[38]; \
  char _ck_y_b[38]; \
  \
  _itoa(_ck_x->I + (_ck_x->V << 4) + (_ck_x->X << 5) + (_ck_x->L << 9) + (_ck_x->C << 10) + (_ck_x->D << 14) + (_ck_x->M << 15), _ck_x_b); \
  _itoa(_ck_y->I + (_ck_y->V << 4) + (_ck_y->X << 5) + (_ck_y->L << 9) + (_ck_y->C << 10) + (_ck_y->D << 14) + (_ck_y->M << 15), _ck_y_b); \
  \
  ck_assert_msg(_ck_x->M OP _ck_y->M, "Assertion '%s' failed: %s == %s, %s == %s", #cX" "#OP" "#cY, #cX, _ck_x_b, #cY, _ck_y_b); \
  ck_assert_msg(_ck_x->D OP _ck_y->D, "Assertion '%s' failed: %s == %s, %s == %s", #cX" "#OP" "#cY, #cX, _ck_x_b, #cY, _ck_y_b); \
  ck_assert_msg(_ck_x->C OP _ck_y->C, "Assertion '%s' failed: %s == %s, %s == %s", #cX" "#OP" "#cY, #cX, _ck_x_b, #cY, _ck_y_b); \
  ck_assert_msg(_ck_x->L OP _ck_y->L, "Assertion '%s' failed: %s == %s, %s == %s", #cX" "#OP" "#cY, #cX, _ck_x_b, #cY, _ck_y_b); \
  ck_assert_msg(_ck_x->X OP _ck_y->X, "Assertion '%s' failed: %s == %s, %s == %s", #cX" "#OP" "#cY, #cX, _ck_x_b, #cY, _ck_y_b); \
  ck_assert_msg(_ck_x->V OP _ck_y->V, "Assertion '%s' failed: %s == %s, %s == %s", #cX" "#OP" "#cY, #cX, _ck_x_b, #cY, _ck_y_b); \
  ck_assert_msg(_ck_x->I OP _ck_y->I, "Assertion '%s' failed: %s == %s, %s == %s", #cX" "#OP" "#cY, #cX, _ck_x_b, #cY, _ck_y_b); \
} while (0)

#define ck_assert_roman_eq(X, Y) _ck_assert_roman(X, ==, Y)

#define ck_assert_not_null(X) do { \
  ck_assert_msg(X !=  NULL, "Assertion '%s' not null failed.", #X); \
} while (0)

#define ck_assert_null(X) do { \
  ck_assert_msg(X ==  NULL, "Assertion '%s' not null failed.", #X); \
} while (0)

void _itoa(int value, char *str) {
    static char num[] = "01";
    char *wstr = str;
    int base = 2;
    int i = 0;

    do {
        *wstr++ = num[value % base];
        if ((i % 4) == 3)
            *wstr++ = ' ';
        i++;
    } while (value /= base);
    *wstr = '\0';

    char *begin = str;
    char *end = wstr - 1;
    char aux;
    while (end > begin) {
        aux = *end, *end-- = *begin, *begin++ = aux;
    }
}

#endif //FALCONCALC_ASSERTS_H
