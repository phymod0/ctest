#include "ctest.h"

#include <time.h>
#include <stdio.h>


#define PSTDOUT(...) fprintf(stdout, __VA_ARGS__)
#define PSTDERR(...) fprintf(stderr, __VA_ARGS__)


typedef struct test_result {
	const char* test_name;
	unsigned long long passed, total;
	const char* failed_checknames[MAX_CHECKNAMES_PER_UNIT];
	unsigned long long n_failed_names;
} test_result_t;


static void print_test_results(test_result_t* result)
{
	/* TODO: Warnings enabled */
	const char* status = result->passed == result->total ? "PASS" : "FAIL";
	const char* test_name = result->test_name;
	if (!test_name)
		test_name = "(unnamed)";
	PSTDOUT("[%s] Test %s: %d/%d checks passed", status, test_name,
		result->passed, result->total);
	if (result->n_failed_names == 0) {
		PSTDOUT(".\n");
		return;
	}
	PSTDOUT(" (failed checks: %s", result->failed_checknames[0]);
	for (int i=1; i<result->n_failed_names; ++i)
		PSTDOUT(", %s", result->failed_checknames[i]);
	PSTDOUT(").\n");
}


static bool run_single_test(test_t test)
{
	srand(time(NULL));
	test_result_t result = {0};

	test(&result);
	print_test_results(&result);

	return result.passed == result.total;
}


void test_acheck(test_result_t* result, bool check)
{
	++result->total;
	if (check)
		++result->passed;
}


void test_check(test_result_t* result, const char* name, bool check)
{
	++result->total;
	if (check) {
		++result->passed;
		return;
	}
	if (result->n_failed_names < MAX_CHECKNAMES_PER_UNIT)
		result->failed_checknames[result->n_failed_names++] = name;
	else
		PSTDERR("Cannot record check failure name (buffer full).\n");
}


void test_name(test_result_t* result, const char* name)
{
	result->test_name = name;
}


int test_run(const test_t* tests, size_t n_tests)
{
	size_t n_passed = 0;
	PSTDOUT("--------------------------------------------------------\n");
	PSTDOUT("****************** RUNNING TEST CASES ******************\n");
	for (size_t i=0; i<n_tests; ++i)
		if (run_single_test(tests[i]))
			++n_passed;
	PSTDOUT("*********************** ALL DONE ***********************\n");
	bool passed = n_passed == n_tests;
	PSTDOUT("[%s] %d/%d test cases passed.\n",
		passed ? "PASS" : "FAIL", n_passed, n_tests);
	PSTDOUT("--------------------------------------------------------\n");
	return (int)(n_tests - n_passed);
}


#undef PSTDERR
#undef PSTDOUT


#undef ERROR
