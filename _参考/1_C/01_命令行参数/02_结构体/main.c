#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
// 定义结构体类型, 自定义类型
struct student {
	int id;
	char name[25];
	char gender;
	int chinese;
	int math;
	int english;
};

void print_stu_info(const struct student* s) {
	//printf("%d %s %c %d %d %d\n",
	//	(*s).id,
	//	(*s).name,
	//	(*s).gender,
	//	(*s).chinese,
	//	(*s).math,
	//	(*s).english);

	// 语法糖：->
	printf("%d %s %c %d %d %d\n",
		s->id,
		s->name,
		s->gender,
		s->chinese,
		s->math,
		s->english);
}

int main(void) {
	// 声明并初始化变量
	struct student s1 = {1, "xixi", 'F', 100, 100, 100};
	struct student s2 = {2, "peanut", 'M'};

	// 1. 获取成员：.
	//printf("%d %s %c %d %d %d\n",
	//	s1.id,
	//	s1.name,
	//	s1.gender,
	//	s1.chinese,
	//	s1.math,
	//	s1.english);

	// 2. 赋值: 结构体变量的复制
	// 往往更习惯传递一个指向结构体变量的指针
	// s2 = s1;

	// 3. 右箭头运算符 ->
	print_stu_info(&s1);

	return 0;
}