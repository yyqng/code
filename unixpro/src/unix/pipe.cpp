#include "pipe.h"

int unnamed()
{
    int ipipe[2];
    if( pipe(ipipe) < 0)
    {
        printf ("pipe error .\n");
        exit(-1);
    }
    char flag = 0;
    int pid = fork();
    if(pid < 0)
    {
        printf("fork error = %d\n", pid);  
        return -1;
    }
    else if(pid == 0)
    {
        read(ipipe[0] , &flag, 1);
        if(flag == 1)
            printf("In child process.\n");
        exit(0);
    }
    else
    {
        printf("In parent process.\n");
        flag = 1;
        sleep(1);
        write(ipipe[1] , &flag, 1);
    }
    //if (waitpid(pid, NULL, 0)<0)
    if (wait(NULL)<0)
        printf("waitpid error.\n");
    else
        printf("pro end.\n");
    return 0;
}
int namedwrite()
{
    char flag = '1';
    printf("pipe write:\n");
    int fd = 0;
    if ( access( "./pipefifo", F_OK ) == 0 ) 
    {
        printf("pipefifo exsit. open:\n");
        fd = open( "./pipefifo", O_WRONLY );    
    }
    else
    {
        printf("pipefifo isnot exsit, mkfifo:\n");
        fd = mkfifo("./pipefifo", O_WRONLY);    
    }

    if( fd < 0 )
    {
        printf("mkfifo error:%s\n", strerror(errno));
        return -1;
    }

    while(1)
    {
        write(fd, &flag, 1);
        sleep(1);
        printf("namedwrite content :%c\n", flag);
    }
    return 0;
}

int namedread()
{
    char flag = 0;
    printf("pipe read:\n");
    int fd = open("./pipefifo", O_RDONLY);    
    if( fd < 0 )
    {
        printf("namedread error:%s\n", strerror(errno));
        return -1;
    }

    while(1)
    {
        read(fd, &flag, 1);
        sleep(1);
        printf("Read content :%c\n", flag);
    }
    return 0;
}

int pipetest(int argc, char *argv[])
{
    //unnamed();
    if(argc !=2 )
        return -1;
    else if( memcmp(argv[1], "w", 1) == 0 )
        namedwrite();
    else if( memcmp(argv[1], "r", 1) == 0 )
        namedread();
    else return -1 ;
    return 0;  
} 

