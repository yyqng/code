#include"test.h"
#include<bitset>
#include<set>
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

//获取进程占用虚拟内存
unsigned int get_proc_virtualmem(unsigned int pid)
{
    char file_name[64]={0};
    FILE *fd;
    char line_buff[512]={0};
    sprintf(file_name,"/proc/%d/status",pid);
    
    fd =fopen(file_name,"r");
    if(nullptr == fd){
        return 0;
    }
    
    char name[64];
    int vmsize;
    for (int i=0; i<VMSIZE_LINE-1;i++){
        fgets(line_buff,sizeof(line_buff),fd);
    }
    
    fgets(line_buff,sizeof(line_buff),fd);
    sscanf(line_buff,"%s %d",name,&vmsize);
    fclose(fd);
 
    return vmsize;
}

#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void mem_usage(double& vm_usage, double& resident_set) {
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
   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
   >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
   >> utime >> stime >> cutime >> cstime >> priority >> nice
   >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest
   stat_stream.close();
   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // for x86-64 is configured to use 2MB pages
   vm_usage = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}

int show_mem() {
   double vm, rss;
   mem_usage(vm, rss);
   cout << "Virtual Memory: " << vm << "\nResident set size: " << rss << endl;
   return 0;
}

class C{
public:
    int i;
    int j;
    bool operator < (const C &c) const;
};

bool C::operator < (const C &c) const {
    return c.i < i;
}

int set_test()
{
    vector<int> si;
    //unsigned int pid = getpid();
    show_mem();
    //printf("pid=%d\n",pid); 
    //printf("mem=%ld\n", si.size() * sizeof(int)); 
    //printf("virtualmem=%d\n",get_proc_virtualmem(pid)); 
    for (int i = 0; i < 10240; ++i) {
        si.push_back(i);
    }
    //int *a = new int[1024];
    //a[1000] = 5;
    //printf("a[1000] = %d\n", a[1000]);
    //printf("virtualmem=%d\n",get_proc_virtualmem(pid)); 
    //printf("mem=%ld\n", si.size() * sizeof(int)); 
    show_mem();
    //delete a;
    while (0) {
    }
    return 0;
}

int set_test2()
{
    vector<C> si;
    C c;
    c.j = 0;
    //unsigned int pid = getpid();
    show_mem();
    //printf("pid = %d\n",pid); 
    //printf("mem = %ld\n", si.size() * sizeof(C)); 
    //printf("virtualmem = %d\n",get_proc_virtualmem(pid)); 
    //int *a = new int[20480];
    //a[20000] = 5;
    //printf("a[20000] = %d\n", a[20000]);
    for (int i = 0; i < 20480; ++i) {
        c.i = i;
        si.push_back(c);
    }
    //printf("virtualmem = %d\n",get_proc_virtualmem(pid)); 
    //printf("mem = %ld\n", si.size() * sizeof(C)); 
    show_mem();
    //delete a;
    while (0) {
    }
    return 0;
}

int main()
{
    //test(vector<int>());
    //testSocket();
    //echo_client();
    //thread_test();
    set_test();
    printf("\n");
    set_test2();
}
