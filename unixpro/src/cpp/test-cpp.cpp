#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "Statis.h"
#include "Complex.h"
#include "String.h"
#include "test-cpp.h"
#include "polymorphic.h"

int func(int*p);
int
main(int argc, char *argv[])
{
/*
    if (argc == 2 && !memcmp(argv[1] , "w", 1))
        writer( );
    else if (argc == 2 && !memcmp(argv[1] , "r", 1))
        reader( );
    else
    {
        printf("Usage shm write: ./test-cpp w\n");
        printf("      shm read : ./test-cpp r\n");
    }
*/
    //sStatis.AddStatis(READ_PKT_SUC_CNT,1);
    //creatshm();
    //cpptest();
    //stringtest();
    //lambdatest();
    //::func( NULL );
    //regextest1();
    //regextest2();
    //polymorphic();
    rightValueTest();
}

int func(int*p)
{
    *p = 0;
    return 0;
}
