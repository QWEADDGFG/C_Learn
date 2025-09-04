#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

// 二进制表示：
bool isOdd(int n) {
	// return n % 2 == 1;
	// return n % 2 != 0;
	return n & 0x1;		// 掩码(mask)
}

bool isPowerof2(int n) {
	// n > 0
	//while ((n & 0x1) == 0) {
	//	n >>= 1;
	//}
	//return n == 1;

	// 2的幂,二进制表示

	return (n & n - 1) == 0;
}

int main(void) {
	printf("isOdd(-1) = %s\n", isOdd(-1) ? "true" : "false");
	// C语言中的 % 运算符和数学上的 mod 不一样。
	// 余数的符号和被除数的符号一致。
	// int i = -1 % 2;	// -1
	return 0;
}