#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// void* p = malloc(sizeof(int) * 100);
	//if (p == NULL) {
	//	printf("Error: malloc failed in main\n");
	//	exit(1);
	//}

	//if (!p) {	// p不存在
	//	printf("Error: malloc failed in main\n");
	//	exit(1);
	//}

	//*p;

	//for (int i = 0; i < 100; i++) {
	//	p[i] = i;
	//}
	
	int* p = calloc(100, sizeof(int));
	if (!p) {
		printf("Error: malloc failed\n");
	}

	return 0;
}