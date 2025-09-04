#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 128

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

int main(int argc, char* argv[]) {
	// xxx.exe  src  dst
	// 1. 参数校验
	if (argc != 3) {
		fprintf(stderr, "Usage: %s src dst\n", argv[0]);
		exit(1);
	}
	// 2. 打开文件
	FILE* src = fopen(argv[1], "r");
	if (!src) {
		fprintf(stderr, "Open %s failed\n", argv[1]);
		exit(1);
	}

	FILE* dst = fopen(argv[2], "w");
	if (!dst) {
		fprintf(stderr, "Open %s failed\n", argv[2]);
		fclose(src);
		exit(1);
	}
	// 3. 读写文件
	// a. 一个字符一个字符地读写：fgetc, fputc
	// 把大写转换成小写字母
	//int c;
	//while ((c = fgetc(src)) != EOF) {
	//	fputc(tolower(c), dst);
	//}

	// b. 一行一行地读写
	//char line[MAXLINE];
	//char buffer[MAXLINE];
	//int num = 1;
	//while (fgets(buffer, MAXLINE, src) != NULL) {
	//	sprintf(line, "%d. %s", num, buffer);
	//	fputs(line, dst);
	//	num++;
	//}
	
	// c. 格式化地读写
	Student students[5];
	for (int i = 0; i < 5; i++) {
		fscanf(src, "%d%s %c%d%d%d",
			&students[i].id,
			students[i].name,
			&students[i].gender,
			&students[i].chinese,
			&students[i].math,
			&students[i].english);
	}

	for (int i = 0; i < 5; i++) {
		students[i].chinese *= 0.8;
		students[i].math *= 0.9;
		students[i].english *= 0.75;
	}

	for (int i = 0; i < 5; i++) {
		fprintf(dst, "%d %s %c %d %d %d\n",
			students[i].id,
			students[i].name,
			students[i].gender,
			students[i].chinese,
			students[i].math,
			students[i].english);
	}
	// 4. 关闭文件
	fclose(src);
	fclose(dst);
	return 0;
}