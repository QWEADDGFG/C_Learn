#include <func.h>

typedef struct {
    int* arr;
    int left;
    int right;
} Section;

void* start_routine(void* args) {
    Section* sec = (Section*) args; 
    int sum = 0;
    for (int i = sec->left; i <= sec->right; i++) {
        sum += sec->arr[i];
    }

    // pthread_exit((void*)sum);
    return (void*) sum;
}

int main(int argc, char* argv[])
{
    // 主线程
    int arr[100];
    for (int i = 1; i <= 100; i++) {
        arr[i - 1] = i;
    }

    pthread_t tid1, tid2;
    Section sec1 = {arr, 0, 49};
    Section sec2 = {arr, 50, 99};

    int err = pthread_create(&tid1, NULL, start_routine, &sec1);
    if (err) {
        error(1, err, "pthread_create");
    }

    err = pthread_create(&tid2, NULL, start_routine, &sec2);
    if (err) {
        error(1, err, "pthread_create");
    }

    // 主线程：等待子线程结束，并接收返回值
    int result1;
    err = pthread_join(tid1, (void**)&result1); // 无限期等待
    if (err) {
        error(1, err, "pthread_join %lu\n", tid1);
    }

    int result2;
    err = pthread_join(tid2, (void**)&result2);
    if (err) {
        error(1, err, "pthread_join %lu\n", tid2);
    }

    printf("main: sum = %d\n", result1 + result2);
    return 0;
}

