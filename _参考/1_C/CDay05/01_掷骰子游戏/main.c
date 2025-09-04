#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
// 1. 函数的功能应该越单一越好。
// 2. C语言是面向过程(函数)的语言: 函数是C语言的基本构建组件。
//                               C语言程序本质上就是函数之间的相互调用。

int roll_dices(void) {
	int a = rand() % 6 + 1;
	int b = rand() % 6 + 1;
	printf("You rolled: %d\n", a + b);
	return a + b;
}

bool play_game(void) {
	int point = roll_dices();
	if (point == 7 || point == 11) {
		printf("You win!\n");
		return true;
	}
	if (point == 2 || point == 3 || point == 12) {
		printf("You lose!\n");
		return false;
	}
	// 进入第二个阶段
	printf("Your point is %d\n", point);
	for (;;) {
		int tally = roll_dices();
		if (tally == point) {
			printf("You win!\n");
			return true;
		}
		if (tally == 7) {
			printf("You lose!\n");
			return false;
		}
	}
}

int main(void) {
	int wins = 0, losses = 0;

	// seed -> n1 -> n2 -> ...
	srand(time(NULL));

	char again;
	do {
		play_game() ? wins++ : losses++;
		
		printf("\nPlay again? ");
		scanf(" %c", &again);
		// 跳过这一行剩余的字符
		while (getchar() != '\n')
			;
	} while (again == 'y' || again == 'Y');
	
	printf("\nWins:%d, Losses:%d\n", wins, losses);
	return 0;
}