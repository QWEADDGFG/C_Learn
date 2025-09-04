#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	

	//// 指针加上一个整数，结果还是一个指针
	// int* p = &arr[2];
	//p = p + 3;
	//printf("*p = %d\n", *p);

	// 指针减去上一个整数，结果还是一个指针
	//int* p = &arr[8];
	//p = p - 3;
	//printf("*p = %d\n", *p);

	// 两个指针相减，结果是一个整数
	int* p = &arr[8];
	int* q = &arr[2];
	printf("p - q = %ld\n", p - q);
	printf("q - p = %ld\n", q - p);

	// p + q;
	// p * q;
	// p / q;
	// p % q;
	return 0;
}

