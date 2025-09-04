#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

void foo(void) {
	printf("Begin\n");
	printf("I love liuyifei\n");
	printf("End\n");
}

int main(void) {
	printf("Hello world\n");

	for (int i = 0; i < 10; i++) {
		printf("I love xixi\n");
	}

	foo();

	printf("Hello kitty");
	return 0;
}