//
// Created by James Stumme on 7/10/16.
//

#ifndef FALCONCALC_TEST_CALCULATOR_H
#define FALCONCALC_TEST_CALCULATOR_H

#include <check.h>
#include <falcon_calc.h>
#include <stdlib.h>
#include "asserts.h"

void free_romans(roman*, roman*, roman*, roman*);

START_TEST (test_add__distinct_numerals)
    {
        roman *left = ator("XVI");
        roman *right = ator("MDCL");

        roman *expected = ator("MDCLXVI");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST

START_TEST (test_subtract__I_from_I_numerals)
    {
        roman *left = ator("I");
        roman *right = ator("I");

        roman *expected = ator("N");
        roman *actual;

        actual = subtract(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_subtract__I_from_II_numerals)
    {
        roman *left = ator("II");
        roman *right = ator("I");

        roman *expected = ator("I");
        roman *actual;

        actual = subtract(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_subtract__duplicate_numerals)
    {
        roman *left = ator("MMCCXXII");
        roman *right = ator("MCXI");

        roman *expected = ator("MCXI");
        roman *actual;

        actual = subtract(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST

Suite *test_calculator_suite(void) {
    Suite *suite = suite_create("Calculator");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add__distinct_numerals);
    tcase_add_test(tc_core, test_subtract__I_from_I_numerals);
    tcase_add_test(tc_core, test_subtract__I_from_II_numerals);
    tcase_add_test(tc_core, test_subtract__duplicate_numerals);
    suite_add_tcase(suite, tc_core);

    return suite;
}

void free_romans(roman *left, roman *right, roman *expected, roman *actual) {
    free(left);
    free(right);
    free(expected);
    free(actual);
}

#endif //FALCONCALC_TEST_CALCULATOR_H
