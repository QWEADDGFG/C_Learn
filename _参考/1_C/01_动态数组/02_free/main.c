#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// 1. double free
	// int* p = malloc(100 * sizeof(int));
	// free(p);	// free(p) 不会改变p的值，只是将p指向的内存空间释放了
	// free(p);

	// 2. use after free
	int* p = malloc(100 * sizeof(int));
	free(p);	// p是悬空指针
	p[0] = 1;	// use after free!

	return 0;
}