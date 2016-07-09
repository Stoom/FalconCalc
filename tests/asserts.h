//
// Created by James Stumme on 7/9/16.
//

#ifndef FALCONCALC_ASSERTS_H
#define FALCONCALC_ASSERTS_H

#include <check.h>

#include "falcon_calc.h"


#define _ck_assert_roman(X, OP, Y) do { \
  roman *_ck_x = (X); \
  roman *_ck_y = (Y); \
  ck_assert_msg(_ck_x->I OP _ck_y->I, "Assertion '%s' failed: %s == %ju, %s == %ju", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y); \
} while (0)

#define ck_assert_roman_eq(X, Y) _ck_assert_roman(X, ==, Y)

#define ck_assert_not_null(X) do { \
  ck_assert_msg(X !=  0, "Assertion '%s' not null failed.", #X); \
} while (0)

#endif //FALCONCALC_ASSERTS_H
