#include "shm.h"

int shmdel(int shmid)
{
    //printf("Before delete : \n");
    //system("ipcs -m");

    //char id[32] = {0};
    //sprintf(id, "%d", shmid);
    //std::string scmd = id;
    //scmd = "ipcrm -m " + scmd;
    //printf("scmd = %s\n", scmd.c_str());
    //system(scmd.c_str());

    shmctl(shmid, IPC_RMID, NULL);

    //printf("After delete : \n");
    //system("ipcs -m");
    //system("ipcs -q");
    //system("ipcs -s");
    return 0;
}

int shmcreat(mybuf *&p)
{
    key_t key = ftok("./shm", 'a');
    if ( key < 0 )
    {
        printf("ftok error: %s.\n", strerror(errno));
        return -1;
    }
    int shmid = shmget(key, 128, IPC_CREAT | 0777) ;
    //int shmid = shmget(IPC_PRIVATE, 128, 0) ;
    //shmid = 1277953;
    if ( shmid < 0 )
    {
        printf("shmget error: %s.\n", strerror(errno));
        return -2;
    }
    printf("creat shm success.shmid = %d, key = %x.\n",shmid, key);
    //system("ipcs -m");

    p = (mybuf *)shmat(shmid, NULL, 0);
    if ( !p )
    {
        printf("shmat error: %s.\n", strerror(errno));
        shmdel(shmid);
        return -3;
    }
    return shmid;
}


int shmwrite()
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

int shmread()
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
void ServershmRW(mybuf* bufp)
{
    //write
    std::string s = "Hello from Server.\n";
    //printf("Server input:\n");
    //std::cin >> s;
    mybuf tmpbufp;
    tmpbufp.pid = getpid();
    memcpy(tmpbufp.buf, s.c_str(), s.length());
    memcpy(bufp, &tmpbufp, sizeof(mybuf));

    //pause
    //printf("Server pause begin.\n");
    pause();
    //printf("Server pause endding.\n");

    //read
    memcpy(&tmpbufp, bufp, sizeof(mybuf));
    printf("Server get share mem : pid = %d, buf = %s\n", tmpbufp.pid, tmpbufp.buf);
    sleep(3);
    kill(bufp->pid, SIGUSR1);
}
void ClientshmRW(mybuf* bufp)
{
    //read
    int ppid ;
    mybuf tmpbufp;
    memcpy(&tmpbufp, bufp, sizeof(mybuf));
    printf("Client get share mem : pid = %d, buf = %s\n", tmpbufp.pid, tmpbufp.buf);
    ppid = tmpbufp.pid;

    //write
    std::string s = "Hello from Client.\n";
    //printf("Client input:\n");
    //std::cin >> s;
    tmpbufp.pid = getpid();
    memcpy(tmpbufp.buf, s.c_str(), s.length());
    memcpy(bufp, &tmpbufp, sizeof(mybuf));
    sleep(3);
    kill(ppid, SIGUSR2);

    //pause
    //printf("Client pause begin.\n");
    pause();
    //printf("Client pause endding.\n");
}
void myfunClient(int signum)
{
    printf("Client receive signum = %d\n", signum);
}
void myfunServer(int signum)
{
    printf("Server receive signum = %d\n", signum);
}
int shmtest(int argc, char *argv[])
{

    int i=1;
    int pid = fork();
    if(pid > 0)
    {
        struct mybuf *p = NULL;
        int shmid = shmcreat(p);
        if ( shmid <=0 || !p)
            return -1;
        signal(SIGUSR2, myfunServer);
        while(i)
        {
            ServershmRW( p );
            --i;
        }
        shmdel(shmid);
    }
    else if(pid == 0)
    {
        struct mybuf* p = NULL;
        int shmid = shmcreat(p);
        if ( shmid <=0 || !p)
            return -1;
        signal(SIGUSR1, myfunClient);
        while(i)
        {
            ClientshmRW( p );
            --i;
        }
        shmdel(shmid);
    }
    else
    {
        printf("fork() error.\n");
    }
    /*
    if(argc !=2 )
        return -1;
    else if( memcmp(argv[1], "w", 1) == 0 )
        shmwrite();
    else if( memcmp(argv[1], "r", 1) == 0 )
        shmread();
    else return -1 ;
    */
    return 0;  
} 

