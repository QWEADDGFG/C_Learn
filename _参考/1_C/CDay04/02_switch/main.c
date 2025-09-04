#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
    // int grade;
    // printf("Enter a grade: ");
    // scanf("%d", &grade);

    // 弊端：1. 可读性差；2. 存在效率问题
    //if (grade == 4)
    //    printf("Excellent\n");
    //else if (grade == 3)
    //    printf("Good\n");
    //else if (grade == 2)
    //    printf("Average\n");
    //else if (grade == 1)
    //    printf("Poor\n");
    //else if (grade == 0)
    //    printf("Failing\n");
    //else
    //    printf("Illegal grade\n");


    // 限制条件：1. switch后面的表达式必须是整型(char, 枚举)
    //          2. switch后面的表达式和case的标签，是用 == 做比较的
    //switch (grade) {
    //case 4:
    //    printf("Excellent\n");
    //    break;
    //case 3:
    //    printf("Good\n");
    //    break;
    //case 2:
    //    printf("Average\n");
    //    break;
    //case 1:
    //    printf("Poor\n");
    //    break;
    //case 0:
    //    printf("Failing\n");
    //    break;
    //default:
    //    printf("Illegal grade\n");
    //    break;
    //}

    // 两个注意事项：1. 多个case可以共用一组语句。
    //              2. 注意case穿透现象
    //switch (grade) {
    //case 4: case 3: case 2: case 1: 
    //    printf("Passing\n");
    //    break;
    //case 0:
    //    printf("Failing\n");
    //    break;
    //default:
    //    printf("Illegal grade\n");
    //    break;
    //}

    // case 穿透现象
    //switch (grade) {
    //case 4:
    //    printf("Excellent\n");
    //    /* break through */
    //case 3:
    //    printf("Good\n");
    //    break;
    //case 2:
    //    printf("Average\n");
    //    break;
    //case 1:
    //    printf("Poor\n");
    //    break;
    //case 0:
    //    printf("Failing\n");
    //    break;
    //default:
    //    printf("Illegal grade\n");
    //    break;
    //}
    // ...

    int grade;
    printf("Enter numerical grade: ");
    scanf("%d", &grade);

    if (grade > 100 || grade < 0) {
        printf("Illegal grade!\n");
    } else {
        char level = '\0';
        switch (grade / 10) {
        case 10: case 9:
            level = 'A';
            break;
        case 8:
            level = 'B';
            break;
        case 7:
            level = 'C';
            break;
        case 6:
            level = 'D';
            break;
        default:
            level = 'F';
            break;
        }
        printf("Letter grade: %c\n", level);
    }
	return 0;
}