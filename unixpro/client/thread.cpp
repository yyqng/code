#include "thread.h"

const int SIZE = 10;

template <typename Container>
void test(Container c)
{
    typedef typename iterator_traits<typename Container::iterator>::value_type Vtype;
    for (int i = 0; i < SIZE; ++i) {
        c.insert(c.end(), Vtype());
    }
}

typedef struct tsd {
    pthread_t tid;
    char *str;
}tsd_t;

pthread_key_t key_td;

void destructor(void* value)
{
    tsd* v = (tsd*)value;
    delete v;
    printf("destory.. free value\n");
}

void *thread_routine(void *arg)
{
    tsd_t *value = new tsd_t;
    value->tid = pthread_self();
    value->str = (char *) arg;
    pthread_setspecific(key_td, (void *)value);
    printf("%p value->tid = %ld value->str = %s, pthread_setspecific\n", value, value->tid, value->str);
    sleep(1);                                                              
    value = (tsd*)pthread_getspecific(key_td);                             
    printf("%p value->tid = %ld value->str = %s, pthread_getspecific\n", value, value->tid, value->str);
    return NULL;
}

int thread_test()
{
    pthread_key_create(&key_td, destructor);

    pthread_t tid1;
    char c1[] = "thread1";
    pthread_create(&tid1, NULL, thread_routine, c1);

    pthread_t tid2;
    char c2[] = "thread2";
    pthread_create(&tid2, NULL, thread_routine, c2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_key_delete(key_td);

    return 0;
}

