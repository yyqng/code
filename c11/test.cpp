#include <stdio.h>  
#include <stdint.h>  
#include <stdlib.h>  
#include <math.h>  
#include <limits.h>  
#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

void print_env()
{
    char *repstext = getenv("reps");
    int reps = repstext ? atoi(repstext) : 2;

    const char *msg = getenv("msg");
    if (!msg) {
        msg = "Hello.";
    }

    for (int i=0; i < reps; i++)
        printf("%s\n", msg);
}

void print_sizeof_longlong()
{
    int size = sizeof(long long int);
    printf("sizeof(long long int) = %d byte\n", size);
    size = sizeof(long long);
    printf("sizeof(long long) = %d byte\n", size);

    size = sizeof(unsigned long long int);
    printf("sizeof(unsigned long long int) = %d byte\n", size);
    size = sizeof(unsigned long long);
    printf("sizeof(unsigned long long) = %d byte\n", size);
}

void init_list()
{
    std::vector<int> v { 1, 2, 3, 4 };
    std::map<int, float> m = { {1, 1.0f}, {2, 2.0f}, {3, 3.0f} };
}

void nulltest(int)
{
    printf("nulltest(int)\n");
}

void nulltest(void*)
{
    printf("nulltest(void*)\n");
}

void nullptr_test()
{
   int *p1 = nullptr;
   int *p2 = 0;
   int *p3 = NULL;
   nulltest(p1);
   nulltest(p2);
   nulltest(p3);
   printf("above: call unlltest(void*) ============\n");
   nulltest(nullptr);
   nulltest(0);
   //nulltest(NULL);    //compiling error
}

int constexpr size()
{
    return 0;
}

void const_test()
{
    constexpr int mf = 20;			//20是常量表达式
    constexpr int limit = mf + 1;   //mf+1是常量表达式
    constexpr int sz = size();      //只有当size是一个constexpr函数时，才是一条正确的声明语句
}

void typedef_test()
{
    struct Test {
        int test0;
        int test1;
    };
    using sT = Test;
    sT a;
    auto size = sizeof(a);
    printf("sizeof(a) = %d\n", size);
    size = sizeof(sT);
    printf("sizeof(sT) = %d\n", size);

    sT *p;
    sT v[5];
    size = sizeof(p);
    printf("sizeof(p) = %d\n", size);
    size = sizeof(v);
    printf("sizeof(v) = %d\n", size);
    p = v;
    size = sizeof(p);
    printf("sizeof(p) = %d\n", size);
}

void auto_test()
{
    auto i = 5 + 8;
    auto size = sizeof(i);
    printf("sizeof(i) = %d\n", size);

    auto j = 5 + 8.0;
    size = sizeof(j);
    printf("sizeof(i) = %d\n", size);
}

int iret(int r)
{
    return r;
}
double dret(double r)
{
    return r;
}
void decltype_test()
{
    decltype(dret(0)) a = 1;
    auto size = sizeof(a);
    printf("sizeof(a) = %d\n", size);

    decltype(iret(0)) b = 1;
    size = sizeof(b);
    printf("sizeof(b) = %d\n", size);
}

void for_test()
{
    vector<vector<int>> v{{1, 2}, {3, 4}};
    v = {{5, 6}, {7, 8}};
    for(auto &v1 : v) {
        for(auto &e : v1) {
            e *= 2;
            cout << e << endl;
        }
    }

    auto it1 = v.begin();	//vector<int>::iterator
    auto it3 = v.cbegin();  //vector<int>::const_iterator
    const vector<vector<int>> cv = {{1, 2}, {3, 4}};
    auto it2 = cv.begin();  //vector<int>::const_iterator

    int ia[] = {0,1,2,3,4,5,6,7,8,9};
    auto size = end(ia) - begin(ia);
    printf("sizeof(ia) = %d\n", size);

    printf("8/3 = %d\n", 8/3);
    printf("-8/3 = %d\n", -8/3);
}


void string_msg(initializer_list<string> il)
{
	for(auto beg = il.begin(); beg != il.end(); ++beg){
		cout<<*beg <<endl;
	}
}

void string_msg(vector<string>sv)
{
	for(auto beg = sv.begin(); beg != sv.end(); ++beg){
		cout<<*beg <<endl;
	}
}

vector<string> process(){
    return {"process1", "process2"};
}

void initializer_list_test()
{
    string s1 = "hello1";
    string s2 = "hello2";
    string_msg({s1, s2});
    string_msg(process());
}

//auto func(int i ) ->int(*)[10];
//auto func(int i ) ->int(*)[10]
//{
//    int *p = new int[10];
//    return p;
//}

auto func2(int i ) ->int(*);
auto func2(int i ) ->int(*)
{
    int *p = new int[10];
    return p;
}

int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};
auto fa(int i)->int(*)[5]
{
    return (i % 2) ? &odd : &even;
}

void fa_test()
{
    int(*o)[5];
    o = fa(65);
    cout << *o << endl;
    cout << **o << endl;
}

decltype(odd) *fd(int i)
{
    return (i % 2) ? &odd : &even;
}

void fd_test()
{
    int(*o)[5];
    o = fd(60);
    cout << *o << endl;
    cout << **o << endl;
}

constexpr int const_p(int a) {return 1 + a;};
constexpr int const_nop() {return 1;};

void constexpr_test()
{
    constexpr int foo1 = const_p(10); // const_nop必须为constexpr 
    int foo2 = const_p(11);
    cout << foo1 << endl;
    cout << foo2 << endl;

    constexpr int foo3 = const_nop(); // const_nop必须为constexpr 
    int foo4 = const_nop();
    cout << foo3 << endl;
    cout << foo4 << endl;
}

class TC {
};

int main()
{
    //print_env();
    //print_sizeof_longlong();
    //nullptr_test();
    //const_test();
    //typedef_test();
    //auto_test();
    //decltype_test();
    //for_test();
    //initializer_list_test();
    //fa_test();
    //fd_test();
    //constexpr_test();
    TC tc;
}
