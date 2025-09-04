#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/


//void foo(int* p) {
//	*p *= 2;
//}

void min_max(const int arr[], int n, int* pmin, int* pmax) {
	*pmin = arr[0];
	*pmax = arr[0];
	
	for (int i = 1; i < n; i++) {	
		if (arr[i] < *pmin) {
			*pmin = arr[i];
		} else if (arr[i] > *pmax) {
			*pmax = arr[i];
		}
	}
}

int main(void) {
	int arr[] = { 9, 5, 2, 7, 1, 3, 4, 0, 6, 8 };
	int min, max;
	min_max(arr, SIZE(arr), &min, &max);
	printf("min = %d, max = %d\n", min, max);
	return 0;
}