#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
void err_sys(const char *s)
{
    //errno = ENOMSG;
    printf("errno = %d\n", errno);
    printf("%s: %s\n", s, strerror(errno));
}

