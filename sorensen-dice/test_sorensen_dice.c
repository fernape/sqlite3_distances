/* 
 * Copyright 2019 - 2020, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Most of the examples here, come from:
 * http://www.algomation.com/algorithm/sorensen-dice-string-similarity
 *
 * Note that for some of the tests, there isn't an exact binary representation
 * so we need to check for a lower bound and an upper bound (test_2, test_4,
 * etc).
 */

#include <check.h>
#include <stdlib.h>
#include "sorensen-dice.h"

/*
 * Some tests for known cases
 */
START_TEST(test_a_is_empty)
{
	ck_assert_double_eq(_sorensen_dice_distance("", "word"), 0.0);
}
END_TEST

START_TEST(test_b_is_empty)
{
	ck_assert_double_eq(_sorensen_dice_distance("word", ""), 0.0);
}
END_TEST

START_TEST(test_1)
{
	ck_assert_double_eq(_sorensen_dice_distance("night", "nacht"), 0.25);
}
END_TEST

START_TEST(test_2)
{
	ck_assert_double_gt(_sorensen_dice_distance("conservationalists", "conversationalists"), 0.7647);
	ck_assert_double_lt(_sorensen_dice_distance("conservationalists", "conversationalists"), 0.7648);
}
END_TEST

START_TEST(test_3)
{
	ck_assert_double_eq(_sorensen_dice_distance("whirled", "world"), 0.2);
}
END_TEST

START_TEST(test_4)
{
	ck_assert_double_gt(_sorensen_dice_distance("complement", "compliment"), 0.7777);
	ck_assert_double_lt(_sorensen_dice_distance("complement", "compliment"), 0.7778);
}
END_TEST

START_TEST(test_5)
{
	ck_assert_double_gt(_sorensen_dice_distance("bazaar", "bizarre"), 0.3636);
	ck_assert_double_lt(_sorensen_dice_distance("bazaar", "bizarre"), 0.3637);
}
END_TEST

START_TEST(test_6)
{
	ck_assert_double_gt(_sorensen_dice_distance("accesary", "accesory"), 0.7142);
	ck_assert_double_lt(_sorensen_dice_distance("accesary", "accesory"), 0.7143);
}
END_TEST

START_TEST(test_7)
{
	ck_assert_double_eq(_sorensen_dice_distance("accessary", "accessory"), 0.75);
}
END_TEST

START_TEST(test_8)
{
	ck_assert_double_gt(_sorensen_dice_distance("algorithms are fun", "logarithms are not"), 0.5882);
	ck_assert_double_lt(_sorensen_dice_distance("algorithms are fun", "logarithms are not"), 0.5883);
}
END_TEST

START_TEST(test_9)
{
	ck_assert_double_gt(_sorensen_dice_distance("assistance", "assitants"), 0.5882);
	ck_assert_double_lt(_sorensen_dice_distance("assistance", "assitants"), 0.5883);
}
END_TEST

START_TEST(test_10)
{
	ck_assert_double_gt(_sorensen_dice_distance("assistance", "assistants"), 0.7777);
	ck_assert_double_lt(_sorensen_dice_distance("assistance", "assistants"), 0.7778);
}
END_TEST

START_TEST(test_11)
{
	ck_assert_double_eq(_sorensen_dice_distance("all together", "altogether"), 0.8);
}
END_TEST

START_TEST(test_12)
{
	ck_assert_double_eq(_sorensen_dice_distance("identical strings", "identical strings"), 1.0);
}
END_TEST

/*
 * Create test suite
 */
Suite *
sorensen_dice_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("SorensenDice");

	/* Core test case */
	tc_core = tcase_create("Core");

	/* Add tests here */
	tcase_add_test(tc_core, test_a_is_empty);
	tcase_add_test(tc_core, test_b_is_empty);
	tcase_add_test(tc_core, test_1);
	tcase_add_test(tc_core, test_2);
	tcase_add_test(tc_core, test_3);
	tcase_add_test(tc_core, test_4);
	tcase_add_test(tc_core, test_5);
	tcase_add_test(tc_core, test_6);
	tcase_add_test(tc_core, test_7);
	tcase_add_test(tc_core, test_8);
	tcase_add_test(tc_core, test_9);
	tcase_add_test(tc_core, test_10);
	tcase_add_test(tc_core, test_11);
	tcase_add_test(tc_core, test_12);
	suite_add_tcase(s, tc_core);

	return s;
}

int
main(int argc, char **argv)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = sorensen_dice_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
