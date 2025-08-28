#include <stdio.h>
#include <stdlib.h>

int compare(const void *p1, const void *p2);

int main()
{
    double a[] = {12.23, 34.23, 12.12, 2, 3, 45, 6, 78};
    int n = sizeof(a) / sizeof(a[0]);

    qsort(a, n, sizeof(a[0]), compare);

    for (size_t i = 0; i < n; i++)
    {
        printf("%.2lf\n", a[i]);
    }
    return 0;
}
int compare(const void *p1, const void *p2)
{
    double a = *(const double*)p1;
    double b = *(const double*)p2;
    return (a > b) - (a < b);
}