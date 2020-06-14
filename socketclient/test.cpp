#include<bitset>
#include<set>
#include<map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
using namespace std;


#define ERR_EXIT(m) do { perror(m); exit(EXIT_FAILURE);} while(0)



const int SIZE = 10;

template <typename Container>
void test(Container c)
{
    typedef typename iterator_traits<typename Container::iterator>::value_type Vtype;
    for (int i = 0; i < SIZE; ++i) {
        c.insert(c.end(), Vtype());
    }
}

int testSocket()
{
    int i = 0x12345678;
    char *p = (char *)&i;
    printf("%0x, %0x, %0x, %0x \n", p[0], p[1], p[2], p[3]);

    int j = htonl(i);
    p = (char *)&j;
    printf("%0x, %0x, %0x, %0x \n", p[0], p[1], p[2], p[3]);

    const char *cp = "192.168.0.100";
    in_addr_t addr = inet_addr(cp);
    printf("addr = %d\n", ntohl(addr));

    struct in_addr in;
    in.s_addr = addr;
    p = inet_ntoa(in);
    printf("p = %s\n", p);

    return 0;
}

int echo_client()
{
    int lfd;
    //if (lfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) < 0) {
    if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ERR_EXIT("socket error\n");
    }

    return 0;
}

typedef struct tsd {
    pthread_t tid;
    char *str;
}tsd_t;

pthread_key_t key_td;

void destructor(void*)
{
    printf("destory..\n");
}

void *thread_routine(void *arg)
{
    tsd_t value;
    pthread_setspecific(key_td, (void *)&value);
    printf("routine..%s\n", (char*) arg);
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

#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static int i = 0;
int readFile()
{
    ++i;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    char filename[32] = {0};
    sprintf(filename, "/proc/%d/stat", getpid());
    printf("%s :\n", filename);
    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu, static i = %d\n", read, i);
        printf("%s", line);
    }
    return 0;
}

void mem_usage(int& vm_usage, int& resident_set) {
    vm_usage = 0.0;
    resident_set = 0.0;
    ifstream stat_stream("/proc/self/stat",ios_base::in); //get info from proc directory
    //create some variables to get info
    string pid, comm, state, ppid, pgrp, session, tty_nr;
    string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    string utime, stime, cutime, cstime, priority, nice;
    string O, itrealvalue, starttime;
    unsigned long vsize;
    long rss;

    //++i;
    //FILE *fp;
    //char *line = NULL;
    //size_t len = 0;
    //ssize_t read;
    //
    //char filename[32] = {0};
    //sprintf(filename, "/proc/%d/stat", getpid());
    //printf("%s :\n", filename);
    //fp = fopen(filename, "r");
    //if (fp == NULL)
    //    exit(EXIT_FAILURE);
    //
    //while ((read = getline(&line, &len, fp)) != -1) {
    //    printf("Retrieved line of length %zu, static i = %d\n", read, i);
    //    printf("%s", line);
    //}

    stat_stream
            >> pid
            >> comm
            >> state
            >> ppid
            >> pgrp
            >> session
            >> tty_nr
            >> tpgid
            >> flags
            >> minflt
            >> cminflt
            >> majflt
            >> cmajflt
            >> utime
            >> stime
            >> cutime
            >> cstime
            >> priority
            >> nice
            >> O
            >> itrealvalue
            >> starttime
            >> vsize
            >> rss; // don't care about the rest
    stat_stream.close();
    long page_size_B = sysconf(_SC_PAGE_SIZE); // for x86-64 is configured to use 2MB pages
    vm_usage = vsize;
    resident_set = rss * page_size_B;
    //readFile();
}


int show_mem(int &vm, int &rss) {
   mem_usage(vm, rss);
   cout << "Virtual Memory: " << vm << endl;
   cout << "Resident set size: " << rss << endl;
   return 0;
}

class C1{
public:
    int i;
    bool operator < (const C1 &c) const;
};

bool C1::operator < (const C1 &c) const {
    return c.i < i;
}

class C2{
public:
    double i;
    //int k[9];
    bool operator < (const C2 &c) const;
};

bool C2::operator < (const C2 &c) const {
    return c.i < i;
}

template <class T>
int __set_mem_test(T & t, int elenum)
{
    int vm1, rss1;
    int vm2, rss2;
    set<T> si;
    //vector<T> si;
    int i = elenum - 1;
    show_mem(vm1, rss1);
    for (i = 0; i < elenum; ++i) {
        t.i = i;
        //t.k[0] = i;
        //t.k[9] = i;
        si.insert(t);
    //    si.push_back(t);
    }
    show_mem(vm2, rss2);
    printf("elenum = %d, sizeof(t) = %ld\n", elenum, sizeof(t));
    cout << "Total memory usage: " << (vm2 - vm1) / sizeof(t) << " ele" << endl;
    cout << "Total resident set usage: " << (rss2 - rss1) / sizeof(t) << " ele"<< endl;
    while (0) {
    }
    return 0;
}

int set_mem_test()
{
    C1 c1;
    __set_mem_test(c1, 1024);
    printf("\n");
    C2 c2;
    __set_mem_test(c2, 1024);
    return 0;
}
