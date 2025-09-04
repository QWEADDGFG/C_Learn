#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

void foo(void) {
	static int i = 1;
	printf("&i = %p, i = %d\n", &i, i++);
	foo();
}

long long next_fib(void) {
	// 存储上一次函数调用的状态
	static long long a = 0;
	static long long b = 1;

	long long t = a + b;
	a = b;
	b = t;

	return a;
}

int main(void) {
	// foo();
	// Fibnacii: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
	printf("next_fib() = %lld\n", next_fib());	// 1
	printf("next_fib() = %lld\n", next_fib());	// 1
	printf("next_fib() = %lld\n", next_fib());	// 2
	printf("next_fib() = %lld\n", next_fib());	// 3
	printf("next_fib() = %lld\n", next_fib());	// 5
	return 0;
}