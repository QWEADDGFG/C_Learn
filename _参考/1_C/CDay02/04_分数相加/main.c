#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SWAP(a, b) {	\
	int t = a;			\
	a = b;				\
	b = t;				\
}						

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
// Q: 如何求两个整数的最大公约数

// gcd(x, 0) = x 
// x = x * 1;
// 0 = x * 0;

// a = b * q + r ( a >= b, 0 <= r < b)
// gcd(a, b) = gcd(b, r) = ... = gcd(d, 0) = d

// greatest common divisor
int gcd(int a, int b) {
	if (a < b) {
		SWAP(a, b);
	}
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	} // b == 0
	return a;
}


// 代码即注释，只在必要的时候写注释。
int main(void) {
	int num1, denom1;
	printf("Enter first fraction: ");
	scanf("%d/%d", &num1, &denom1);

	int num2, denom2;
	printf("Enter second fraction: ");
	scanf("%d/%d", &num2, &denom2);

	int result_num = num1 * denom2 + num2 * denom1;
	int result_denom = denom1 * denom2;
	int divisor = gcd(result_num, result_denom);

	if (divisor == result_denom) {
		printf("The sum is %d\n", result_num / divisor);
	} else {
		printf("The sum is %d/%d\n", result_num / divisor, result_denom / divisor);
	}

	return 0;
}