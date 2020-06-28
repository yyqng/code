#include "malloc_test.h"
const int N1 = 1e7;
char *p1[N1];
char *p2[N1];

void stdmalloc (char **p)
{ 
    for (int i = 0; i < N1; ++i) {
        p[i] = (char*)malloc(sizeof(char));
    }
};

static void printTime2(struct timespec start, const char *info)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << N1 << " times.Total time cost: " << elapsed << " s" << endl;
}

int malloc_test0()
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread1(stdmalloc, p1);
    thread1.join();
    printTime2(start, "Single thread malloc ");
    for (int i = 0; i < N1; ++i) {
        free(p1[i]);
        p1[i] = NULL;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
	std::thread thread3(stdmalloc, p1);
	std::thread thread4(stdmalloc, p2);
    thread3.join();
    thread4.join();
    printTime2(start, "Two threads. each thread malloc ");
    for (int i = 0; i < N1; ++i) {
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

int malloc_test()
{
    printf("\nmalloc\n");
    pthread_t threads[2];
    memset(&threads, 0, sizeof(threads));
    Strarg s1 = {p1, N1};
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (pthread_create(&threads[0], NULL, threadf, (void*)&s1) == -1) {
        printf("thread1 create falied\n");
        exit(-1);
    }
    pthread_join(threads[0],NULL);
    printTime2(start, "Single thread malloc ");
    for (int i = 0; i < N1; ++i) {
        free(s1.p[i]);
        s1.p[i] = NULL;
    }

    memset(&threads, 0, sizeof(threads));
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (pthread_create(&threads[0], NULL, threadf, (void*)&s1) == -1) {
        printf("threads1 create falied\n");
        exit(-1);
    }
    Strarg s2 = {p2, N1};
    if (pthread_create(&threads[1], NULL, threadf, (void*)&s2) == -1) {
        printf("threads1 create falied\n");
        exit(-1);
    }
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    printTime2(start, "Two threads. each thread malloc ");
    for (int i = 0; i < N1; ++i) {
        free(s1.p[i]);
        s1.p[i] = NULL;
        free(s2.p[i]);
        s2.p[i] = NULL;
    }
    return 0;
    printf("\n\n");
}

