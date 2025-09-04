#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int sum_array(int arr[], int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		// sum += *(arr + i);
		// sum += arr[i];
		sum += i[arr];
	}
	return sum;
}

int main(void) {
	// 1. 指针处理数组
	//int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };	// 初始化语句
	//
	//int sum = 0;
	//int* p = &arr[0];
	//while (p < &arr[10]) {
	//	sum += *p++;
	//}
	//printf("sum = %d\n", sum);
	
	// 2. 在必要的时候，数组可以退化成指向它索引为0元素的指针
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//int sum = 0;
	//for (int* p = arr; p < arr + 10; p++) {
	//	sum += *p;
	//}
	//printf("sum = %d\n", sum);

	// 3. 指针也支持取下标运算。
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//int* p = arr;
	//int sum = 0;
	//for (int i = 0; i < 10; i++) {
	//	sum += p[i];
	//}
	int sum = sum_array(arr, SIZE(arr));

	printf("sum = %d\n", sum);

	return 0;
}