#include "signal.h"
void sig_int(int signo )
{
    std::cout<<"int interrupt"<<std::endl;
    //exit(-1);//注释掉此句,函数返回后程序继续执行
}

void sig_term(int signo )
{
    std::cout<<"term interrupt"<<std::endl;
}


void sig_kill(int signo )
{
    std::cout<<"kill interrupt"<<std::endl;
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
        std::cout<<"SIGFPE ERR"<<std::endl;
    }

    if( signal(SIGINT , sig_int) == SIG_ERR) //CTR+C触发
    {
        std::cout<<"SIGINT ERR"<<std::endl;
    }

    if( signal(SIGTERM , sig_term) == SIG_ERR) //kill pid触发
    {
        std::cout<<"SIGTERM ERR"<<std::endl;
    }

    if( signal(SIGKILL , sig_kill) == SIG_ERR) //kill -9 pid触发
    {
        std::cout<<"SIGKILL ERR"<<std::endl;
    }

    sleep(30);
    sleep(30);
    //int i = 2/0; //exit(-1);
    std::cout<<"Program is going on"<<std::endl;
}



