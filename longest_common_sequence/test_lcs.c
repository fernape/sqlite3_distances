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

START_TEST(test_lcs_is_0)
{
	ck_assert_int_eq(_lcs_distance("a", "b"), 0);
}
END_TEST

START_TEST(test_lcs_is_1_a)
{
	ck_assert_int_eq(_lcs_distance("a", "ba"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_b)
{
	ck_assert_int_eq(_lcs_distance("a", "bad"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_c)
{
	ck_assert_int_eq(_lcs_distance("a", "bade"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_d)
{
	ck_assert_int_eq(_lcs_distance("a", "badef"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_e)
{
	ck_assert_int_eq(_lcs_distance("ab", "b"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_f)
{
	ck_assert_int_eq(_lcs_distance("ab", "ba"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_g)
{
	ck_assert_int_eq(_lcs_distance("ab", "bad"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_h)
{
	ck_assert_int_eq(_lcs_distance("ab", "bade"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_i)
{
	ck_assert_int_eq(_lcs_distance("ab", "badef"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_j)
{
	ck_assert_int_eq(_lcs_distance("abc", "b"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_k)
{
	ck_assert_int_eq(_lcs_distance("abc", "ba"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_l)
{
	ck_assert_int_eq(_lcs_distance("abc", "bad"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_m)
{
	ck_assert_int_eq(_lcs_distance("abc", "bade"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_n)
{
	ck_assert_int_eq(_lcs_distance("abc", "badef"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_o)
{
	ck_assert_int_eq(_lcs_distance("abcd", "b"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_p)
{
	ck_assert_int_eq(_lcs_distance("abcd", "ba"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_q)
{
	ck_assert_int_eq(_lcs_distance("abcde", "b"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_r)
{
	ck_assert_int_eq(_lcs_distance("abcde", "ba"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_s)
{
	ck_assert_int_eq(_lcs_distance("abcdef", "b"), 1);
}
END_TEST

START_TEST(test_lcs_is_1_t)
{
	ck_assert_int_eq(_lcs_distance("abcdef", "ba"), 1);
}
END_TEST

START_TEST(test_lcs_is_2_a)
{
	ck_assert_int_eq(_lcs_distance("abcd", "bad"), 2);
}
END_TEST

START_TEST(test_lcs_is_2_b)
{
	ck_assert_int_eq(_lcs_distance("abcd", "bade"), 2);
}
END_TEST

START_TEST(test_lcs_is_2_c)
{
	ck_assert_int_eq(_lcs_distance("abcd", "badef"), 2);
}
END_TEST

START_TEST(test_lcs_is_2_d)
{
	ck_assert_int_eq(_lcs_distance("abcde", "bad"), 2);
}
END_TEST

START_TEST(test_lcs_is_2_e)
{
	ck_assert_int_eq(_lcs_distance("abcdef", "bad"), 2);
}
END_TEST

START_TEST(test_lcs_is_3_a)
{
	ck_assert_int_eq(_lcs_distance("abcde", "bade"), 3);
}
END_TEST

START_TEST(test_lcs_is_3_b)
{
	ck_assert_int_eq(_lcs_distance("abcde", "badef"), 3);
}
END_TEST

START_TEST(test_lcs_is_3_c)
{
	ck_assert_int_eq(_lcs_distance("abcdef", "bade"), 3);
}
END_TEST

START_TEST(test_lcs_is_4_a)
{
	ck_assert_int_eq(_lcs_distance("abcdef", "badef"), 4);
}
END_TEST

START_TEST(test_lcs_is_4_b)
{
	ck_assert_int_eq(_lcs_distance("ABDCEF", "BADEF"), 4);
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
	tcase_add_test(tc_core, test_lcs_is_0);
	tcase_add_test(tc_core, test_lcs_is_1_a);
	tcase_add_test(tc_core, test_lcs_is_1_b);
	tcase_add_test(tc_core, test_lcs_is_1_c);
	tcase_add_test(tc_core, test_lcs_is_1_d);
	tcase_add_test(tc_core, test_lcs_is_1_e);
	tcase_add_test(tc_core, test_lcs_is_1_f);
	tcase_add_test(tc_core, test_lcs_is_1_g);
	tcase_add_test(tc_core, test_lcs_is_1_h);
	tcase_add_test(tc_core, test_lcs_is_1_i);
	tcase_add_test(tc_core, test_lcs_is_1_j);
	tcase_add_test(tc_core, test_lcs_is_1_k);
	tcase_add_test(tc_core, test_lcs_is_1_l);
	tcase_add_test(tc_core, test_lcs_is_1_m);
	tcase_add_test(tc_core, test_lcs_is_1_n);
	tcase_add_test(tc_core, test_lcs_is_1_o);
	tcase_add_test(tc_core, test_lcs_is_1_p);
	tcase_add_test(tc_core, test_lcs_is_1_q);
	tcase_add_test(tc_core, test_lcs_is_1_r);
	tcase_add_test(tc_core, test_lcs_is_1_s);
	tcase_add_test(tc_core, test_lcs_is_1_t);
	tcase_add_test(tc_core, test_lcs_is_2_a);
	tcase_add_test(tc_core, test_lcs_is_2_b);
	tcase_add_test(tc_core, test_lcs_is_2_c);
	tcase_add_test(tc_core, test_lcs_is_2_d);
	tcase_add_test(tc_core, test_lcs_is_2_e);
	tcase_add_test(tc_core, test_lcs_is_3_a);
	tcase_add_test(tc_core, test_lcs_is_3_b);
	tcase_add_test(tc_core, test_lcs_is_3_c);
	tcase_add_test(tc_core, test_lcs_is_4_a);
	tcase_add_test(tc_core, test_lcs_is_4_b);
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
