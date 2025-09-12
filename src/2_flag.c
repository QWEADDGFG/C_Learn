#include "func.h"

//A --> B --> C 

typedef struct shared_data_s
{
    int flag; // 0表示A未完成，1表示A已完成B未执行，2表示A已完成B已执行
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} shared_data_t;

void *threadFunc(void *arg)
{
    shared_data_t *pdata = (shared_data_t *)arg;
    pthread_mutex_lock(&pdata->mutex);
    while (pdata->flag != 1){
        pthread_cond_wait(&pdata->cond, &pdata->mutex);
    }
    pthread_mutex_unlock(&pdata->mutex);
    printf("B\n");
    pthread_mutex_lock(&pdata->mutex);
    pdata->flag = 2;
    pthread_cond_signal(&pdata->cond);
    pthread_mutex_unlock(&pdata->mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    shared_data_t data;
    data.flag = 0;
    pthread_mutex_init(&data.mutex, NULL);
    pthread_cond_init(&data.cond, NULL);

    pthread_t tid;
    pthread_create(&tid, NULL, threadFunc, &data);
    printf("A\n");
    pthread_mutex_lock(&data.mutex);
    data.flag = 1;
    pthread_cond_signal(&data.cond);
    pthread_mutex_unlock(&data.mutex);

    pthread_mutex_lock(&data.mutex);
    while (data.flag != 2){
        pthread_cond_wait(&data.cond, &data.mutex);
    }
    pthread_mutex_unlock(&data.mutex);
    printf("C\n");

    pthread_join(tid, NULL);
    return 0;
}