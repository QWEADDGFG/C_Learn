#include <stdio.h>

#define FOO(x)	(1 + (x) * (x))

int main(void) {
	printf("10 / FOO(1+2) = %d\n", 10 / FOO(1+2));
	return 0;
}