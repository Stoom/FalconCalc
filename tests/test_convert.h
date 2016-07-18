//
// Created by James Stumme on 7/9/16.
//
#ifndef TEST_CONVERT_H
#define TEST_CONVERT_H

#include <check.h>
#include <falcon_calc.h>
#include "asserts.h"

START_TEST (test_ator__converts_string_I_to_romain_numeral_1)
    {
        char str[] = "I";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b0001;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_II_to_romain_numeral_2)
    {
        char str[] = "II";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b0011;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_V_to_romain_numeral_5)
    {
        char str[] = "V";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->V = 0b1;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_MDCLX_to_romain_numeral_1660)
    {
        char str[] = "MDCLX";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->X = 0b0001;
        expected->L = 0b1;
        expected->C = 0b0001;
        expected->D = 0b1;
        expected->M = 0b0001;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_IV_to_romain_numeral_4)
    {
        char str[] = "IV";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b1111;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_IX_to_romain_numeral_9)
    {
        char str[] = "IX";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->I = 0b1111;
        expected->V = 0b1;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_CDXL_to_romain_numeral_440)
    {
        char str[] = "CDXL";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->X = 0b1111;
        expected->C = 0b1111;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_CMXC_to_romain_numeral_990)
    {
        char str[] = "CMXC";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->X = 0b1111;
        expected->L = 0b1;
        expected->C = 0b1111;
        expected->D = 0b1;
        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converts_string_N_to_romain_numeral_nulla)
    {
        char str[] = "N";
        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__protects_against_buffer_overflow)
    {
        char *str = malloc(sizeof(char) * 19);
        char attack[] = {'M', (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90,
                         (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90,
                         (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90,
                         (char) 0x90, 'I'};
        memcpy(str, attack, sizeof(char) * strlen(attack));

        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->M = 0b001;

        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST

Suite *test_convert_suite(void) {
    Suite *suite = suite_create("Convert");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_ator__converts_string_I_to_romain_numeral_1);
    tcase_add_test(tc_core, test_ator__converts_string_II_to_romain_numeral_2);
    tcase_add_test(tc_core, test_ator__converts_string_V_to_romain_numeral_5);
    tcase_add_test(tc_core, test_ator__converts_string_MDCLX_to_romain_numeral_1660);
    tcase_add_test(tc_core, test_ator__converts_string_IV_to_romain_numeral_4);
    tcase_add_test(tc_core, test_ator__converts_string_IX_to_romain_numeral_9);
    tcase_add_test(tc_core, test_ator__converts_string_CDXL_to_romain_numeral_440);
    tcase_add_test(tc_core, test_ator__converts_string_CMXC_to_romain_numeral_990);
    tcase_add_test(tc_core, test_ator__converts_string_N_to_romain_numeral_nulla);
    tcase_add_test(tc_core, test_ator__protects_against_buffer_overflow);
    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif //TEST_CONVERT_H