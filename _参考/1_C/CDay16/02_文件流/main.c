#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	// 1. 打开文件流
	FILE* stream = fopen("a.txt", "a");
	if (stream == NULL) {
		fprintf(stderr, "Open a.txt failed\n");
		exit(1);
	}

	// 2. 读写文件 (统计，转换，加密，解密...)
	
	// 3. 关闭文件流
	fclose(stream);
	return 0;
}