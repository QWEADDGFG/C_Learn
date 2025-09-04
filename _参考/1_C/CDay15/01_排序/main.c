#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

void insertion_sort(int arr[], int n);
void shell_sort(int arr[], int n);

void print_array(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(void) {
	// int arr[] = { 3, 6, 4, 2, 11, 10, 5 };
	int arr[] = { 16, 1, 45, 23, 99, 2, 18, 67, 42, 10 };
	print_array(arr, SIZE(arr));

	// insertion_sort(arr, SIZE(arr));
	shell_sort(arr, SIZE(arr));

	return 0;
}

/**********************************************************************/
/*                       插入排序                                      */
/**********************************************************************/
void insertion_sort(int arr[], int n) {
	for (int i = 1; i < n; i++) {	// i: 要插入元素的索引
		int value = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > value) {
			arr[j + 1] = arr[j];
			j--;
		}	// j == -1 || arr[j] <= value
		arr[j + 1] = value;

		// print_array(arr, n);
	}
}


/**********************************************************************/
/*                       希尔排序                                      */
/**********************************************************************/
void shell_sort(int arr[], int n) {
	// gap: n/2, n/4, ..., 1, 0
	int gap = n >> 1;
	while (gap) {
		// 组间插入排序 (gap个人轮流抓拍)
		for (int i = gap; i < n; i++) { // 牌堆[gap, n)
			int value = arr[i];
			// 保证手牌有序
			int j = i - gap;
			while (j >= 0 && arr[j] > value) {
				arr[j + gap] = arr[j];
				j -= gap;
			} // j < 0 || arr[j] <= value
			arr[j + gap] = value;
		}
		print_array(arr, n);
		// 缩小gap
		gap >>= 1;
	} // gap == 0
}