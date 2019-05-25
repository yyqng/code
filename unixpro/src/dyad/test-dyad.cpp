#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "dyad.h"

void printdyadUsage()
{
	printf("Usage:\n");
	printf("      test-dyad httpserv\n");
	printf("      test-dyad httpserv2\n");
	printf("      test-dyad echoserv\n");
	printf("      test-dyad daytime\n");
	printf("      test-dyad ircbot\n");
	printf("      __cplusplus:%d\n", __cplusplus);
	exit(-1);
}
int
main(int argc, char *argv[])
{
#ifdef DYAD_TESTPRO
	if (argc != 2 )
		printdyadUsage();
	if( !strcmp(argv[1], "httpserv") )
		httpserv();
	else if ( !strcmp(argv[1], "httpserv2") )
		httpserv2();
	else if ( !strcmp(argv[1], "echoserv") )
		echoserv();
	else if ( !strcmp(argv[1], "daytime") )
		daytime();
	else if ( !strcmp(argv[1], "ircbot") )
		ircbot();
	else
		printdyadUsage();

#endif
}
