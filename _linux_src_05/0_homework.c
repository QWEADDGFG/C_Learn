#include "func.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

typedef struct shareResource_s
{
    int flag;               // 共享标志：0-A未完成，1-A已完成
    pthread_mutex_t mutex;  // 保护 flag 的互斥锁
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

    /* 轮询等待 A 完成 */
    while (1)
    {
        /* ① 加锁：确保读取 flag 时不会与主线程的写入同时发生 */
        pthread_mutex_lock(&pshare_resource->mutex);
        if (pshare_resource->flag == 1)   // ② 读取共享标志
        {
            pthread_mutex_unlock(&pshare_resource->mutex);
            break;                        // ③ 条件满足，退出循环
        }
        pthread_mutex_unlock(&pshare_resource->mutex);
        /* ④ 短暂让出 CPU，避免狂烧 CPU 空转（可再加 usleep） */
    }

    B();          // ⑤ A 完成后才执行 B
    return NULL;
}

int main(int argc, char *argv[])
{
    shareResource_t share_resource;
    share_resource.flag = 0;                     // 初始状态：A 未完成
    pthread_mutex_init(&share_resource.mutex, NULL);

    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, &share_resource);

    A();                                         // 主线程执行 A

    /* ⑥ 把状态置为“完成”，通过同一把锁保证原子性和可见性 */
    pthread_mutex_lock(&share_resource.mutex);
    share_resource.flag = 1;
    pthread_mutex_unlock(&share_resource.mutex);

    pthread_join(tid, NULL);                     // 等待子线程结束
    return 0;
}
/*

t0   主线程  pthread_create(...)          // 子线程诞生，进入就绪队列
t1   子线程  开始运行
       ↓
t2   子线程  pthread_mutex_lock(&m)   // ① 抢到锁，成为 owner
t3   子线程  if(flag==0) → true
t4   子线程  pthread_mutex_unlock(&m) // ② 释放锁，owner 变空
       ↑
      这里锁已空闲，**任何**线程都能再次 lock
t5   内核调度  时钟中断 → 切换回主线程
t6   主线程  A() 执行完毕
t7   主线程  pthread_mutex_lock(&m)   // ③ 锁空闲，成功拿到
t8   主线程  flag = 1
t9   主线程  pthread_mutex_unlock(&m) // ④ 释放
t10  内核调度  唤醒等待者（子线程）
t11  子线程  从 pthread_mutex_lock 返回，继续循环
       …

*/