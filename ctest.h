#ifndef TEST
#define TEST


#include <stdlib.h>


#define MAX_CHECKNAMES_PER_UNIT 256


struct test_result;
typedef struct test_result test_result_t;

typedef void (*test_t)(test_result_t* result);


void test_name(test_result_t* result, const char* name);
void test_anonymous_check(test_result_t* result, bool check);
void test_check(test_result_t* result, const char* name, bool check);
void test_run(const test_t* tests, size_t n_tests);


#define TEST_AUTONAME(result) test_name(result, __func__)

#define TEST_RUN(...) {							\
	int (*test_fns[])(void) = {__VA_ARGS__};			\
	const size_t n_tests = sizeof test_fns / sizeof test_fns[0];	\
	test_run(test_fns, n_tests);					\
}


#endif /* TEST */
