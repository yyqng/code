#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int epoll_client(int argc, char *argv[]);
int epoll_server(int argc, char *argv[]);
// clients_list save all the clients's socket
extern list<int> clients_list;

/**********************   macro defintion **************************/
// server ip
#define SERVER_IP "127.0.0.1"

// server port
#define SERVER_PORT 8888

//epoll size
#define EPOLL_SIZE 5000

//message buffer size
#define BUF_SIZE 0xFFFF

#define SERVER_WELCOME "Welcome you join  to the chat room! Your chat ID is: Client #%d"

#define SERVER_MESSAGE "ClientID %d say >> %s"

// exit
#define EXIT "EXIT"

#define CAUTION "There is only one int the char room!"

/**********************   some function **************************/
/**
  * @param sockfd: socket descriptor
  * @return 0
**/
int setnonblocking(int sockfd);

/**
  * @param epollfd: epoll handle
  * @param fd: socket descriptor
  * @param enable_et : enable_et = true, epoll use ET; otherwise LT
**/
void addfd( int epollfd, int fd, bool enable_et );

/**
  * @param clientfd: socket descriptor
  * @return : len
**/
int sendBroadcastmessage(int clientfd);
#endif // UTILITY_H_INCLUDED
