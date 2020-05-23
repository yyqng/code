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
//g++ primer.cpp -g -std=c++11
using namespace std;
class A
{
public:
//    A(const A &a1) = default;
//    A(const A &a1) = delete;
    A(int a, int b): a(a), b(b) {};
    int a;
    int b;
};
void algo();
int otst();
