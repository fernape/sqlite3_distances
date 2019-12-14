/* 
 * Copyright 2019 - 2019, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Tests taken from:
 * http://www.algomation.com/player?algorithm=5657518553ab3d0300f13819
 */

#include <check.h>
#include <stdlib.h>
#include "optimal_string_alignment.h"

/*
 *  Edit distance of a string with itself should be zero
 */
START_TEST(test_is_0)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("a", "a"), 0);
}
END_TEST

START_TEST(test_is_1_a)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("a", "az"), 1);
}
END_TEST

START_TEST(test_is_1_b)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("ab", "a"), 1);
}
END_TEST

START_TEST(test_is_1_c)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("ab", "az"), 1);
}
END_TEST

START_TEST(test_is_1_d)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abc", "azc"), 1);
}
END_TEST

START_TEST(test_is_2_a)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("a", "azc"), 2);
}
END_TEST

START_TEST(test_is_2_b)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("ab", "azc"), 2);
}
END_TEST

START_TEST(test_is_2_c)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abc", "a"), 2);
}
END_TEST

START_TEST(test_is_2_d)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abc", "az"), 2);
}
END_TEST

START_TEST(test_is_2_e)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abc", "azce"), 2);
}
END_TEST

START_TEST(test_is_2_f)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcd", "azc"), 2);
}
END_TEST

START_TEST(test_is_2_g)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcd", "azce"), 2);
}
END_TEST

START_TEST(test_is_2_h)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcd", "azced"), 2);
}
END_TEST

START_TEST(test_is_2_i)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcde", "azce"), 2);
}
END_TEST

START_TEST(test_is_3_a)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("a", "azce"), 3);
}
END_TEST

START_TEST(test_is_3_b)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("ab", "azce"), 3);
}
END_TEST

START_TEST(test_is_3_c)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abc", "azced"), 3);
}
END_TEST

START_TEST(test_is_3_d)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcd", "a"), 3);
}
END_TEST

START_TEST(test_is_3_e)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcd", "az"), 3);
}
END_TEST

START_TEST(test_is_3_f)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcde", "azc"), 3);
}
END_TEST

START_TEST(test_is_3_g)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcde", "azced"), 2);
}
END_TEST

START_TEST(test_is_3_h)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcdef", "azce"), 3);
}
END_TEST

START_TEST(test_is_3_i)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcdef", "azced"), 3);
}
END_TEST

START_TEST(test_is_4_a)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("a", "azced"), 4);
}
END_TEST

START_TEST(test_is_4_b)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("ab", "azced"), 4);
}
END_TEST

START_TEST(test_is_4_c)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcde", "a"), 4);
}
END_TEST

START_TEST(test_is_4_d)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcde", "az"), 4);
}
END_TEST

START_TEST(test_is_4_e)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcdef", "azc"), 4);
}
END_TEST

START_TEST(test_is_5_a)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcdef", "a"), 5);
}
END_TEST

START_TEST(test_is_5_b)
{
	ck_assert_int_eq(_optimal_string_alignment_distance("abcdef", "az"), 5);
}
END_TEST

/*
 * Create test suite
 */
Suite *
optimal_string_alignment_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("OptimalStringAlignment");

	/* Core test case */
	tc_core = tcase_create("Core");


	/* Add tests here */
	tcase_add_test(tc_core, test_is_0);
	tcase_add_test(tc_core, test_is_1_a);
	tcase_add_test(tc_core, test_is_1_b);
	tcase_add_test(tc_core, test_is_1_c);
	tcase_add_test(tc_core, test_is_1_d);
	tcase_add_test(tc_core, test_is_2_a);
	tcase_add_test(tc_core, test_is_2_b);
	tcase_add_test(tc_core, test_is_2_c);
	tcase_add_test(tc_core, test_is_2_d);
	tcase_add_test(tc_core, test_is_2_e);
	tcase_add_test(tc_core, test_is_2_f);
	tcase_add_test(tc_core, test_is_2_g);
	tcase_add_test(tc_core, test_is_2_h);
	tcase_add_test(tc_core, test_is_2_i);
	tcase_add_test(tc_core, test_is_3_a);
	tcase_add_test(tc_core, test_is_3_b);
	tcase_add_test(tc_core, test_is_3_c);
	tcase_add_test(tc_core, test_is_3_d);
	tcase_add_test(tc_core, test_is_3_e);
	tcase_add_test(tc_core, test_is_3_f);
	tcase_add_test(tc_core, test_is_3_g);
	tcase_add_test(tc_core, test_is_3_h);
	tcase_add_test(tc_core, test_is_3_i);
	tcase_add_test(tc_core, test_is_4_a);
	tcase_add_test(tc_core, test_is_4_b);
	tcase_add_test(tc_core, test_is_4_c);
	tcase_add_test(tc_core, test_is_4_d);
	tcase_add_test(tc_core, test_is_4_e);
	tcase_add_test(tc_core, test_is_5_a);
	tcase_add_test(tc_core, test_is_5_b);
	suite_add_tcase(s, tc_core);

	return s;
}

int
main(int argc, char **argv)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = optimal_string_alignment_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
