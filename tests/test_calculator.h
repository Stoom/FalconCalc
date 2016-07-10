//
// Created by James Stumme on 7/9/16.
//
#ifndef TEST_CALCULATOR_H
#define TEST_CALCULATOR_H

#include <check.h>
#include "asserts.h"
#include <falcon_calc.h>

START_TEST (test_strtoroman__converts_string_I_to_romain_numeral_1)
    {
        char str[] = "I";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b0001;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_strtoroman__converts_string_II_to_romain_numeral_2)
    {
        char str[] = "II";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b0010;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_strtoroman__converts_string_V_to_romain_numeral_5)
    {
        char str[] = "V";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->V = 0b1;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_strtoroman__converts_string_MDCLX_to_romain_numeral_1660)
    {
        char str[] = "MDCLX";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->X = 0b0001;
        expected->L = 0b1;
        expected->C = 0b0001;
        expected->D = 0b1;
        expected->M = 0b0001;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_strtoroman__converts_string_IV_to_romain_numeral_4)
    {
        char str[] = "IV";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b1000;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_strtoroman__converts_string_IX_to_romain_numeral_9)
    {
        char str[] = "IX";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b1000;
        expected->V = 0b1;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_strtoroman__converts_string_CDXL_to_romain_numeral_440)
    {
        char str[] = "CDXL";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->X = 0b1000;
        expected->C = 0b1000;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_strtoroman__converts_string_CMXC_to_romain_numeral_990)
    {
        char str[] = "CMXC";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->V = 0b1;
        expected->X = 0b1000;
        expected->D = 0b1;
        expected->C = 0b1000;
        actual = strtoroman(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST

Suite *test_calculator_suite(void) {
    Suite *suite = suite_create("FalconCalc");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_strtoroman__converts_string_I_to_romain_numeral_1);
    tcase_add_test(tc_core, test_strtoroman__converts_string_II_to_romain_numeral_2);
    tcase_add_test(tc_core, test_strtoroman__converts_string_V_to_romain_numeral_5);
    tcase_add_test(tc_core, test_strtoroman__converts_string_MDCLX_to_romain_numeral_1660);
    tcase_add_test(tc_core, test_strtoroman__converts_string_IV_to_romain_numeral_4);
    tcase_add_test(tc_core, test_strtoroman__converts_string_IX_to_romain_numeral_9);
    tcase_add_test(tc_core, test_strtoroman__converts_string_CDXL_to_romain_numeral_440);
    tcase_add_test(tc_core, test_strtoroman__converts_string_CMXC_to_romain_numeral_990);
    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif //TEST_CALCULATOR_H