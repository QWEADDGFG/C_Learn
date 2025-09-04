#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

// 函数的功能应该越单一越好：高内聚低耦合
//void is_prime(int n) {
//	int rt = sqrt(n);	// square root
//	for (int i = 2; i <= rt; i++) {
//		if (n % i == 0) {
//			printf("Not prime\n");
//			return;
//		}
//	}
//	printf("Prime\n");
//}

bool is_prime(int n) {
	int rt = sqrt(n);	// square root
	for (int i = 2; i <= rt; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int main(void) {
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);

	if (is_prime(n)) {
		printf("Prime\n");
	} else {
		printf("Not prime\n");
	}
	return 0;
}