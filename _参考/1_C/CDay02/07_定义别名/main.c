#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

typedef long Quantity;

int main(void) {
	Quantity q1 = 100000;
	Quantity q2 = 200000;
	Quantity q3 = q1 + q2;

	int a = 3, b = 4;

	char c1 = 'A', c2 = 'B';

	printf("q3 = %d\n", q3);
	return 0;
}