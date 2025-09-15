#include "func.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

typedef struct shareResource_s
{
    int flag;              // 共享标志：0-->A未完成，B不可执行，1-->A已完成，B可执行
    pthread_mutex_t mutex; // 保护 flag 的互斥锁
    pthread_cond_t  cond;   // 新增：条件变量 
} shareResource_t;

void A()
{
    printf("before A\n");
    sleep(1);
    printf("after A\n");
    sleep(1);
}

void B()
{
    printf("before B\n");
    sleep(1);
    printf("after B\n");
    sleep(1);
}

void *thread_func(void *arg)
{
    shareResource_t *pshare_resource = (shareResource_t *)arg;

    // /* 轮询等待 A 完成 */ // --> 效率太低，可以使用条件变量
    // while (1)
    // {
    //     /* ① 加锁：确保读取 flag 时不会与主线程的写入同时发生 */
    //     pthread_mutex_lock(&pshare_resource->mutex);
    //     if (pshare_resource->flag == 1) // ② 读取共享标志
    //     {
    //         pthread_mutex_unlock(&pshare_resource->mutex);
    //         break; // ③ 条件满足，退出循环
    //     }
    //     pthread_mutex_unlock(&pshare_resource->mutex);
    //     /* ④ 短暂让出 CPU，避免狂烧 CPU 空转（可再加 usleep） */
    // }

    pthread_mutex_lock(&pshare_resource->mutex); // ① 加锁
    if (pshare_resource->flag == 0){
        pthread_cond_wait(&pshare_resource->cond, &pshare_resource->mutex); // ② 等待条件变量
    } 
    pthread_mutex_unlock(&pshare_resource->mutex); // ③ 解锁

    B(); // ⑤ A 完成后才执行 B
    return NULL;
}

int main(int argc, char *argv[])
{
    shareResource_t share_resource;
    share_resource.flag = 0; // 初始状态：A 未完成
    pthread_mutex_init(&share_resource.mutex, NULL);
    pthread_cond_init(&share_resource.cond, NULL);

    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, &share_resource);
    sleep(1); 

    A(); // 主线程执行 A

    /* ⑥ 把状态置为“完成”，通过同一把锁保证原子性和可见性 */
    pthread_mutex_lock(&share_resource.mutex);
    share_resource.flag = 1;
    pthread_cond_signal(&share_resource.cond); // 通知线程
    pthread_mutex_unlock(&share_resource.mutex);

    pthread_join(tid, NULL); // 等待子线程结束
    return 0;
}
// #define _GNU_SOURCE
// #include <pthread.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <time.h>
// #include <string.h>
// #include <stdarg.h>   // 拿 va_list / va_start /

// typedef struct {
//     int flag;
//     pthread_mutex_t mutex;
//     pthread_cond_t  cond;
// } shareResource_t;

// /* ---------- 工具：带时间戳的打印 ---------- */
// static void ts_printf(const char *tag, const char *fmt, ...)
// {
//     struct timespec now;
//     clock_gettime(CLOCK_REALTIME, &now);
//     struct tm *t = localtime(&now.tv_sec);

//     char buf[64];
//     snprintf(buf, sizeof(buf), "[%02d:%02d:%03ld] [%s] ",
//              t->tm_min, t->tm_sec, now.tv_nsec / 1000000, tag);

//     printf("%s", buf);
//     va_list ap;
//     va_start(ap, fmt);
//     vprintf(fmt, ap);
//     va_end(ap);
//     fflush(stdout);
// }

// /* ---------- 业务函数 ---------- */
// void A(void)
// {
//     ts_printf("M", "A 开始\n");
//     sleep(1);
//     ts_printf("M", "A 结束\n");
//     sleep(1);
// }

// void B(void)
// {
//     ts_printf("T", "B 开始\n");
//     sleep(1);
//     ts_printf("T", "B 结束\n");
//     sleep(1);
// }

// /* ---------- 子线程入口 ---------- */
// void *thread_func(void *arg)
// {
//     shareResource_t *p = (shareResource_t *)arg;
//     ts_printf("T", "子线程启动\n");

//     pthread_mutex_lock(&p->mutex);
//     ts_printf("T", "加锁成功，检查 flag=%d\n", p->flag);
//     if (p->flag == 0) {
//         ts_printf("T", "flag 仍为 0，即将 cond_wait 阻塞…\n");
//         pthread_cond_wait(&p->cond, &p->mutex);
//         ts_printf("T", "被唤醒，重新获得锁，flag=%d\n", p->flag);
//     }
//     pthread_mutex_unlock(&p->mutex);
//     ts_printf("T", "解锁，准备执行 B\n");

//     B();
//     ts_printf("T", "子线程即将退出\n");
//     return NULL;
// }

// /* ---------- main ---------- */
// int main(void)
// {
//     shareResource_t sr = { .flag = 0 };
//     pthread_mutex_init(&sr.mutex, NULL);
//     pthread_cond_init (&sr.cond,  NULL);

//     pthread_t tid;
//     pthread_create(&tid, NULL, thread_func, &sr);
//     ts_printf("M", "已创建子线程，先 sleep 1 s 模拟其他工作\n");
//     sleep(1);

//     A();          /* 主线程干正事 */

//     ts_printf("M", "准备改 flag 并发出信号…\n");
//     pthread_mutex_lock(&sr.mutex);
//     sr.flag = 1;
//     ts_printf("M", "flag 已置 1，即将 pthread_cond_signal\n");
//     pthread_cond_signal(&sr.cond);
//     pthread_mutex_unlock(&sr.mutex);
//     ts_printf("M", "主线程已解锁，等待子线程结束\n");

//     pthread_join(tid, NULL);
//     ts_printf("M", "子线程已回收，进程退出\n");

//     pthread_cond_destroy(&sr.cond);
//     pthread_mutex_destroy(&sr.mutex);
//     return 0;
// }