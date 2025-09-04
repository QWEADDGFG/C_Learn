#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

void hanoi(int n, char start, char middle, char target) {
	// 边界条件
	if (n == 1) {
		printf("%c -> %c\n", start, target);
		return;
	}
	// 递归公式
	// 将上面n-1个盘子从start,经过target，移动到middle上
	hanoi(n - 1, start, target, middle);
	// 将最大的盘子从start直接移动到target上
	printf("%c -> %c\n", start, target);
	// 将上面n-1个盘子从middle,经过start，移动到target上
	hanoi(n - 1, middle, start, target);
}

int main(void) {
	int n;
	scanf("%d", &n);

	// 计算最少需要移动的次数
	// S(n) + 1 = 2S(n-1) + 2
	// S(1) = 1;
	// S(n) + 1 = 2 ^ n
	// S(n) = 2 ^ n - 1;

	printf("Total steps: %lld\n", (1LL << n) - 1);
	// 打印移动步骤
	hanoi(n, 'A', 'B', 'C');
	return 0;
}