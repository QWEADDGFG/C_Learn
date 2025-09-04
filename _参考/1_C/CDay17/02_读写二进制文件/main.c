#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BUFSIZE 4096
/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(int argc, char* argv[]) {
	// 1. 校验参数
	if (argc != 3) {
		fprintf(stderr, "Usage: %s src dst\n", argv[0]);
		exit(1);
	}


	// 2. 打开文件
	FILE* src = fopen(argv[1], "rb");
	if (!src) {
		fprintf(stderr, "Open %s failed\n", argv[1]);
		exit(1);
	}

	FILE* dst = fopen(argv[2], "wb");
	if (!dst) {
		fprintf(stderr, "Open %s failed\n", argv[2]);
		fclose(src);
		exit(1);
	}
	// 3. 读写文件 (复制)
	char buffer[BUFSIZE];
	int bytes;
	while ((bytes = fread(buffer, 1, BUFSIZE, src)) > 0) {
		fwrite(buffer, 1, bytes, dst);
	}

	// 4. 关闭文件
	fclose(src);
	fclose(dst);
	return 0;
}