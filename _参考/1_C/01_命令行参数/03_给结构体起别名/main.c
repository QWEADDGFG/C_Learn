#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
// typedef 类型 别名;
// 匿名结构体：没有标签的结构体类型
//typedef struct  {
//	int id;
//	char name[25];
//	char gender;
//	int chinese;
//	int math;
//	int english;
//} Student;

// 请不要给指针类型起别名！
typedef struct student {
	int id;
	char name[25];
	char gender;
	int chinese;
	int math;
	int english;
} Student, *pStudent;

int main(void) {
	// Student s1 = { 1, "xixi", 'f', 100, 100, 100 };
	// Student s2 = { 2, "peanut", 'm'};

	pStudent s1;
	Student* s2;
	return 0;
}