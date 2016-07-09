//
// Created by James Stumme on 7/8/16.
//

#include <stdio.h>
#include <check.h>
#include <stdlib.h>

#include "falcon_calc.h"


START_TEST (test_hello)
    {
        ck_assert_int_eq(0, 0);
    }
END_TEST

Suite *falcon_calc_suite(void)
{
    Suite *suite = suite_create("FalconCalc");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_hello);
    suite_add_tcase(suite, tc_core);

    return suite;
}

int main(int argc, char *argv[])
{
    int number_failed;
    Suite *suite = falcon_calc_suite();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0)
           ? EXIT_SUCCESS
           : EXIT_FAILURE;
}