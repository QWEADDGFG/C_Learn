#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
/*
j
*/
int main(void) {
	// printf("a = %d, b = %d\n", a, b);
	//int a = 4;
	//// printf("a = %d, b = %d\n", a, b);
	//{
	//	// printf("a = %d, b = %d\n", a, b);
	//	int b = 5;
	//	printf("a = %d, b = %d\n", a, b);
	//}
	// printf("a = %d, b = %d\n", a, b);
	// printf("global = %d\n", global);

	return 0;
}

int global = 100;

void foo(void) {
	printf("global = %d\n", global);
}

void bar(void) {
	printf("global = %d\n", global);
}