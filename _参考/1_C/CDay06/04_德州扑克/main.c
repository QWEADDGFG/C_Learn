#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

void read_cards(void);
void analyze_hand(void);
void print_result(void);

int main(void) {
	for (;;) {
		// 读取用户输入 (一副手牌)
		read_cards();
		// 分析手牌 (计算)
		analyze_hand();
		// 输出结果
		print_result();
	}
	return 0;
}

int num_in_suit[4];		// 每个花色有几张
int num_in_rank[13];	// 每个点数有几张
void read_cards(void) {
	// 初始化
	bool bad_card = false;
	bool in_hand[4][13] = { false };

	for (int i = 0; i < 4; i++) {
		num_in_suit[i] = 0;
	}
	for (int j = 0; j < 13; j++) {
		num_in_rank[j] = 0;
	}

	// 读取用户输入
	int cards_read = 0;
	while (cards_read < 5) {
		char c = getchar();
		int rank;	
		switch (c) {
		case '0':	exit(0);
		case '2':	rank = 0;			break;
		case '3':	rank = 1;			break;
		case '4':	rank = 2;			break;
		case '5':	rank = 3;			break;
		case '6':	rank = 4;			break;
		case '7':	rank = 5;			break;
		case '8':	rank = 6;			break;
		case '9':	rank = 7;			break;
		case 't': case 'T': rank = 8;	break;
		case 'j': case 'J': rank = 9;	break;
		case 'q': case 'Q': rank = 10;	break;
		case 'k': case 'K': rank = 11;	break;
		case 'a': case 'A': rank = 12;	break;
		default:	bad_card = true;	break;
		}

		c = getchar();
		int suit;
		switch (c) {
		case 'd': case 'D':	suit = 0;	break;
		case 'c': case 'C':	suit = 1;	break;
		case 'h': case 'H':	suit = 2;	break;
		case 's': case 'S':	suit = 3;	break;
		default:	bad_card = true;	break;
		}

		// 读取剩余的字符
		while ((c = getchar()) != '\n') {	
			if (c != ' ' && c != '\t') {
				bad_card = true;
			}
		}

		// (rank, suit) -> 扑克牌
		if (bad_card) {
			printf("Bad card; ignored.\n");
		} else if (in_hand[suit][rank]) {
			printf("Duplicate card; ignored.\n");
		} else {
			cards_read++;
			in_hand[suit][rank] = true;
			num_in_suit[suit]++;
			num_in_rank[rank]++;
		}
	}
}

bool straight, flush, four, three;
int pairs;	/* 0, 1, 2*/

void analyze_hand(void) {

}

void print_result(void) {

}