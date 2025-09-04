#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE(a) (sizeof(a) / sizeof(a[0]))
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
void swap(int a, int b) {
	int t = a;
	a = b;
	b = t;
}


void clear(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}

	//for (int i = 0; i < SIZE(arr); i++) {
	//	arr[i] = 0;
	//}
}

int main(void) {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	clear(arr, 5);

	for (int i = 0; i < SIZE(arr); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}