#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	double init_balance;
	printf("Enter initial balance: ");
	scanf("%lf", &init_balance);

	int rate;
	printf("Enter interest rate: ");
	scanf("%d", &rate);

	int years;
	printf("Enter number of years: ");
	scanf("%d", &years);

	printf("\nYears  ");
	double balances[5];
	for (int i = 0; i < 5; i++) {
		balances[i] = init_balance;
		printf("%4d%%  ", rate + i);
	}
	printf("\n");
	
	for (int year = 1; year <= years; year++) {
		printf("%3d    ", year);
		for (int i = 0; i < 5; i++) {
			balances[i] += balances[i] * ((rate + i) / 100.0);
			printf("%7.2lf", balances[i]);
		}
		printf("\n");
	}

	return 0;
}