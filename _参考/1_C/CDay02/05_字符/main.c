#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// printf("%c\n", 'A');
	// printf("%c", '\a');
	// printf("%c\n", '\101');
	// printf("%c\n", '\x41');

	//char ch;
	//int i;

	//i = 'a';				/* i is now 97 */
	//ch = 65;				/* ch is now 'A' */
	//ch = ch + 1;			/* ch is now 'B' */
	//ch++;					/* ch is now 'C' */

	// char c = 'a' / 'b' + 'c';

	// char c = 'A';
	// printf("%c", c);
	// char c1, c2;
	// scanf("%c %c", &c1, &c2);

	// char c = 'A';
	// putchar(c);

	// char c = getchar();
	// char c1, c2;
	// c1 = getchar();

	// 跳过这一行剩余的字符
	// while (getchar() != '\n')
	//	;

	// c2 = getchar();

	int length = 0;
	printf("Enter a message: ");
	while (getchar() != '\n')
		length++;

	printf("Your message was %d character(s) long.", length);
	return 0;
}