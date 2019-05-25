#include "apue.h"

void err_sys(const char * s)
{
    printf("%s: %s", s , strerror(errno));
}
void sig_usr(int signo)
{
    sigflag = 1;
}

void TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("signal(SIGUSR1) error");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("signal(SIGUSR2) error");
  
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGUSR1);
    sigaddset(&newmask,SIGUSR2);
  
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
        err_sys("SIG_BLOCK error");
}
