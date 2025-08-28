#include <stdio.h>

int main(void) {
    int a[5] = {0, 0, 0, 0, 0};   // 一个长度为 5 的整型数组
    int *p = a;                  // p 指向数组的首元素 a[0]
    int j = 42;                  // 要写入的值

    printf("执行前：\n");
    for (int i = 0; i < 5; ++i) printf("a[%d] = %d\n", i, a[i]);
    printf("p 指向的下标 = %ld\n\n", p - a);   // 0

    /* 关键语句 */
    *p++ = j;        // 等价于： *(p++) = j;

    printf("执行后：\n");
    for (int i = 0; i < 5; ++i) printf("a[%d] = %d\n", i, a[i]);
    printf("p 指向的下标 = %ld\n", p - a);   // 1

    return 0;
}
