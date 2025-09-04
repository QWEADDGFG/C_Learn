#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	int arr[4] = {1, 2, 3, 4}; // 声明数组
	int arr2[] = {1, 2, 3, 4};	// {1, 2, 3, 4}: 数组的初始化式.
	int arr3[10] = { 1, 2, 3, 4 };

	printf("SIZE(arr) = %d\n", SIZE(arr));
	printf("SIZE(arr2) = %d\n", SIZE(arr2));
	printf("SIZE(arr3) = %d\n", SIZE(arr3));

	// printf("arr[2] = %d\n", arr[2]);

	return 0;
}