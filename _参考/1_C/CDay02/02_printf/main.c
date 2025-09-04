#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	//int i, j;
	//float x, y;

	//i = 10;
	//j = 20;
	//x = 43.2892f;
	//y = 5527.0f;
	//// 格式串
	//printf("i = %d, j = %d, x = %f, y = %f\n", i, j, x, y);

	int i = 40;
	float x = 839.21f;

	printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
	printf("|%f|%10f|%10.2f|%-10.2f|\n", x, x, x, x);
	return 0;
}