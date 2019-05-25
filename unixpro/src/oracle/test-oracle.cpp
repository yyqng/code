#include "oracle.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <signal.h>


int
main(int argc, char *argv[])
{
    DB &db1 = sDB;
    db1.oracle_insert();
    db1.oracle_select();
    db1.oracle_delete();
    db1.oracle_select();
    db1.stop();
    return 0;
}
