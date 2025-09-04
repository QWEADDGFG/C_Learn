#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
/*
	Fibnacci(0) = 0;
	Fibnacci(1) = 1;
	Fibnacci(n) = Fibnacci(n-1) + Fibnacci(n-2);  (n >= 2)
*/

// 教训：具有递归结构的问题，不一定要用递归求解。(存在大量重复计算)
// 指数级别
long long fib1(int n) {
	if (n == 0 || n == 1) {
		return n;
	}
	return fib1(n - 1) + fib1(n - 2);
}

// O(n)
long long fib2(int n) {
	long long a = 0;
	long long b = 1;

	// 循环不变式：每次进入循环体之前都成立的条件。
	// fib(i) 未求解
	for (int i = 2; i <= n; i++) {
		long long t = a + b;
		a = b;
		b = t;
	} // i == n + 1, fib(i)未求解
	// 循环不变式也成立！

	return b;
}

int main(void) {
	// 1, 1, 2, 3, 5, 8, 13, 21, 34
	int n = 60;
	// printf("fib1(%d) = %lld\n", n, fib1(n));
	printf("fib2(%d) = %lld\n", n, fib2(n));
	return 0;
}