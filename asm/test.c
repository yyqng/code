#include <stdio.h>  
#include <stdint.h>  
#include <math.h>  
//#include <string>
//#include <vector>
//#define _Conn_(x,y)  (x##y)
//#define Conn(x,y)  _Conn_(x,y)
//#define _Conn_(x,y)  (x##e##y)
//#define Conn(x,y)  _Conn_(x,y)
//#define ToChar(x)  #@x ----------wrong 
//#define ToString(x) #x
//using namespace std;
//
//gcc test.c -std=c99 -lm -g

void int64_print_test()
{
    int64_t x = 888;
    int64_t y = 999;
    printf("x=%d, y=%d\n", x, y);
}

int main()
{
    int64_print_test();
}
