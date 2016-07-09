//
// Created by James Stumme on 7/9/16.
//

#ifndef FALCONCALC_ASSERTS_H
#define FALCONCALC_ASSERTS_H

#include <check.h>

#include "falcon_calc.h"


#define _ck_assert_roman(cX, OP, cY) do { \
  roman *_ck_x = (cX); \
  roman *_ck_y = (cY); \
  ck_assert_msg(_ck_x->M OP _ck_y->M, "Assertion '%s' failed: %s == 0x%x, %s == 0x%x", #cX" "#OP" "#cY, #cX, *_ck_x, #cY, *_ck_y); \
  ck_assert_msg(_ck_x->D OP _ck_y->D, "Assertion '%s' failed: %s == 0x%x, %s == 0x%x", #cX" "#OP" "#cY, #cX, *_ck_x, #cY, *_ck_y); \
  ck_assert_msg(_ck_x->C OP _ck_y->C, "Assertion '%s' failed: %s == 0x%x, %s == 0x%x", #cX" "#OP" "#cY, #cX, *_ck_x, #cY, *_ck_y); \
  ck_assert_msg(_ck_x->L OP _ck_y->L, "Assertion '%s' failed: %s == 0x%x, %s == 0x%x", #cX" "#OP" "#cY, #cX, *_ck_x, #cY, *_ck_y); \
  ck_assert_msg(_ck_x->X OP _ck_y->X, "Assertion '%s' failed: %s == 0x%x, %s == 0x%x", #cX" "#OP" "#cY, #cX, *_ck_x, #cY, *_ck_y); \
  ck_assert_msg(_ck_x->V OP _ck_y->V, "Assertion '%s' failed: %s == 0x%x, %s == 0x%x", #cX" "#OP" "#cY, #cX, *_ck_x, #cY, *_ck_y); \
  ck_assert_msg(_ck_x->I OP _ck_y->I, "Assertion '%s' failed: %s == 0x%x, %s == 0x%x", #cX" "#OP" "#cY, #cX, *_ck_x, #cY, *_ck_y); \
} while (0)

#define ck_assert_roman_eq(X, Y) _ck_assert_roman(X, ==, Y)

#define ck_assert_not_null(X) do { \
  ck_assert_msg(X !=  0, "Assertion '%s' not null failed.", #X); \
} while (0)

#endif //FALCONCALC_ASSERTS_H
