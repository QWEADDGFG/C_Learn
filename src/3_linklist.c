#include <stdio.h>

int main()
{
    double arr[] = {2, 2, 3, 4, 15, 6, 7, 81, 9, 10};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    float arr_0 = arr[0];
    for (int i = 0; i < arr_size; i++)
    {
        arr[i] = arr[i] / arr_0;
        printf("%.2f ", arr[i]);
    }
    return 0;
}