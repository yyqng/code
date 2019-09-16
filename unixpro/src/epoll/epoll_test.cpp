#include "utility.h"

int main(int argc, char *argv[])
{
    if(argc != 2 )
    {
        printf("Usage server: ./epoll_test s\n");
        printf("Usage client: ./epoll_test c\n");
        return -1;
    }
    if( argv[1][0] == 's' )
        epoll_server(argc, argv);
    if( argv[1][0] == 'c' )
        epoll_client(argc, argv);
    return 0;
}
