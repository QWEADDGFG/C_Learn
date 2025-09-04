#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int lastSetBit(int n) {
	//int x = 0x1;	// 1, 2, 4, ...
	//while ((n & x) == 0) {
	//	x <<= 1;
	//} // (n & x) != 0
	//return x;

	return n & -n;
}

int findSingleNum(int nums[], int n) {
	int singleNum = 0;	// TODO: singleNUm = ?; 
	for (int i = 0; i < n; i++) {
		singleNum ^= nums[i];
	}
	return singleNum;
}


int main(void) {
	// int n = 24;
	// printf("%d\n", lastSetBit(n));

	// int a = 3, b = 4;

	//printf("a = %d, b = %d\n", a, b);
	//a = a + b;	// a1 = a0 + b0, b1 = b0
	//b = a - b;	// a2 = a0 + b0, b2 = a1 - b1 = a0
	//a = a - b;	// a3 = a2 - b2 = b0, b3 = a0
	//printf("a = %d, b = %d\n", a, b);

	//printf("a = %d, b = %d\n", a, b);
	//a = a ^ b;	// a1 = a0 ^ b0, b1 = b0
	//b = a ^ b;	// a2 = a0 ^ b0, b2 = a1 ^ b1 = a0
	//a = a ^ b;	// a3 = a2 ^ b2 = b0, b3 = a0
	//printf("a = %d, b = %d\n", a, b);

	// int nums[] = { 1, 2, 4, 1, 2 };
	// printf("singleNum = %d\n", findSingleNum(nums, 5));

	int nums[] = { 1, 2, 3, 5, 2, 1 };

	int xor = 0;
	for (int i = 0; i < 6; i++) {
		xor ^= nums[i];
	}	// xor = a ^ b;	(xor != 0)

	int lsb = xor & (-xor);	// a和b在这一位上不同。

	// 根据这一位将所有元素分类
	int a = 0, b = 0;
	for (int i = 0; i < 6; i++) {
		if (nums[i] & lsb) {
			// 为 1
			a ^= nums[i];
		} else {
			// 为 0
			b ^= nums[i];
		}
	}

	printf("a = %d, b = %d\n", a, b);
	return 0;
}