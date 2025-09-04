#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	//char c = 'A';
	//short s = 100;
	//int i = 1000;
	//long l = 10000;
	//long long ll = 1000000;

	//float f = 3.14f;
	//double d = 5.67;

	//int i = -1;
	//unsigned int u = 100;

	//if (u > i) {
	//	printf("Greater!\n");
	//} else {
	//	printf("Less!\n");
	//}

	// float f = 3.14f;
	// ...

	// int i = (int)f; /* 注意：这里发生了转换，可能会出现问题 */

	// float quotient;
	// int dividend = 3;
	// int divisor = 4;

	// quotient = dividend / divisor;
	// quotient = (float)dividend / divisor;

	long long millisPerDay = 24 * 60 * 60 * 1000;
	long long nanosPerDay = (long long)24 * 60 * 60 * 1000 * 1000 * 1000;

	printf("nanosPerDay / millisPerDay = %lld\n", nanosPerDay / millisPerDay);
	return 0;
}