#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <sys/stat.h>  
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>  
#include <sys/ipc.h>  
#include <iostream>  
#include <signal.h>  

struct mybuf
{
    int pid;
    char buf[128];
};
int shmtest(int argc, char *argv[]);
