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
        char attack[] = {'M', 'M', 'M', 'M', 'D',
                         'C', 'C', 'C', 'C', 'L',
                         'X', 'X', 'X', 'X', 'V',
                         'I', 'I', 'I', 'I', (char) 0x90, (char) 0x90, (char) 0x90, (char) 0x90, 'I'};
        memcpy(str, attack, sizeof(char) * strlen(attack));

        roman *expected = calloc(1, sizeof(roman));
        roman *actual;

        expected->M = 0b1111;
        expected->D = 0b1;
        expected->C = 0b1111;
        expected->L = 0b1;
        expected->X = 0b1111;
        expected->V = 0b1;
        expected->I = 0b1111;

        actual = ator(str);

        ck_assert_not_null(actual);
        ck_assert_roman_eq(expected, actual);

        free(expected);
        free(actual);
    }
END_TEST
START_TEST (test_ator__converting_invalid_character_fails)
    {
        char str[] = "FOOBAR";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__ignores_null)
    {
        roman *actual;

        actual = ator(NULL);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_too_many_Is)
    {
        char str[] = "IIIII";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_too_many_Vs)
    {
        char str[] = "VV";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_too_many_Xs)
    {
        char str[] = "XXXXX";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_too_many_Ls)
    {
        char str[] = "LL";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_too_many_Cs)
    {
        char str[] = "CCCCC";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_too_many_Ds)
    {
        char str[] = "DD";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_too_many_Ms)
    {
        char str[] = "MMMMM";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_IVI)
    {
        char str[] = "IVI";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_IXV)
    {
        char str[] = "IXV";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_IXI)
    {
        char str[] = "IXI";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_XLX)
    {
        char str[] = "XLX";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_XCL)
    {
        char str[] = "XCL";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_XCX)
    {
        char str[] = "XCX";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_CDC)
    {
        char str[] = "CDC";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_CMD)
    {
        char str[] = "CMD";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST
START_TEST (test_ator__detects_CMC)
    {
        char str[] = "CMC";
        roman *actual;

        actual = ator(str);

        ck_assert_null(actual);

        free(actual);
    }
END_TEST

START_TEST (test_rtoa__converts_M)
    {
        roman *r = ator("M");
        char expected[] = "M";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_MM)
    {
        roman *r = ator("MM");
        char expected[] = "MM";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_D)
    {
        roman *r = ator("D");
        char expected[] = "D";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_MD)
    {
        roman *r = ator("MD");
        char expected[] = "MD";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_CC)
    {
        roman *r = ator("CC");
        char expected[] = "CC";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_CD)
    {
        roman *r = ator("CD");
        char expected[] = "CD";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_CM)
    {
        roman *r = ator("CM");
        char expected[] = "CM";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_MMMMCMXCIX)
    {
        roman *r = ator("MMMMCMXCIX");
        char expected[] = "MMMMCMXCIX";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_CDXLIV)
    {
        roman *r = ator("CDXLIV");
        char expected[] = "CDXLIV";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_CXI)
    {
        roman *r = ator("CXI");
        char expected[] = "CXI";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__converts_LV)
    {
        roman *r = ator("LV");
        char expected[] = "LV";

        char *actual = rtoa(r);

        ck_assert_not_null(actual);
        ck_assert_str_eq(expected, actual);

        free(r);
        free(actual);
    }
END_TEST
START_TEST (test_rtoa__ignores_null)
    {

        char *actual = rtoa(NULL);

        ck_assert_null(actual);

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
    tcase_add_test(tc_core, test_ator__converting_invalid_character_fails);
    tcase_add_test(tc_core, test_ator__ignores_null);
    tcase_add_test(tc_core, test_ator__detects_too_many_Is);
    tcase_add_test(tc_core, test_ator__detects_too_many_Vs);
    tcase_add_test(tc_core, test_ator__detects_too_many_Xs);
    tcase_add_test(tc_core, test_ator__detects_too_many_Ls);
    tcase_add_test(tc_core, test_ator__detects_too_many_Cs);
    tcase_add_test(tc_core, test_ator__detects_too_many_Ds);
    tcase_add_test(tc_core, test_ator__detects_too_many_Ms);
    tcase_add_test(tc_core, test_ator__detects_IVI);
    tcase_add_test(tc_core, test_ator__detects_IXV);
    tcase_add_test(tc_core, test_ator__detects_IXI);
    tcase_add_test(tc_core, test_ator__detects_XLX);
    tcase_add_test(tc_core, test_ator__detects_XCL);
    tcase_add_test(tc_core, test_ator__detects_XCX);
    tcase_add_test(tc_core, test_ator__detects_CDC);
    tcase_add_test(tc_core, test_ator__detects_CMD);
    tcase_add_test(tc_core, test_ator__detects_CMC);

    tcase_add_test(tc_core, test_rtoa__converts_M);
    tcase_add_test(tc_core, test_rtoa__converts_MM);
    tcase_add_test(tc_core, test_rtoa__converts_D);
    tcase_add_test(tc_core, test_rtoa__converts_MD);
    tcase_add_test(tc_core, test_rtoa__converts_CC);
    tcase_add_test(tc_core, test_rtoa__converts_CD);
    tcase_add_test(tc_core, test_rtoa__converts_CM);
    tcase_add_test(tc_core, test_rtoa__converts_MMMMCMXCIX);
    tcase_add_test(tc_core, test_rtoa__converts_CDXLIV);
    tcase_add_test(tc_core, test_rtoa__converts_CXI);
    tcase_add_test(tc_core, test_rtoa__converts_LV);
    tcase_add_test(tc_core, test_rtoa__ignores_null);
    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif //TEST_CONVERT_H