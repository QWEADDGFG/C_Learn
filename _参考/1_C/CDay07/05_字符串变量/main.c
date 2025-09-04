#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_LINE 128

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	//char str[] = "Hello world\n";
	//int len = strlen(str);
	//for (int i = 0; i < len; i++) {
	//	char c = str[i];
	//}

	// 声明字符串变量并赋初始值
	// char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'}; // 数组的初始化式
	// char str2[] = "Hello";	// 语法糖："Hello"是数组初始化的简写形式！

	// 建议：1. 如果初始化字符数组，{'H', 'e', 'l', 'l', 'o'};
	//      2. 如果初始化字符串， "Hello"

	// char str[] = "hello";	// 长度为6
	// char str[10] = "hello";	    // {'H', 'e', 'l', 'l', 'o', '\0'};
	// char str[5] = "hello";	    // 长度为5，不表示字符串

	// printf("%s", str);

	// 注意事项
	// char str[] = "hello";	// "hello": 数组的初始化式
	// char* p = "hello";		// "hello": 字符串字面值

	// str[0] = 'H';
	// printf("%s", str);
	//p[0] = 'H';
	//printf("%s", *p);

	//char str[] = "Hello world";
	//printf("%s\n", str);
	//printf("%.5s\n", str);

	//char str[MAX_LINE];
	//scanf("%s", str);	// 不需要加取地址运算符!
	//printf("%s", str);

	//char str[MAX_LINE] = "Hello world";

	//printf("%s\n", str);
	//puts(str);

	char str[MAX_LINE];
	// gets(str);
	fgets(str, MAX_LINE, stdin);
	return 0;


}