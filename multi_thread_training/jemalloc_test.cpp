#include "jemalloc_test.h"
static void printTime2(struct timespec start, const char *info)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << elapsed << " s" << endl;
}

const int N2 = 1e7;
char *p3[N2];
char *p4[N2];

struct Strarg {
    char **p;
    int len;
};


void jemalloc(char **p, int N2)
{
    for (int i = 0; i < N2; ++i) {
        p[i] = (char*)mallocx(sizeof(char), 0);
    }
}

int jemalloc_test()
{
    printf("\njemalloc\n");
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread1(jemalloc, p3, N2);
    thread1.join();
    printTime2(start, "thread1   mallocx.");
    for (int i = 0; i < N2; ++i) {
        p3[i] = NULL;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread3(jemalloc, p3, N2);
    std::thread thread4(jemalloc, p4, N2);
    thread3.join();
    thread4.join();
    printTime2(start, "thread3/4 mallocx.");
    for (int i = 0; i < N2; ++i) {
        p3[i] = NULL;
        p4[i] = NULL;
    }
    printf("\n\n");
    return 0;
}
