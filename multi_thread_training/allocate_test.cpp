#include "allocate_test.h"
int const T_SIZE = 9;
const int N1 = (T_SIZE - 1) * 1e6;
char *p[T_SIZE][N1];
const int ALLOC_SIZE = 1024;

static void printTime2(struct timespec start, const char *info, int n)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << n << " times.Total time cost: " << elapsed << " s" << endl;
}

struct Strarg {
    char **p;
    int len;
};

int __allocate_test(void *(*start_routine) (void *))
{
    pthread_t threads[T_SIZE];
    memset(&threads, 0, sizeof(threads));
    const int N = N1 / (T_SIZE - 1);
    Strarg s[T_SIZE] = {
        {p[0], N1},
        {p[1], N},
        {p[2], N},
        {p[3], N},
        {p[4], N},
        {p[5], N},
        {p[6], N},
        {p[7], N},
        {p[8], N},
    };
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (pthread_create(&threads[0], NULL, start_routine, (void*)&s[0]) == -1) {
        printf("thread[0] create failed\n");
        exit(-1);
    }
    pthread_join(threads[0],NULL);
    printTime2(start, "Single thread allocate ", N1);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 1; i < T_SIZE; ++i) {
        if (pthread_create(&threads[i], NULL, start_routine, (void*)&(s[i])) == -1) {
            printf("threads[%d] create failed\n", i);
            exit(-1);
        }
    }

    for (int i = 1; i < T_SIZE; ++i) {
        pthread_join(threads[i],NULL);
    }
    printTime2(start, "8 threads. each thread allocate ", N);
    for (int j = 0; j < N1; ++j) {
        delete(s[0].p[j]);
        s[0].p[j] = NULL;
    }
    for (int i = 1; i < T_SIZE; ++i) {
        for (int j = 0; j < N; ++j) {
            delete(s[i].p[j]);
            s[i].p[j] = NULL;
        }
    }
    return 0;
}



static void *do_new(void *arg)       
{
    Strarg *s = (Strarg*)arg;
    //printf("s->len = %d\n", s->len);
    for (int i = 0; i < s->len; ++i) {
        s->p[i] = NULL;
        //s->p[i] = (char*)malloc(sizeof(char));
        s->p[i] = new(char[ALLOC_SIZE]);
        if (s->p[i] == NULL) {
            printf("new failed\n");
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
int _new_test()
{
    printf("Use new:\n");
    __allocate_test(do_new);
    printf("\n");
    return 0;
}


static void *do_jemalloc(void *arg)       
{
    Strarg *s = (Strarg*)arg;
    //printf("s->len = %d\n", s->len);
    for (int i = 0; i < s->len; ++i) {
        s->p[i] = NULL;
        s->p[i] = (char*)mallocx(sizeof(char) * ALLOC_SIZE, 0);
        if (s->p[i] == NULL) {
            printf("mallocx failed\n");
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

int _jemalloc_test()
{
    printf("Use mallocx(jemalloc):\n");
    __allocate_test(do_jemalloc);
    return 0;
}

int allocate_test()
{
    _new_test();
    _jemalloc_test();
    return 0;
}

