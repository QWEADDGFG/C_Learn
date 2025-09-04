#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE(a) (sizeof(a) / sizeof(a[0]))

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int* foo(void) {
	int arr[] = { 1, 2, 3, 4 };
	return &arr[1];
}

int main(void) {
	int* p = foo();
	printf("*p = %d\n", *p);
	printf("*p = %d\n", *p);
	return 0;
}