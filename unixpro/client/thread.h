#include <bitset>
#include <set>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define ERR_EXIT(m) do { perror(m); exit(EXIT_FAILURE);} while(0)

int thread_test();
