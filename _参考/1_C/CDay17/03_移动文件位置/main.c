#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

char* readFile(const char* path) {
	// 1. 打开文件
	FILE* stream = fopen(path, "rb");
	if (!stream) {
		fprintf(stderr, "Open %s failed\n", path);
		exit(1);
	}

	// 2. 确定文件大小
	fseek(stream, 0, SEEK_END);
	long n = ftell(stream);
	char* content = malloc(n + 1);	// 1 for '\0'

	// 3. 读文件内容，填充content数组
	rewind(stream);	// 回到文件开头
	int bytes = fread(content, 1, n, stream);
	content[bytes] = '\0';

	// 4. 关闭文件
	fclose(stream);
	return content;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}

	char* content = readFile(argv[1]);

	// ...

	free(content);
	return 0;
}