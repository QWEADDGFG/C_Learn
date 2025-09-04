#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//#define DIAMOND 0
//#define CLUB	1
//#define HEART	2
//#define SPADE	3

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

// typedef int Suit;
typedef enum  {
	// 罗列枚举值
	DIAMOND,	// 0
	CLUB = 4,
	HEAET = 10,
	SPADE
} Suit;

int main(void) {
	
	// Suit suit = DIAMOND;
	Suit suit1 = DIAMOND;
	Suit suit2 = CLUB;
	Suit suit3 = HEAET;
	Suit suit4 = SPADE;

	return 0;
}