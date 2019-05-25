//包含头文件
#include "conf.h"

int main(int argc,char **argv)
{
    argcheck(argc, argv);
    if ( argv[1][0] == 'r')
        cfgread( argv[2] );
    else if ( argv[1][0] == 'w')
        cfgcreat( argv[2] );
    return 0;
}
