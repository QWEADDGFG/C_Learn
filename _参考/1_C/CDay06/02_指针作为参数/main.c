#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

void swap(int* p1, int* p2) {
	int t = *p1; 
	*p1 = *p2;
	*p2 = t;
}

int main(void) {
	int a = 3, b = 4;

	printf("a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);
	return 0;
}