#include<iostream>
#include<vector>
#include<algorithm>
#include <iterator>
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <deque>
#include <iterator>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
//g++ primer.cpp -g -std=c++11
using namespace std;
 
#define VMRSS_LINE 17
#define VMSIZE_LINE 13
#define PROCESS_ITEM 14
 
typedef struct {
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
}Total_Cpu_Occupy_t;
 
 
typedef struct {
    unsigned int pid;
    unsigned long utime;  //user time
    unsigned long stime;  //kernel time
    unsigned long cutime; //all user time
        unsigned long cstime; //all dead time
}Proc_Cpu_Occupy_t;
 
class A
{
public:
    A() = default;
//    A(const A &a1) = delete;
    A(int a, int b): a(a), b(b) {};
    int a;
    int b;
};
void algo();
int otst();

int testmem();
unsigned int get_proc_virtualmem(unsigned int pid);
