#include"test.h"
#include<bitset>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) do { perror(m); exit(EXIT_FAILURE);} while(0)



const int SIZE = 10;

template <typename Container>
void test(Container c)
{
    typedef typename iterator_traits<typename Container::iterator>::value_type Vtype;
    for (int i = 0; i < SIZE; ++i) {
        c.insert(c.end(), Vtype());
    }
}

int testSocket()
{
    int i = 0x12345678;
    char *p = (char *)&i;
    printf("%0x, %0x, %0x, %0x \n", p[0], p[1], p[2], p[3]);

    int j = htonl(i);
    p = (char *)&j;
    printf("%0x, %0x, %0x, %0x \n", p[0], p[1], p[2], p[3]);

    const char *cp = "192.168.0.100";
    in_addr_t addr = inet_addr(cp);
    printf("addr = %d\n", ntohl(addr));

    struct in_addr in;
    in.s_addr = addr;
    p = inet_ntoa(in);
    printf("p = %s\n", p);

    return 0;
}

int echo_client()
{
    int lfd;
    //if (lfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) < 0) {
    if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ERR_EXIT("socket error\n");
    }

    return 0;
}

int main()
{
    //test(vector<int>());
    //testSocket();
    echo_client();
}
