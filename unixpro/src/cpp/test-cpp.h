#pragma once

/*
 * test.cpp - Lambda表达式、for_each测试
 *
 *   C++ 11标准 Lambda表达式，for_each函数模板
 *
 *             Copyright  叶剑飞  2012
 *
 *
 *  编译命令：
 *        g++ test.cpp -o test -std=c++0x -Wall
 */

#include <cstdlib>
#include <algorithm>   // sort函数模板、for_each函数模板
#include <functional>  // function类模板
#ifndef _countof
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif
int for_each_Lambda( );

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define IPCKEY 0x366378
#define N 64

using namespace std;


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
void lambdatest();
void rightValueTest();

