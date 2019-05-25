#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "malloc.h"
#include "ftoktest.h"
#include "signaltest.h"
extern int errno;



void fun1()
{
	printf("Hello,fun1\n");
}

void fun2()
{
	printf("Hello,fun2\n");
}

void err_sys(const char *s)
{
	printf("errno=%d, %s\n", errno, s);
}
void atexittest1()
{
   if( atexit( fun1 ) != 0 )
	   err_sys("can't register fun1");
}

void atexittest2()
{
   if( atexit( fun2 ) != 0 )
	   err_sys("can't register fun2");
}

void
argvtest(int argc, char *argv[])
{
	for(int i=0; i< argc; ++i)
	{
		printf("argv[%d]: %s\n" , i , argv[i]);
	}

}
void envtest()
{
	extern char **environ;
	
	for( int i=0 ; environ[i] != NULL; ++i)
	{
		printf("environ[ %d ] is %s \n" , i, environ[i]);
	}
}
void errsys( const char *c )
{
    printf("errno: %2d\t%s\n", errno, strerror( errno ));
    printf("%s\n", c);
    exit(-1);
}
void *myrealloc(void*p,size_t newsize)
{
    size_t oldsize = malloc_usable_size(p);
    size_t copysize = 0;
    if( p )
    {
        if( oldsize == newsize )
            return p;
        else if ( oldsize < newsize )
            copysize = oldsize;
        else
            copysize = newsize;

        void *vp = malloc( newsize );
        if(!vp)
            return NULL;
        memcpy( vp , p , copysize);
        free(p);
        p = vp;
    }
    else
    {
        p = malloc( newsize );
    }
    return p;
}

void
sizeoftest(int argc, char *argv[])
{
    printf("sizeof(int)       is %lu\n",sizeof(int) );
    printf("sizeof(long)      is %lu\n",sizeof(long) );
    printf("sizeof(long long) is %lu\n",sizeof(long long) );
    printf("sizeof(float)     is %lu\n",sizeof(float) );
    printf("sizeof(double)    is %lu\n",sizeof(double) );
    printf("sizeof(char )     is %lu\n",sizeof(char) );
    printf("sizeof(short)     is %lu\n",sizeof(short) );
    printf("sizeof(unsigned)  is %lu\n",sizeof(unsigned) );
    printf("sizeof(signed)    is %lu\n",sizeof(signed) );
}
void
alloctest(int argc, char *argv[])
{
    int *ip = (int *)malloc(10 * sizeof(int));
    if ( !ip )
        errsys("malloc");
    printf("sizeof(ip) : %lu \n",  sizeof(ip));
    printf("sizeof(ip[0]) %lu \n",  sizeof(ip[0]));
    printf("malloc_usable_size(ip): %lu \n",  malloc_usable_size(ip));
    int arrszie = malloc_usable_size(ip)/sizeof(ip[0]);
    for(int i=0; i< arrszie; ++i)
    {
        ip[i] = i;
        printf("ip[%d] = %d\n", i , ip[i]);
    }

    if ( myrealloc( ip, 5 * sizeof(int)) == NULL )
        errsys("realloc");
    printf("sizeof(ip) : %lu \n",  sizeof(ip));
    printf("sizeof(ip[0]) %lu \n",  sizeof(ip[0]));
    printf("malloc_usable_size(ip): %lu \n",  malloc_usable_size(ip));
    arrszie = malloc_usable_size(ip)/sizeof(ip[0]);
    for(int i=0; i< arrszie; ++i)
    {
        printf("ip[%d] = %d\n", i, ip[i]);
    }
    free(ip);
}
int
main(int argc, char *argv[])
{
   singnaltest( argc , argv);
   //atexittest1();
   //atexittest2();
   //argvtest( argc, argv );
   //envtest();
   //alloctest( argc, argv );
   //sizeoftest( argc, argv );
   //ftoktest( argc, argv );

}
