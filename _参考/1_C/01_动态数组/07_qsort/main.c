#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
 // 作用：(Why)
 // 1. 函数式编程 (传递函数，返回函数)， 函数指针支持函数式编程
 //    分解任务，解耦合
 // 
 // 2. 编写非常通用的函数 (功能非常强大的函数)

// qsort(void* base, size_t n, size_t size, int (*compare)(const void*, const void*));


typedef struct {
	int id;
	char name[25];
	char gender;
	int chinese;
	int math;
	int english;
} Student;

// 比较规则：按总分从高到低排序；如果总分相同，再分别按语文、数学、英语成绩从大到小排序；
//          如果各科成绩都一样，再按学号从小到大排序。

// <0: p1比p2小
// =0：p1和p2相等
// >0: p1比p2大
int cmp(const void* p1, const void* p2) {
	Student* s1 = p1;
	Student* s2 = p2;

	int total1 = s1->chinese + s1->math + s1->english;
	int total2 = s2->chinese + s2->math + s2->english;
	if (total1 != total2) {
		return total2 - total1;
	}
	if (s1->chinese != s2->chinese) {
		return s2->chinese - s1->chinese;
	}
	if (s1->math != s2->math) {
		return s2->math - s1->math;
	}	
	if (s1->english != s2->english) {
		return s2->english - s1->english;
	}

	return s1->id - s2->id;
}

void print_stu_info(const Student* s) {
	printf("%d %s %c %d %d %d\n",
		s->id,
		s->name,
		s->gender,
		s->chinese,
		s->math,
		s->english);
}

int main(void) {
	Student students[5];
	for (int i = 0; i < 5; i++) {
		scanf("%d%s %c%d%d%d",
			&students[i].id,
			students[i].name,
			&students[i].gender,
			&students[i].chinese,
			&students[i].math,
			&students[i].english);
	}

	// 从小到大排序
	qsort(students, 5, sizeof(Student), cmp);

	printf("---------------------------------------\n");

	for (int i = 0; i < 5; i++) {
		print_stu_info(&students[i]);
	}
	return 0;
}