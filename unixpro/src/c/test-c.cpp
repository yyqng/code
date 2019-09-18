#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
extern int errno;

//int var[20];
void vartest()
{
    int var[20];
    for( int i=0; i<20; ++i)
	    printf("var[%d] = %d\n", i, var[i]);
}

void definetest()
{
# define I 5
    int i = I;
	printf("i = %d\n", i);
	printf("I = %d\n", I);
}

void definetest2()
{
#define MIN(A,B) ((A) <= (B) ? (A) : (B))
    int a[2] = {1,2};
    int b[2] = {3,4};
    int *p = a;
	printf("MIN(*p++, b[0]) = %d\n", MIN(*p++, b[0]));
	printf("*p = %d\n", *p);

}

void definetest3()
{
//#define eprintf(format, args...) fprintf (stderr, format, ##args)
#define eprintf(format, ...) fprintf (stderr, format, ##__VA_ARGS__)
//未来标准的语法，预计要2020年以后才支持
//#define eprintf(format, ...) fprintf (stderr, format __VA_OPT__(,), __VA_ARGS__)
    eprintf("%d %d\n", 10, 14);
    eprintf("Hello World\n");

}

int const consttest()
{
    int i = 3;
    return i;
}

int const *constPtrtest()
{
    int *p = new int[2];
    p[0] = 1;
    p[1] = 1;
    return p;
}

void sizeofTest()
{
    printf("sizeof(long long)=%ld\n",sizeof(long long));
    printf("sizeof(long )=%ld\n",sizeof(long ));
    ::printf("sizeof(size_t)=%ld\n",sizeof(size_t));
}

int printfTest(void) {
//    char s[] = "abcdefg";
    int i = 12345;
    int j = -45;
    double d = 123.45678;
    double e = 23.45678;

//    printf("%s\n", s);
//    printf("%.*s\n", 3, s);
//    printf("%#.8x\n", s);
//    printf("%#p\n\n", s);
//
//    printf("%d\n", i);
    printf("%*d\n", 6, i);
    printf("%*d\n", 6, j);
//    printf("%0*d\n\n", 10, i);
//
//    printf("%f\n", d);
//    printf("%.*f\n", 3, d);
//    printf("%20.10f\n", d);
    printf("%*.*f\n\n", 20, 10, d, d);
    printf("%*.*f\n\n", 20, 10, e, e);

    return 0;
}
int main(int argc, char *argv[])
{
    //vartest();
    //definetest();
    //int k = consttest();
    //k = 4;
    //printf("k is %d\n", k);
    //int const *p = constPtrtest();
    //p[0] = 4;
    //printf("p[0] is %d\n", p[0]);
    //sizeofTest();
    //definetest2();
    //definetest3();
    printfTest();
}

