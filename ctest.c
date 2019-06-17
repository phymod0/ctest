#include "test.h"

#include <time.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct test_result {
	char* test_name;
	unsigned long long passed, total;
	char* failed_checknames[MAX_CHECKNAMES_PER_UNIT];
	unsigned long long n_failed_names;
} test_result_t;


static void print_test_results(test_result_t* result)
{
	char* status = result.passed == result.total ? "PASS" : "FAIL";
	fprintf(stderr, "[%s] Test \"%s\": %d/%d checks passed",
		status, result.test_name, result.passed, result.total);
	if (result.n_failed_names == 0) {
		fprintf(stderr, ".\n");
		return;
	}
	fprintf(stderr, " (failed checks: %s", result.failed_checknames[0]);
	for (int i=1; i<result.n_failed_names; ++i)
		fprintf(stderr, ", %s", result.failed_checknames[j]);
	fprintf(stderr, ").\n");
}


static bool run_single_test(test_t* test)
{
	srand(time(NULL));
	test_result_t result;

	test(&result);
	print_test_results(&result);

	return result.passed == result.total;
}


void test_anonymous_check(test_result_t* result, bool check)
{
	++result.total;
	if (check)
		++result.passed;
}


void test_check(test_result_t* result, const char* name, bool check)
{
	++result.total;
	if (check) {
		++result.passed;
		continue;
	}
	if (result.n_failed_names < MAX_CHECKNAMES_PER_UNIT)
		result.failed_checknames[result.n_failed_names++] = name;
	else
		fprintf(stderr, "Cannot record check failure name (full "
			"buffer).\n");
}


void test_name(test_result_t* result, const char* name)
{
	result->test_name = name;
}


void test_run(const test_t* tests, size_t n_tests)
{
	size_t n_passed = 0;
	fprintf(stderr, "------------------------------------------------\n");
	fprintf(stderr, "************** RUNNING TEST CASES **************\n");
	for (size_t i=0; i<n_tests; ++i)
		if (run_single_test(tests[i]))
			++n_passed;
	fprintf(stderr, "******************* ALL DONE *******************\n");
	bool passed = n_passed == n_tests;
	fprintf(stderr, "[%s] %d/%d test cases passed.\n",
		passed ? "PASS" : "FAIL", n_passed, n_tests);
	fprintf(stderr, "------------------------------------------------\n");
}
