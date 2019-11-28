/* 
 * Copyright 2019 - 2019, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Tests taken from:
 * https://scarcitycomputing.blogspot.com/2013/04/damerau-levenshtein-edit-distance.html
 * https://github.com/tdebatty/java-string-similarity#damerau-levenshtein
 */

#include <check.h>
#include <stdlib.h>
#include "damerau-levenshtein.h"

/*
 *  Tests what happens if str_a is empty (distance is length of str_b)
 */
START_TEST(test_a_is_empty)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("", "aa"), 2);
}
END_TEST

/*
 *  Tests what happens if str_b is empty (distance is length of str_a)
 */
START_TEST(test_b_is_empty)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("aaa", ""), 3);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_damerau_levenshtein_is_1_a)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("ABCDEF", "ABDCEF"), 1);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_damerau_levenshtein_is_1_b)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("ABCDEF", "ABCDE"), 1);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_damerau_levenshtein_is_1_c)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("ABCDEF", "BCDEF"), 1);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_damerau_levenshtein_is_1_d)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("ABCDEF", "ABCGDEF"), 1);
}
END_TEST


/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_damerau_levenshtein_is_2_a)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("ABCDEF", "BACDFE"), 2);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_damerau_levenshtein_is_2_b)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("a abct", "a cat"), 2);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_damerau_levenshtein_is_6)
{
	ck_assert_int_eq(_damerau_levenshtein_distance("ABCDEF", "POIU"), 6);
}
END_TEST


/*
 * Create test suite
 */
Suite *
damerau_levenshtein_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("DamerauLevenshtein");

	/* Core test case */
	tc_core = tcase_create("Core");

	/* Add tests here */
	tcase_add_test(tc_core, test_a_is_empty);
	tcase_add_test(tc_core, test_b_is_empty);
	tcase_add_test(tc_core, test_damerau_levenshtein_is_1_a);
	tcase_add_test(tc_core, test_damerau_levenshtein_is_1_b);
	tcase_add_test(tc_core, test_damerau_levenshtein_is_1_c);
	tcase_add_test(tc_core, test_damerau_levenshtein_is_1_d);
	tcase_add_test(tc_core, test_damerau_levenshtein_is_2_a);
	tcase_add_test(tc_core, test_damerau_levenshtein_is_2_b);
	tcase_add_test(tc_core, test_damerau_levenshtein_is_6);
	suite_add_tcase(s, tc_core);

	return s;
}

int
main(int argc, char **argv)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = damerau_levenshtein_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
