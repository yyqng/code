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


void destructor(void* value)
{
    tsd* v = (tsd*)value;
    delete v;
    printf("destory.. free value\n");
}

pthread_key_t key_td;
int thread_routine2()
{
    sleep(1);                                                              
    tsd_t *value = new tsd_t;
    value = (tsd*)pthread_getspecific(key_td);                             
    printf("%p value->tid = %ld value->str = %s, pthread_getspecific\n", value, value->tid, value->str);
    return 0;
}

pthread_once_t once_control = PTHREAD_ONCE_INIT;
void init_routine(void)
{
    pthread_key_create(&key_td, destructor); 
    printf("init_routine \n");
    return;
}
void *thread_routine(void *arg)
{
//    pthread_key_create(&key_td, destructor); //run twice : Segmentation fault 
    pthread_once(&once_control, init_routine); // OK
    tsd_t *value = new tsd_t;
    value->tid = pthread_self();
    value->str = (char *) arg;
    pthread_setspecific(key_td, (void *)value);
    printf("%p value->tid = %ld value->str = %s, pthread_setspecific\n", value, value->tid, value->str);
    thread_routine2();
    return NULL;
}

//void destructor(void* value)
//{
//    printf("destory.. free value\n");
//}
//
//void *thread_routine(void *arg)
//{
//    tsd_t ovalue;
//    tsd_t *value = &ovalue;
//    value->tid = pthread_self();
//    value->str = (char *) arg;
//    printf("%p value->tid = %ld value->str = %s\n", value, value->tid, value->str);
//    sleep(1);                                                              
//    printf("%p value->tid = %ld value->str = %s\n", value, value->tid, value->str);
//    return NULL;
//}

int thread_test()
{

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

