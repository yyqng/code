#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
extern int errno;
using namespace std;

void sig_int(int signo );
void sig_fpe(int signo );
void singnaltest(int argc , char *argv[] );
