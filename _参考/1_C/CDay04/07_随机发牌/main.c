#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// 伪随机数生成
	// seed -> n1 -> n2 -> n3 -> ...
	// srand(100);	// 设置随机种子
	
	// 根据时间设置随机种子, 往往随机种子只需设置一次
	//srand(time(NULL));	
	//printf("rand() = %d\n", rand());
	//printf("rand() = %d\n", rand());
	//printf("rand() = %d\n", rand());

	int cards;
	printf("Enter number of cards in hand: ");
	scanf("%d", &cards);
	// 校验...

	// 随机发牌
	const char suits[] = { 'S', 'H', 'C', 'D' };
	const char ranks[] = { '2', '3', '4', '5', '6', '7', '8',
						  '9', 'T', 'J', 'Q', 'K', 'A' };
	bool in_hand[4][13] = { false };

	srand(time(NULL));
	printf("Your hand: ");
	while (cards) {
		int i = rand() % 4;
		int j = rand() % 13;
		if (!in_hand[i][j]) {
			in_hand[i][j] = true;
			cards--;
			printf("%c%c ", ranks[j], suits[i]);
		}
	} // cards == 0
	printf("\n");

	return 0;
}