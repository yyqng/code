#include "process.h"
#include "error.h"

static volatile sig_atomic_t sigflag;
static sigset_t newmask;
static sigset_t oldmask;
static sigset_t zeromask;

static void sig_usr(int signo)
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
void TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);
}
void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);
}

void WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
        err_sys("SIG_SETMASK error");
}
void WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
        err_sys("SIG_SETMASK error");
}



void printXXID()
{
    printf("GID  %ld\n", (long)getgid());
    printf("EGID %ld\n", (long)getegid());
    printf("UID  %ld\n", (long)getuid());
    printf("EUID %ld\n", (long)geteuid());
    printf("PID  %ld\n", (long)getpid());
    printf("PPID %ld\n", (long)getppid());
}

void fork_execlp()
{
    int const MAXLINE = 2048;
    char buffer[MAXLINE];
    pid_t pid;
    int status;
    printf("%% ");
    while(fgets( buffer , MAXLINE , stdin ) != NULL)
    {
        if(buffer[strlen(buffer) - 1] == '\n')
                buffer[ strlen(buffer) - 1 ] = 0;
        if( (pid = fork() ) < 0)
        {
            exit(-1);
        }
        else if(pid == 0)
        {
            execlp(buffer, buffer , ( char *)0);
            printf ("couldn't execute %s ", buffer);
            exit(127);

        }
    }

    if( (pid = waitpid(pid , &status, 0) )  < 0 )
    {
        err_sys("waitpid error");
    }
    printf ( " %% \n" );
}

void forktest()
{
    printf("fork test :  ");
    int j = 0;
    if ( fork() == 0 ) 
    {
        /* child process */
        for ( int i = 1; i <2; i ++ ) 
             printf("This is child process\n");
        ++j;
    }
    else 
    {
        sleep(1);
        /* father process */
        for ( int i = 1; i <2; i ++ ) 
            printf("This is parent process\n");
    }
    printXXID();
    printf("j = %d\n", j);
    printf("\n\n");
}

void vforktest()
{
    printf("vfork test :  \n");
    int j = 0;
    if ( vfork() == 0 ) 
    {
        printf("This is child process\n");
        ++j;
        printXXID();
        printf("j = %d\n", j);
        printf("\n\n");
        //_exit终止进程但不运行终止处理程序或信号处理程序
        _exit(0);
    }
    else 
    {
        printf("This is parent process\n");
    }
    //Child proccess runs in father proccess address space.
    //Father proccess runs after Child proccess exit
    printXXID();
    printf("j = %d\n", j);
}


void printExitStatus(int status)
{
    if(WIFEXITED(status))
        printf("Normail exit,   status        = %d\n", WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("Abnormal exit,  signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
    WCOREDUMP(status) ? "( Core file generated)": "");
#else
    "");
#endif
    else if(WIFSTOPPED(status))
        printf("Child stopped,  signal number = %d\n", WSTOPSIG(status));
}

void normalExit()
{
    int status;
    pid_t pid;
    if( (pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);
    if( wait( &status ) != pid )
        err_sys("wait error");
    printExitStatus(status);
}


void abortExit()
{
    int status;
    pid_t pid;
    if( (pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();
    if( wait( &status ) != pid )
        err_sys("wait error");
    printExitStatus(status);
}


void chu0Exit()
{
    int status;
    pid_t pid;
    if( (pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        status = 0;
        //status /= 0;
    if( wait( &status ) != pid )
        err_sys("wait error");
    printExitStatus(status);
}
void exittest()
{
    normalExit();
    abortExit();
    chu0Exit();
}

static void charatatime(const char *str)
{
    const char *p;
    int c;
    setbuf(stdout, NULL);
    for(p = str; (c = *p++) != 0 ; )
        putc(c, stdout);
}

void competetest()
{
    pid_t pid;
    if( ( pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        charatatime( "Output from child\n" );
    }
    else
    {
        charatatime( "Output from father\n" );
    }
    exit(0);
}
void nocompetetest()
{
    pid_t pid;
    TELL_WAIT();
    if( ( pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        WAIT_PARENT();
        charatatime( "Output from child\n" );
    }
    else
    {
        charatatime( "Output from father\n" );
        TELL_CHILD(pid);
    }
    err_sys("wait error");
    exit(0);
}
