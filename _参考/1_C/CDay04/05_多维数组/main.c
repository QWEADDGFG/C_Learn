#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	//int matrix[3][7];

	// printf("SIZE(matrix) = %d\n", SIZE(matrix));	// 3
	// printf("SIZE(matrix[0]) = %d\n", SIZE(matrix[0]));	// 7

	int matrix1[3][7] = { {1, 2, 3, 4}, {2, 2, 3, 4}, {3, 2, 3, 4} };
	// int matrix2[3][7] = { 1, 2, 3, 4, 2, 2, 3, 4, 3, 2, 3, 4 };
	// int matrix3[3][7] = { 0 };

	// 操作
	matrix1[1][2];
	return 0;
}