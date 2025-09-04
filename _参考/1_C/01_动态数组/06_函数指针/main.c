#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

// 语法： (How)
//	  变量声明：int (*p)(int, int);
//    值	     ：foo, &foo
//    通过函数指针调用函数： p(a, b); (*p)(a, b);



int add(int a, int b) {
	printf("add(%d, %d) = %d\n", a, b, a + b);
	return a + b;
}

int mul(int a, int b) {
	printf("mul(%d, %d) = %d\n", a, b, a * b);
	return a * b;
}

int main(void) {
	// 声明函数指针变量，并赋值
	int (*p1)(int, int) = add;	
	int (*p2)(int, int) = &mul;

	// 通过函数指针调用函数
	p1(3, 4);		
	(*p2)(3, 4);
	return 0;
}