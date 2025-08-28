#include <stdio.h>
#include <stdlib.h>

#define STU_NUM 5
#define COURSE_NUM 3

typedef struct {
    int  id;                 /* 学号            */
    char name[20];           /* 姓名            */
    float score[COURSE_NUM]; /* 三门课成绩      */
    float total;             /* 总分（计算用）  */
} Student;

/* 比较函数：按总分降序 */
/**
* @brief 比较两个学生的总成绩
*
* 使用qsort函数时作为比较函数，比较两个Student对象的总成绩
*
* @param a 指向第一个Student对象的指针的指针
* @param b 指向第二个Student对象的指针的指针
*
* @return 如果b指向的对象的总成绩大于a指向的对象的总成绩，返回正数；
*         如果b指向的对象的总成绩小于a指向的对象的总成绩，返回负数；
*         如果两者总成绩相等，返回0
*/
int cmp(const void *a, const void *b)
{
    float t1 = (*(Student **)a)->total;
    float t2 = (*(Student **)b)->total;
    return (t2 > t1) - (t2 < t1);
}

int main(void)
{
    Student stu[STU_NUM];        /* 5 个学生实体 */
    Student *pStu[STU_NUM];      /* 5 个指针 */

    /* 1. 输入数据并计算总分 */
    for (int i = 0; i < STU_NUM; ++i) {
        pStu[i] = &stu[i];       /* 指针指向实体 */
        printf("请输入第 %d 个学生的信息（学号 姓名 三门成绩）：\n", i + 1);
        scanf("%d %19s", &stu[i].id, stu[i].name);
        stu[i].total = 0;
        for (int j = 0; j < COURSE_NUM; ++j) {
            scanf("%f", &stu[i].score[j]);
            stu[i].total += stu[i].score[j];
        }
    }

    /* 2. 排序 */
    qsort(pStu, STU_NUM, sizeof(Student *), cmp);

    /* 3. 输出 */
    printf("\n排序后的学生信息：\n");
    printf("学号\t姓名\t总分\n");
    for (int i = 0; i < STU_NUM; ++i) {
        printf("%d\t%s\t%.2f\n", pStu[i]->id, pStu[i]->name, pStu[i]->total);
    }

    return 0;
}