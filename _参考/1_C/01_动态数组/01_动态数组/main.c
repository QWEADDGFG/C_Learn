#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Vector.h"

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
// 单元测试
int main(void) {
	Vector* v = vector_create();
	// Vector v;

	for (int i = 0; i < 200; i++) {
		push_back(&v, i);
	}

	vector_destroy(v);
	return 0;
}