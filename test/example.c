#include "example.c"

#include "ctest.h"


TEST_DEFINE(test_add_ints, res)
{
	TEST_AUTONAME(res);
	int a = 2, b = 3, sum = a + b;

	test_check(res, "Addition succeeded", add_ints(a, b) == sum);
	test_acheck(res, a*b == 5);
}

TEST_DEFINE(test_str_reverse, res)
{
	test_name(res, "ReverseTest");

	char arr[] = "Hello world!";
	char rev[sizeof arr];
	reverse(rev, arr);

	bool equal = true;
	size_t len = (sizeof arr) - 1;
	for (size_t i=0; i<len; ++i)
		if (arr[i] != rev[len-i-1]) {
			equal = false;
			break;
		}

	test_check(res, "Successfully reversed", equal);
}


TEST_START
(
	test_add_ints,
	test_str_reverse,
)
