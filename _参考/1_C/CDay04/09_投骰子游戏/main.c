#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
int roll_dices(void);
bool play_game(void);

int main(void) {
	int wins = 0, losses = 0;

	char again;
	do {
		play_game() ? wins++ : losses++;
		printf("\nPlay again?");
		// ...
	} while (again == 'y' || again == 'Y');

	printf("\nWins:%d, Losses:%d\n", wins, losses);

	return 0;
}