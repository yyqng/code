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
int test();

int set_mem_test();
unsigned int get_proc_virtualmem(unsigned int pid);
