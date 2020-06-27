#include "malloc_test.h"
#include<malloc.h>
void stdmalloc (char **p, int n)
{ 
    for (int i = 0; i < n; ++i) {
        p[i] = (char*)malloc(sizeof(char));
    }
};
void printTime2(struct timespec start, const char *info)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << elapsed << " s" << endl;
}
const int N = 1e7;
char *p1[N];
char *p2[N];
int malloc_test0()
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread1(stdmalloc, p1, N);
    thread1.join();
    printTime2(start, "thread1   new.");
    for (int i = 0; i < N; ++i) {
        free(p1[i]);
        p1[i] = NULL;
    }

//    clock_gettime(CLOCK_MONOTONIC, &start);
//	std::thread thread2(stdmalloc, p2, N);
//    thread2.join();
//    printTime2(start, "thread2   new.");
//    for (int i = 0; i < N; ++i) {
//        delete p2[i];
//        p2[i] = NULL;
//    }

    clock_gettime(CLOCK_MONOTONIC, &start);
	std::thread thread3(stdmalloc, p1, N);
	std::thread thread4(stdmalloc, p2, N);
    thread3.join();
    thread4.join();
    printTime2(start, "thread3/4 new.");
    for (int i = 0; i < N; ++i) {
        delete p1[i];
        p1[i] = NULL;
        delete p2[i];
        p2[i] = NULL;
    }
    return 0;
}

struct Strarg {
    char **p;
    int len;
};

static void *threadf(void *arg)       
{
    Strarg *s = (Strarg*)arg;
    for (int i = 0; i < s->len; ++i) {
        s->p[i] = (char*)malloc(sizeof(char));
    }
    pthread_exit(NULL);
}

int __malloc_test()
{

    pthread_t threads[2];
    memset(&threads, 0, sizeof(threads));
    Strarg s1 = {p1, N};
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (pthread_create(&threads[0], NULL, threadf, (void*)&s1) == -1) {
        printf("thread1 create falied\n");
        exit(-1);
    }
    pthread_join(threads[0],NULL);
    printTime2(start, "thread1   malloc.");
    for (int i = 0; i < N; ++i) {
        free(s1.p[i]);
        s1.p[i] = NULL;
    }

    memset(&threads, 0, sizeof(threads));
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (pthread_create(&threads[0], NULL, threadf, (void*)&s1) == -1) {
        printf("threads1 create falied\n");
        exit(-1);
    }
    Strarg s2 = {p2, N};
    if (pthread_create(&threads[1], NULL, threadf, (void*)&s2) == -1) {
        printf("threads1 create falied\n");
        exit(-1);
    }
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    printTime2(start, "thread0/1 malloc.");
    for (int i = 0; i < N; ++i) {
        free(s1.p[i]);
        s1.p[i] = NULL;
        free(s2.p[i]);
        s2.p[i] = NULL;
    }
    return 0;
}

extern "C"
{
#include "jemalloc/jemalloc.h"
}
void jemalloc(char **p, int n)
{
    for (int i = 0; i < n; ++i) {
        p[i] = (char*)mallocx(sizeof(char), 0);
    }
}

int jemalloc_test()
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread1(jemalloc, p1, N);
    thread1.join();
    printTime2(start, "thread1   mallocx.");
    for (int i = 0; i < N; ++i) {
        p1[i] = NULL;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread3(jemalloc, p1, N);
    std::thread thread4(jemalloc, p2, N);
    thread3.join();
    thread4.join();
    printTime2(start, "thread3/4 mallocx.");
    for (int i = 0; i < N; ++i) {
        p1[i] = NULL;
        p2[i] = NULL;
    }
    return 0;
}

int malloc_test()
{
    printf("\nmalloc\n");
    __malloc_test();
    printf("\njemalloc\n");
    jemalloc_test();
    printf("\n\n");
    return 0;
}

/*
选择题
1. 对于一次性异步计算的结果, 以下哪个同步工具比较合适:(单选, 5分) C
A. blocking queue, B. latch, C. future, D. mutex

2. 对于生产者消费者问题, 以下哪个同步工具比较合适:(单选, 5分) D
A. blocking queue, B. latch, C. future, D. mutex

3. 以下哪个不是线程安全的实现方法:(单选, 5分) A
A. static local variable
B. thread local sotrage
C. mutual exclusion
D. stateless implementation

4. 以下的说法, 正确的是:(多选, 10分, 错选得0分, 少选得5分) E
A. boost::future::then是线程安全observer模式的体现
B. 为了实现线程安全c++类, mutable 成员变量本身应当是线程安全的
C. 跨线程引用的对象, 可以使用智能指针管理其生命周期
D. 互斥量和条件变量都是不可复制的
E. std::thread提供了cancel机制

问答题:
5. std::lock_guard和std::unique_lock有什么区别? 各有什么使用场景?(10分)
    lock_guard使用起来比较简单，除了构造函数外没有其他member function，在整个区域都有效。
    unique_guard除了lock_guard的功能外，提供了更多的member_function，相对来说更灵活一些。
    unique_guard的最有用的一组函数为： lock, unlock, try_lock, try_lock_for, try_lock_until
    通过这些函数，可以灵活的控制锁的范围和加锁的等待时间，但是资源的消耗要大一些。

6. 什么是false sharing, 写一个简单的代码示例, 并提供解决方法(15分)
当多线程修改互相独立的变量时，如果这些变量共享同一个缓存行，就会无意中影响彼此的性能，这就是伪共享。
示例代码的解决方法是使多线程访问的变量无法在同一个缓存行容纳。


7. 内存分配会成为多线程程序的性能瓶颈吗, 如果是, 写一个简单的代码示例, 并提供解决方法(20分)

编程题:
8. 以C++11标准库实现bounded blocking queue并测量其性能 (30分)
*/
