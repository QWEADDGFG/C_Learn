#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAXLINE 128

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

size_t my_strlen(const char* s) {
	// 版本一
	//size_t n = 0;
	//while (*s != '\0') {
	//	n++;
	//	s++;
	//}  // *s == '\0'
	//return n;

	const char* p = s;
	while (*p) {
		p++;
	} 
	return p - s;
}

char* my_strcpy(char* s1, const char* s2) {
	// 版本一
	//while (*s2 != '\0') {
	//	*s1 = *s2;	// 复制
	//	s1++;
	//	s2++;
	//}	// *s2 == '\0';
	//*s1 = '\0';
	//return s1;

	// 版本二
	char* p = s1;
	while (*s1++ = *s2++)	// *s2
		;	// 复制
	// *s2 == '\0'
	return p;
}

// count: 最多复制count个字符
char* my_strncpy(char* s1, const char* s2, size_t count) {
	char* p = s1;
	while ((count-- > 0) && (*s1++ = *s2++))
		;
	// count == 0 || *s2 == '\0'
	return p;
}

char* my_strcat(char* s1, const char* s2) {
	// 1. 搜索s1的末尾
	char* p = s1;
	while (*s1) {
		s1++;
	}	// *s1 == '\0'
	// 2. 复制s2
	while (*s1++ = *s2++)
		;
	return p;
}

// count: 最多拼接count个字符
char* my_strncat(char* s1, const char* s2, size_t count) {
	// 1. 搜索s1的末尾
	char* p = s1;
	while (*s1) {
		s1++;
	}	// *s1 == '\0'
	// 2. 复制s2
	while ((count--) && (*s1++ = *s2++))
		;
	return p;
}

int my_strcmp(const char* s1, const char* s2) {
	while (*s1 && *s2) {
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
		s1++;
		s2++;
	} // *s1 == '\0' || *s2 == '\0'
	return *s1 - *s2;
}

int main(void) {
	// printf("my_strlen(\"ABC\") = %d\n", my_strlen("ABC"));	// 3
	// printf("my_strlen(\"\") = %d\n", my_strlen(""));	   // 0

	// char s1[MAXLINE];	// s1是一个数组
	// my_strcpy(s1, "Hello world");
	// my_strncpy(s1, "Hello world", MAXLINE);	// 1 for '\0'
	// s1[MAXLINE - 1] = '\0';

	// 字符串的拼接
	// strcat = string + concatenate
	// char s1[MAXLINE] = "Hello ";	// s1是一个数组
	// my_strcat(s1, "world\n");
	// strncat(s1, "world\n", MAXLINE - strlen(s1) - 1);	// 1 for '\0'
	// s1[MAXLINE - 1] = '\0';

	// 字符串的比较：strcmp
	// int strcmp(const char* s1, const char* s2);
	// 返回值：>0: s1 > s2
	//        =0: s1 == s2
	//        <0: s1 < s2
	// 比较规则：字典序 (ASCII)

	printf("my_strcmp(%s, %s) = %d\n", "ABC", "abc", my_strcmp("ABC", "abc")); // < 0
	printf("my_strcmp(%s, %s) = %d\n", "ABC", "ABD", my_strcmp("ABC", "ABD")); // < 0
	printf("my_strcmp(%s, %s) = %d\n", "ABC", "ABCD", my_strcmp("ABC", "ABCD")); // < 0
	return 0;
}