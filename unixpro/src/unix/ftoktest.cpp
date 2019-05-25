#include "ftoktest.h"
int ftoktest(int argc, char *argv[])
{  
    if(argc <= 1)
        return -1;
    key_t semkey;  
    if(( semkey = ftok( argv[1], 127 ))<0)  
    {  
        printf("ftok failed\n");  
        exit(EXIT_FAILURE);  
    }     
    printf("ftok ok ,semkey = %d\n", semkey);  
    return 0;  
} 

