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
START_TEST (test_add__same_numeral)
    {
        roman *left = ator("I");
        roman *right = ator("I");

        roman *expected = ator("II");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_add__II_and_III)
    {
        roman *left = ator("II");
        roman *right = ator("III");

        roman *expected = ator("V");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_add__IV_and_II)
    {
        roman *left = ator("IV");
        roman *right = ator("II");

        roman *expected = ator("VI");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_add__CMXCIX_and_I)
    {
        roman *left = ator("CMXCIX");
        roman *right = ator("I");

        roman *expected = ator("M");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_add__M_and_M)
    {
        roman *left = ator("M");
        roman *right = ator("M");

        roman *expected = ator("MM");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_add__MMMM_and_M_overflows)
    {
        roman *left = ator("MMMM");
        roman *right = ator("M");

        roman *expected = ator("N");
        roman *actual;

        actual = add(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_add__ignores_left_null)
    {
        roman *right = ator("II");

        roman *actual;

        actual = add(NULL, right);

        ck_assert_null(actual);

        free(right);
        free(actual);
    }
END_TEST
START_TEST (test_add__ignores_right_null)
    {
        roman *left = ator("II");

        roman *actual;

        actual = add(left, NULL);

        ck_assert_null(actual);

        free(left);
        free(actual);
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
START_TEST (test_subtract__borrows_for_I_from_V)
    {
        roman *left = ator("V");
        roman *right = ator("I");

        roman *expected = ator("IV");
        roman *actual;

        actual = subtract(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_subtract__borrows_for_I_from_X)
    {
        roman *left = ator("X");
        roman *right = ator("I");

        roman *expected = ator("VIV");
        roman *actual;

        actual = subtract(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_subtract__borrows_for_CXXI_from_MCXII)
    {
        roman *left = ator("MCXII");
        roman *right = ator("CXXI");

        roman *expected = ator("CMLXLI");
        roman *actual;

        actual = subtract(left, right);

        ck_assert_roman_eq(expected, actual);
        free_romans(left, right, expected, actual);
    }
END_TEST
START_TEST (test_subtract__larger_from_smaller_fails)
    {
        roman *left = ator("I");
        roman *right = ator("II");

        roman *actual;

        actual = subtract(left, right);

        ck_assert_null(actual);

        free(left);
        free(right);
        free(actual);
    }
END_TEST
START_TEST (test_subtract__ignores_left_null)
    {
        roman *right = ator("II");

        roman *actual;

        actual = subtract(NULL, right);

        ck_assert_null(actual);

        free(right);
        free(actual);
    }
END_TEST
START_TEST (test_subtract__ignores_right_null)
    {
        roman *left = ator("II");

        roman *actual;

        actual = subtract(left, NULL);

        ck_assert_null(actual);

        free(left);
        free(actual);
    }
END_TEST

Suite *test_calculator_suite(void) {
    Suite *suite = suite_create("Calculator");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add__distinct_numerals);
    tcase_add_test(tc_core, test_add__same_numeral);
    tcase_add_test(tc_core, test_add__II_and_III);
    tcase_add_test(tc_core, test_add__IV_and_II);
    tcase_add_test(tc_core, test_add__CMXCIX_and_I);
    tcase_add_test(tc_core, test_add__M_and_M);
    tcase_add_test(tc_core, test_add__MMMM_and_M_overflows);
    tcase_add_test(tc_core, test_add__ignores_left_null);
    tcase_add_test(tc_core, test_add__ignores_right_null);

    tcase_add_test(tc_core, test_subtract__I_from_I_numerals);
    tcase_add_test(tc_core, test_subtract__I_from_II_numerals);
    tcase_add_test(tc_core, test_subtract__duplicate_numerals);
    tcase_add_test(tc_core, test_subtract__borrows_for_I_from_V);
    tcase_add_test(tc_core, test_subtract__borrows_for_I_from_X);
    tcase_add_test(tc_core, test_subtract__borrows_for_CXXI_from_MCXII);
    tcase_add_test(tc_core, test_subtract__larger_from_smaller_fails);
    tcase_add_test(tc_core, test_subtract__ignores_left_null);
    tcase_add_test(tc_core, test_subtract__ignores_right_null);
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
