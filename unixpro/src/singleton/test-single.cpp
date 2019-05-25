#include "single.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <signal.h>


int
main(int argc, char *argv[])
{
    STSingleton::GetInstance();
    return 0;
}
