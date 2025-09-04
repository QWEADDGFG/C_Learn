#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

// 10 -> 'A'
// 11 -> 'B'
// ...
// 15 -> 'F'
char digit_to_hex(int digit) {
	return "0123456789ABCDEF"[digit];
}

int main(void) {
	//printf("I love xixi   -- From peanut\n");

	//printf("I love xixi\
 //-- From peanut\n");

	//printf("I love xixi"
	//	   " -- From peanut\n");

	// printf("   *\n");
	// printf("  * *\n");
	// ...
	
	//printf("   *\n"
	//	   "  * *\n"
	//	   " *   *\n");

	// "ABC"[0] = 'a';

	// char* p = "ABC" + 1;
	// printf("%c\n", *p);

	return 0;
}