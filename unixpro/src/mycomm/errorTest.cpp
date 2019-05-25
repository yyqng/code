#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int errno;

void errortest(int argc , char *argv[] )
{
        fprintf(stderr, "EACCES: %s\n", strerror(EACCES) );
        errno = ENOENT;
        perror(argv[0]);
        exit(0);
}



int
main(int argc, char *argv[])
{
   errortest( argc , argv);

}
