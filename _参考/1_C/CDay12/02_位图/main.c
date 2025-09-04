#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "BitMap.h"

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	BitMap* bm = bitmap_create(100);

	bitmap_set(bm, 9);
	bitmap_set(bm, 5);
	bitmap_set(bm, 2);
	bitmap_set(bm, 7);

	bitmap_set(bm, 120);
	bitmap_set(bm, 128);

	//bitmap_unset(bm, 9);
	//bitmap_unset(bm, 5);
	//bitmap_unset(bm, 2);
	//bitmap_unset(bm, 7);
	//bitmap_unset(bm, 10);

	// printf("bitmap_isset(bm, 7) = %s\n", bitmap_isset(bm, 7) ? "true" : "false");
	// printf("bitmap_isset(bm, 10) = %s\n", bitmap_isset(bm, 10) ? "true" : "false");

	bitmap_clear(bm);
	return 0;
}