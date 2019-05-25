#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define IPCKEY 0x366378
#define N 64

typedef struct st_setting
{
    char agen[10];
    unsigned char file_no;
}st_setting;


typedef struct
{
    pid_t pid;
    char buf[N];
} SHM;


int creatshm();
int writer();
int reader();
void handler(int signo);

