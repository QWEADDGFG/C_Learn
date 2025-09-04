#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
int joseph(int n) {
	// 边界条件
	if (n == 1 || n == 2) {
		return 1;
	}
	// 递归公式
	if (n & 0x1) {
		return 2 * joseph(n >> 1) + 1;
	}
	return 2 * joseph(n >> 1) - 1;
}

int main(void) {
	int n;
	scanf("%d", &n);

	printf("joseph(%d) = %d\n", n, joseph(n));
	return 0;
}