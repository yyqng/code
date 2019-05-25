#include "signal.h"
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



