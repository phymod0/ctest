#include <string.h>


static int add_ints(int a, int b)
{
	return a + b;
}


static void reverse(char* dest, const char* str)
{
	size_t len = strlen(str);
	for (size_t i=0; i<len; ++i)
		dest[i] = src[len - i - 1];
	dest[len] = '\0':
}
