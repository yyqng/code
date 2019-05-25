#include "signaltest.h"

void sig_int(int signo )
{
        std::cout<<"int interrupt"<<std::endl;
        //exit(-1);//注释掉此句,函数返回后程序继续执行
}

void sig_fpe(int signo )
{
        std::cout<<"fpe interrupt"<<std::endl;
        exit(-1);//注释掉此句将导致死循环
}

void singnaltest(int argc , char *argv[] )
{
        if( signal(SIGFPE , sig_fpe) == SIG_ERR)
        {
            std::cout<<"catch SIGFPE error"<<std::endl;
        }

        if( signal(SIGINT , sig_int) == SIG_ERR) //CTR+C触发
        {
            std::cout<<"catch SIGINT error"<<std::endl;
        }

        sleep(3);
        //int i = 2/0; //exit(-1);
        std::cout<<"Program is going on"<<std::endl;
}

void killtest(int argc , char *argv[] )
{
    if (argc != 2)
    {
        printf("arg error.\n");
        exit(-1);
    }
    int pid = atoi(argv[1]);
    //int sig = atoi(argv[2]);
    //kill(pid, sig);
    //kill(pid, SIGKILL);
    if (kill(pid, SIGKILL) < 0 )
        printf("kill error: %s\n ",strerror(errno));
    else
        printf("kill susccess");
}

//int sigfun(int signum)
void sigfun(int signum)
{
    printf("Catch sigfun. signum = %d\n",signum);
    exit(0);
}

void killchildtest(int argc , char *argv[] )
{
    int pid = fork();
    signal(SIGINT, sigfun);
    //signal(SIGCHLD, sigfun);
    if(pid <0)
        printf("fork error.\n");
    else if (pid ==0)
    {
        printf("child raise before.\n");
        raise(SIGSTOP);
        printf("child raise after.\n");
        exit(0);
    }
    else
    {
        //pause();
        sleep(5);
        printf("This is parent, pid = %d\n", pid);
        if( waitpid(pid, NULL, WNOHANG) == -1)
            printf("wait error.\n");
        else 
        {
            if (kill(pid, SIGKILL) < 0 )
                printf("kill error.\n");
            else
                printf("kill susccess.\n");
        }
        printf("alarm before.\n");
        //pause();
        alarm(5);
        printf("alarm after.\n");
        while(1)
        {
            sleep(1);
            printf( "Process is going on.\n" );
        }
    }
}
