#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <errno.h>
#include <string.h>
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// printf("%d\n", errno); // 0: 没有错误
	FILE* stream = fopen("not_exist.txt", "r");

	printf("%d\n", errno);
	printf("%s\n", strerror(errno)); // 错误原因
	perror("fopen");
	return 0;
}