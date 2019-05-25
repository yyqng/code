#include "fileio.h"

void ls(int argc , char *argv[] )
{
    DIR           *dp;
    struct dirent *dirp;

    if(argc != 2)
    {
        exit(-1);
        //err_qiut("usage : ls directory_name ");
    }

    if(( dp = opendir(argv[1])) == NULL)
        exit(-1);
        //err_sys(can't open %s", argv[1]);
    while( (dirp = readdir(dp)) != NULL)
        printf("%s\n",dirp->d_name);

    closedir(dp);
    exit(0);
}


void copy_stdin_to_stdout(int argc , char * argv[])
{
        int const BUFFSIZE = 4096;
        int n ;
        char buffer[BUFFSIZE];

        while(( n = read(STDIN_FILENO, buffer ,BUFFSIZE) ) > 0 )
        {
                if ( write (STDOUT_FILENO ,buffer ,n ) != n )
                {
                        exit(-1);
                }
        }

        if(n < 0 )
        {
                exit(-1);
        }
}

void copy_char_stdin_to_stdout(int argc , char * argv[])
{
        int c ;
        while ((c = getc(stdin)) != EOF )
        {
                if (putc (c ,stdout ) == EOF)
                {
                        exit(-1);
                }
        }

        if( ferror(stdin) )
        {
                exit(-1);
        }
}


void lseek_test(int argc , char * argv[])
{
        if (lseek(STDIN_FILENO, 0 , SEEK_CUR) == -1 )
        {
                printf("lseek error \n");
        }
        else
        {
                printf( "lseek ok \n");
        }
}

#include <fcntl.h>
void creat_holefile(int argc , char * argv[])
{
    char buff1[]="abcdefg";
    char buff2[]="ABCDEFG";
    
    int fd;
    if( (fd = creat( "holefile" , O_CREAT) ) < 0)
    {
            printf( "creat error" );
    }

    if( write( fd , buff1, 10 ) < 0) 
    {
            printf( "wirte error" );
    }

    if( lseek( fd , 16384, SEEK_SET) == -1 ) 
    {
            printf( "lseek error" );
    }

    if( write( fd , buff2, 10) < 0) 
    {
            printf( "write error" );
    }
}

#include <sys/stat.h>
void lstat_test(int argc , char * argv[])
{
        int i;
        struct stat buf;
        for(i=1; i<argc ; ++i)
        {
                printf("%s:  ",argv[i]);
                if(lstat(argv[i] , &buf)<0)
                {
                        printf("lstat error\n");
                        continue;
                }
                if( S_ISREG(buf.st_mode))
                        printf("regular file\n");
                else if( S_ISDIR(buf.st_mode))
                        printf("directory\n");
                else if( S_ISCHR(buf.st_mode))
                        printf("character specail\n");
                else if( S_ISBLK(buf.st_mode))
                        printf("block specail\n");
                else if( S_ISFIFO(buf.st_mode))
                        printf("fifo\n");
                else if( S_ISLNK(buf.st_mode))
                        printf("link\n");
                else if( S_ISSOCK(buf.st_mode))
                        printf("socket file\n");
                else 
                        printf("unkown mode\n");

        }
}

void printData( const char *data, uint32_t dataSize,  const char *subject = NULL)
{
    if(data == NULL || dataSize<=0)
    {
        return;
    }
    std::ostringstream outfile;
    
    time_t t = time(NULL); //get time.
    char ctime[32] = {0};
    sprintf( ctime, "%d" , (int)t );
    static int emailcount = 0;
    char ccount[32] = {0};
    ++emailcount;
    sprintf( ccount, "%d" , emailcount );
    if(subject == NULL)
    {
        outfile<<"/root/pktspy/" << ctime << ccount << ".html";
    }
    else
    {
        outfile<<"/root/pktspy/" << ctime << subject << ".html";
    }

    FILE *fp = fopen(outfile.str().data() , "a");
    if( NULL == fp )
    {
        return;
    }

    fwrite(data , dataSize , 1 , fp);
    fclose(fp);
    fp = NULL;
}
