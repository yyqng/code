#include "msg.h"

int msgcreat()
{
    int key = ftok( "./a.c", 'a');
    if( key < 0 )
    {
        printf("ftok error : %s", strerror(errno));
        return -1;
    }
    int msgid = msgget( key, IPC_CREAT|0777);
    if( msgid < 0 )
    {
        printf("msgget error : %s", strerror(errno));
        return -2;
    }
    system("ipcs -q");
    return msgid;

}

int msgclose(int msgid)
{
    int ret = msgctl(msgid, IPC_RMID, NULL);
    if( ret < 0 )
    {
        printf("msgctl error msgid = %d: %s", msgid, strerror(errno));
        return -2;
    }
    system("ipcs -q");
    return ret;
}

int const BUFSIZE = 128;
struct mymsg
{
    int mtype;
    char mtext[BUFSIZE];
};

void server(int msgid)
{
    //while(1)
    {
        struct mymsg ssendbuf;
        memset(ssendbuf.mtext, 0, BUFSIZE);
        memcpy(ssendbuf.mtext, "hello from server.\n", BUFSIZE);
        ssendbuf.mtype = 200;
        printf("server msgsnd\n");
        if (msgsnd(msgid, &ssendbuf, strlen(ssendbuf.mtext), 0) < 0)
        {
            printf("Server msgsnd error : %s", strerror(errno));
            exit(-1);
        }
        printf("Server msgsnd success : %s\n", ssendbuf.mtext);
        sleep(1);

        struct mymsg rsvbuf;
        printf("Server rsvbuf\n");
        memset(rsvbuf.mtext, 0, BUFSIZE);
        rsvbuf.mtype = 100;
        printf("server msgrcv \n");
        if (msgrcv(msgid, &rsvbuf, BUFSIZE, rsvbuf.mtype, 0) < 0)
        {
            printf("Server msgrcv error : %s", strerror(errno));
            exit(-1);
        }
        printf("Server msgrcv success : %s\n", rsvbuf.mtext);
        sleep(1);
    }
}

void client(int msgid)
{
    //while(1)
    {
        struct mymsg rsvbuf;
        memset(rsvbuf.mtext, 0, BUFSIZE);
        rsvbuf.mtype = 200;
        printf("client rsvbuf \n");
        if( msgrcv(msgid, &rsvbuf, BUFSIZE, rsvbuf.mtype, 0) < 0 )
        {
            printf("client msgrcv error : %s", strerror(errno));
            exit(-1);
        }
        printf("client rsvbuf success = %s\n", rsvbuf.mtext);

        struct mymsg sendbuf;
        memset(sendbuf.mtext, 0, BUFSIZE);
        sendbuf.mtype = 100;
        memcpy(sendbuf.mtext, "hello from client.\n", BUFSIZE);
        printf("strlen(sendbuf.mtext) = %d\n", (int)strlen(sendbuf.mtext) );
        printf("client msgsnd \n");
        if ( msgsnd(msgid, &sendbuf, strlen(sendbuf.mtext), 0) < 0)
        {
            printf("client msgsnd error : %s", strerror(errno));
        }
        printf("client msgsnd success : %s\n", sendbuf.mtext);
        sleep(1);
    }
}
int gmsgid = 0;
void myfun(int signo )
{
    if(gmsgid > 0)
        msgclose( gmsgid );
    std::cout<<"int interrupt,signo = " << signo <<std::endl;
    //exit(-1);//注释掉此句,函数返回后程序继续执行
}


int const CN = 1;
int msgtest(int argc, char *argv[])
{
    signal(SIGINT, myfun);
    gmsgid = msgcreat();
    int pid[CN] ;
    for(int i=0; i<CN; ++i)
    {
        pid[i] = fork();
        if( pid[i] > 0)
        {
            server( gmsgid );
        }
        else if( pid[i] == 0)
        {
            client( gmsgid );
            exit(0);
        }
        else
        {
            printf("fork error.\n");
        }
    }

    for(int i=0; i<CN; ++i)
    {
        if(waitpid(pid[i], NULL, 0) < 0 )
            printf("pid = %d, wait error.\n", getpid());
        else
        {
            printf("pid = %d, wait success.\n", getpid());
        }
    }
    return 0;  
} 

