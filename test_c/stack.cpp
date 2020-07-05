#include<iostream>
#include<stdio.h>
//g++ stack.cpp -g

static int wtest()
{
   //int a : 1 = 0;
   int a  = 1 << 31;
   printf("%d.\n", a);
   return 0;
}

int stack_test_cpp()
{
    //char a='a';
    //char b[1000000]={'x'};
    //b[100000]='u';
    //char c='c';
    //char *pa = &a;
    //char *pc = &c;
    //std::cout<<static_cast<const void *>(pa)<<std::endl;
    //std::cout<<static_cast<const void *>(b)<<std::endl;
    //std::cout<<static_cast<const void *>(pc)<<std::endl;
    //std::cout<<static_cast<const void *>(pc) - static_cast<const void *>(pa)<<std::endl;
    wtest();
    return 0;
}
