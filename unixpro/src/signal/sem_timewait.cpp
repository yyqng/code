#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
 
#define TIMEOUT_S 5
#define TIMEOUT_MS 1500
 
sem_t sem;
 
// 时间 time 自加 ms 毫秒
void time_add_ms(struct timeval *time, uint ms)
{
    time->tv_usec += ms * 1000; // 微秒 = 毫秒 * 1000
    if(time->tv_usec >= 1000000) // 进位，1000 000 微秒 = 1 秒
    {
            time->tv_sec += time->tv_usec / 1000000;
            time->tv_usec %= 1000000;
    }
}
 
void *pthread(void *arg)
{
    struct timespec t;
 
    // 毫秒级别
    struct timeval time;
    gettimeofday(&time, NULL);
    time_add_ms(&time, TIMEOUT_MS);
    t.tv_sec = time.tv_sec;
    t.tv_nsec = time.tv_usec * 1000;
 
    // 秒级别
    //t.tv_sec = time(NULL) + TIMEOUT_S;
    //t.tv_nsec = 0;
 
    printf("t.tv_sec = %lu\n", t.tv_sec);
    printf("t.tv_nsec = %lu\n", t.tv_nsec);
 
    while(1)
    {
        int semvalue = -1;
        sem_getvalue(&sem, &semvalue);
        printf("will call sem_timedwait, semvalue = %d\n", semvalue);
 
        // 如果sem 信号量值>0，则sem_timedwait 立即返回；如果sem 信号量值≤0，则 sem_timedwait 阻塞等待 TIMEOUT秒后再返回。
        int ret = sem_timedwait(&sem, &t);
        printf("over call sem_timedwait, ret = %d\n", ret);
        if (ret == -1)
        {
                sem_getvalue(&sem, &semvalue);
                printf("pthread() will return\n");
                return NULL;
        }
    }
}
 
int sem_timedwaittest(int argc , char *argv[] )
{
        pthread_t tid;
 
        sem_init(&sem, 0, 0);  // 第3个参数是0，相当于此时停车场已经停满了，必须要等到有车离开时(即执行sem_post 操作)才能停车。
        sem_post(&sem);
        //sem_wait(&sem);
        sem_post(&sem);
 
        pthread_create(&tid, NULL, &pthread, NULL);
        pthread_join(tid, NULL);
 
        sem_destroy(&sem);
 
        return 0;
}
