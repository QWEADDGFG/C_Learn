#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// int* p, q;
	//int a;
	//int* p;
	//int[10] arr;

	// int a, *p, arr[10];

	/* 两个基本操作 */
	//int i = 1;
	//int* p = &i;

	//printf("*p = %d\n", *p);
	//*p = 10;
	//printf("i = %d\n", i);

	/* 野指针 */
	// int* p;
	//int* p = 0xCAFEBABE;
	//printf("p = %p\n", p);
	//printf("*p = %d\n", *p);

	/* 给指针变量赋值 */
	int i = 10, j = 20;
	int* p = &i;
	int* q = &j;

	// p = q;
	*p = *q;

	printf("*p = %d, *q = %d\n", *p, *q);	// 20, 20
	printf("i = %d, j = %d\n", i, j);		// 20, 20

	return 0;
}