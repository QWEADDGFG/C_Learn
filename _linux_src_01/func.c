#include <stdio.h>

// 声明函数
void func()
{
    printf("hello func\n");
}

// 实现两个数字相减
int minus(int m, int n)
{
    return m - n;
}

// 取两个数字中的最大值
int max(int a, int b)
{
    int c;
    c = a > b ? a : b;
    return c;
}

// 主函数
int main()
{
    // 函数的调用
    func();
    func();

    printf("17-90的结果：%d\n", minus(17, 90));
    printf("21-180的结果：%d\n", minus(21, 180));
    printf("12和16之间较大的是：%d\n", max(12, 16));
    printf("45和31之间较大的是：%d\n", max(45, 31));

    return 0;
}