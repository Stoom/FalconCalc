//
// Created by James Stumme on 7/10/16.
//

#ifndef FALCONCALC_TEST_CALCULATOR_H
#define FALCONCALC_TEST_CALCULATOR_H

#include <check.h>
#include <falcon_calc.h>
#include <stdlib.h>
#include "asserts.h"

START_TEST (test_add__distinct_numerals)
    {
        roman *left = ator("XVI");
        roman *right = ator("MDCL");

        roman *expected = ator("MDCLXVI");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
    }
END_TEST
START_TEST (test_add__same_numeral)
    {
        roman *left = ator("I");
        roman *right = ator("I");

        roman *expected = ator("II");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
    }
END_TEST

Suite *test_calculator_suite(void) {
    Suite *suite = suite_create("Calculator");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add__distinct_numerals);
    tcase_add_test(tc_core, test_add__same_numeral);
    suite_add_tcase(suite, tc_core);

    return suite;
}
#endif //FALCONCALC_TEST_CALCULATOR_H
