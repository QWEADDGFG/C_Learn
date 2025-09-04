#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

typedef struct {
	int id;
	char name[25];
	char gender;
	int chinese;
	int math;
	int english;
} Student;

void print_stu_info(const Student* p) {
	printf("%d %s %c %d %d %d\n",
		p->id,
		p->name,
		p->gender,
		p->chinese,
		p->math,
		p->english);
}

int total_score(const Student* p) {
	return p->chinese + p->math + p->english;
}

void sort_students(Student* stus[], int n) {
	// 根据总分排序
	// 选择排序
	for (int i = 0; i < n - 1; i++) {
		// i: 下一个元素应该置于的位置
		int maxIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (total_score(stus[j]) > total_score(stus[maxIdx])) {
				maxIdx = j;
			}
		}
		Student* t = stus[i];
		stus[i] = stus[maxIdx];
		stus[maxIdx] = t;
	}
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

	Student* pstudents[5] = {students, students + 1, students + 2, 
		students + 3, students + 4};
	
	// 对指针数组排序
	sort_students(pstudents, 5);

	// 打印排序后的信息
	for (int i = 0; i < 5; i++) {
		print_stu_info(pstudents[i]);
	}
	return 0;
}