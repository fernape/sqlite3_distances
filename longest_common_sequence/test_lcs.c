/* 
 * Copyright 2019 - 2020, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <check.h>
#include <stdlib.h>
#include "lcs.h"

/*
 * Test what happens if first string is null
 */
START_TEST(test_first_null)
{
	ck_assert_int_eq(_lcs_distance(NULL, "asdf"), 0);
}
END_TEST

/*
 * Test what happens if second string is null
 */
START_TEST(test_second_null)
{
	ck_assert_int_eq(_lcs_distance("asdf", NULL), 0);
}
END_TEST

/*
 * Test what happens if both strings are null
 */
START_TEST(test_both_null)
{
	ck_assert_int_eq(_lcs_distance(NULL, NULL), 0);
}
END_TEST

/*
 * Test what happens if first string is empty
 */
START_TEST(test_first_empty)
{
	ck_assert_int_eq(_lcs_distance("", "asdf"), 0);
}
END_TEST

/*
 * Test what happens if second string is empty
 */
START_TEST(test_second_empty)
{
	ck_assert_int_eq(_lcs_distance("asdf", ""), 0);
}
END_TEST

/*
 * Test what happens if both strings are empty
 */
START_TEST(test_both_empty)
{
	ck_assert_int_eq(_lcs_distance("", ""), 0);
}
END_TEST

/*
 * Create test suite
 */
Suite *
lcs_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("LongestCommonSequence");

	/* Core test case */
	tc_core = tcase_create("Core");

	/* Add tests here */
	tcase_add_test(tc_core, test_first_null);
	tcase_add_test(tc_core, test_second_null);
	tcase_add_test(tc_core, test_both_null);
	tcase_add_test(tc_core, test_first_empty);
	tcase_add_test(tc_core, test_second_empty);
	tcase_add_test(tc_core, test_both_empty);
	suite_add_tcase(s, tc_core);

	return s;
}

int
main(int argc, char **argv)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = lcs_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
