#include <check.h>
#include <stdlib.h>
#include "hamming.h"

/*
 * Test the result if both strings are
 * of different length
 */
START_TEST(test_different_length)
{
	ck_assert_int_eq(_hamming_distance("a", "aa"), -1);
}
END_TEST

/*
 *  Tests what happens if str_a is null
 */
START_TEST(test_a_is_null)
{
	ck_assert_int_eq(_hamming_distance(NULL, "aa"), -1);
}
END_TEST

/*
 *  Tests what happens if str_b is null
 */
START_TEST(test_b_is_null)
{
	ck_assert_int_eq(_hamming_distance("aa", NULL), -1);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_hamming_is_1)
{
	/* Only 1 different character */
	ck_assert_int_eq(_hamming_distance("hello", "hallo"), 1);
}
END_TEST

/*
 * Test the difference is what is supposed to be
 */
START_TEST(test_hamming_is_2)
{
	/* Only 1 different character */
	ck_assert_int_eq(_hamming_distance("hello", "halle"), 2);
}
END_TEST

/*
 * Create test suite
 */
Suite *
hamming_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hamming");

	/* Core test case */
	tc_core = tcase_create("Core");

	/* Add tests here */
	tcase_add_test(tc_core, test_different_length);
	tcase_add_test(tc_core, test_a_is_null);
	tcase_add_test(tc_core, test_b_is_null);
	suite_add_tcase(s, tc_core);

	return s;
}

int
main(int argc, char **argv)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = hamming_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
