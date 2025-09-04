#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
/**********************************************************************
 *                          COMMENT                                   *
 ********************************************************************/
int bsearch(int arr[], int left, int right, int key) {
	// 边界条件
	if (left > right) return -1;
	// 递归公式
	int mid = left + (right - left >> 1);	// 注意事项
	int cmp = key - arr[mid];

	if (cmp < 0) return bsearch(arr, left, mid - 1, key);
	if (cmp > 0) return bsearch(arr, mid + 1, right, key);
	return mid;
}

int binary_search1(int arr[], int n, int key) {
	// 闭区间：[0, n-1]
	return bsearch(arr, 0, n - 1, key);
}

/************************************************************/
/*                      循环                                */
/************************************************************/
int binary_search2(int arr[], int n, int key) {
	int left = 0, right = n - 1;

	while (left <= right) {	// 注意事项1
		int mid = left + (right - left >> 1);	// 注意事项2

		int cmp = key - arr[mid];
		if (cmp < 0) {
			right = mid - 1;	// 注意事项3
		} else if (cmp > 0) {
			left = mid + 1;		// 注意事项4
		} else {
			return mid;
		}
	}	// left > right
	return -1;
}

// 查找第一个和key值相等的元素
int binary_search3(int arr[], int n, int key) {
	int left = 0, right = n - 1;

	while (left <= right) {
		int mid = left + (right - left >> 1);

		int cmp = key - arr[mid];
		if (cmp < 0) {
			right = mid - 1;
		} else if (cmp > 0) {
			left = mid + 1;
		} else {
			// [left, right]
			if (mid == left || arr[mid - 1] < key) {
				return mid;
			}
			right = mid - 1;
		}
	}	// left > right
	return -1;
}

// 查找第一个大于等于 key 值的元素
int binary_search4(int arr[], int n, int key) {
	int left = 0, right = n - 1;

	while (left <= right) {
		int mid = left + (right - left >> 1);

		int cmp = arr[mid] - key;
		if (cmp < 0) {
			left = mid + 1;
		} else {
			if (mid == left || arr[mid - 1] < key) {
				return mid;
			}
			right = mid - 1;
		}
	}	// left > right
	return -1;
}

int main(void) {
	int arr[] = { 0, 10, 20, 30, 30, 30, 30, 30, 30, 30, 30, 40, 50, 60, 70, 80, 90 };

	// printf("%d\n", binary_search2(arr, SIZE(arr), 80));
	// printf("%d\n", binary_search2(arr, SIZE(arr), 800));

	// printf("%d\n", binary_search3(arr, SIZE(arr), 30));
	// printf("%d\n", binary_search3(arr, SIZE(arr), 300));

	printf("%d\n", binary_search4(arr, SIZE(arr), 30));		// 3
	printf("%d\n", binary_search4(arr, SIZE(arr), 15));		// 2 
	printf("%d\n", binary_search4(arr, SIZE(arr), -100));	// 0
	printf("%d\n", binary_search4(arr, SIZE(arr), 100));	// -1

	return 0;
}