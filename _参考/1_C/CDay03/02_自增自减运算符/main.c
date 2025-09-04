#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// ++i: 表达式的值i+1，副作用是i自增。
	//int i = 1;
	//printf("i is %d\n", ++i);	// 2
	//printf("i is %d\n", i);		// 2

	// i++: 表达式的值i，副作用是i自增
	//int i = 1;
	//printf("i is %d\n", i++);	// 1
	//printf("i is %d\n", i);		// 2

	int i, j, k;
	i = 1;
	j = 2;
	k = ++i + j++;
	printf("i = %d, j = %d, k = %d\n", i, j, k);	// 2, 3, 4
	return 0;
}