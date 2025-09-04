#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(int argc, char* argv[]) {
	// argc: argument count, 命令行参数的个数
	// argv: argument vector, 命令行参数，字符串
	//		 第一个参数是可执行程序的路径

	// printf("argc = %d\n", argc);
	// 打印所有的命令行参数
	//for (int i = 0; i < argc; i++) {
	//	puts(argv[i]);
	//}

	// 命令行参数的转换
	// xxx.exe n f
	int n;
	float f;

	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%f", &f);

	return 0;
}