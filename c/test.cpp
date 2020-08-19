//#define NDEBUG
#include <stdio.h>  
#include <stdint.h>  
#include <stdlib.h>  
#include <math.h>  
#include <limits.h>  
#include <assert.h>
#include "hmtest.h"
//c99 -xc - -lm -g -Wall -include stdio.h -O3 << '---' 
//int main(){printf("Hello from the command line.\n");} 
//---
//./a.out

//cat txt |c99 -xc - -lm -g -Wall -include stdio.h -O3
//./a.out

/** \page onewordtag My page
 * My page content
*/

//// below generated by : DoxAuthor
/**
 * @file test.c
 * @brief This is my test.c file of book 21st Century C
 * @author yyqng
 * @version 0.01
 * @date 2020-1-11
 */
 
//// below generated by : 'Dox ' command in vim
/**
 * @brief
 * This is doxygen_test()
 * @param a
 * This is parm a
 * @param b
 * This is parm b
 * @return
 * return int value
 */
int doxygen_test(int a ,int b)
{
//// below generated by : 'DoxBlock' command in vim
    /**
     * @name
     * @{ */
    /**  @} */
    a++;
    return a;
}

/**
 * @brief
 * This is void print_env()
 * @param a
 * No parm a
 * @return
 * return void value
 */
//reps=10 msg="Ha" ./test
void print_env()
{
    printf("print test1  "
           "print test2\n");
    char *repstext = getenv("reps");
    int reps = repstext ? atoi(repstext) : 2;

    const char *msg = getenv("msg");
    if (!msg) {
        msg = "Hello.";
    }

    for (int i=0; i < reps; i++)
        printf("%s\n", msg);
}

/**
 * @brief
 * This is void print_env2()
 * @param a
 * No parm a
 * @return
 * return void value
 */
void print_env2()
{
}
void switch_case0(int input)
{
    switch (input) {
        case 1:
            printf("1\n");
            printf("111\n");
            break;
        case 2:
            printf("2\n");
            printf("222\n");
            break;
        case 3:
            printf("3\n");
            printf("333\n");
            break;
        default:
            printf("0\n");
            printf("000\n");
            break;
            break;
    }
}
void switch_case_test()
{
    switch_case0(1);
    switch_case0(2);
    switch_case0(15);
}
int main()
{
    hm_test();
//    assert(0);
    //exit(3);
    //abort();
    //int *p = (int*)malloc(sizeof(int));
    //free(p);
    //switch_case_test();
    //print_env();
    assert(1);
    struct DoubleXY {
        double x;
        double y;
    }b[2];
    if (b[0].x > 0 &&
        b[0].y > 0)
    //if (b[0].x > 0)
        printf("hello1");
    if (b[0].x > 0 &&
        b[0].y > 0)
    //if (b[0].x > 0)
        printf("hello2");
}
