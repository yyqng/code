#pragma once
#ifndef MY_LIBC_H
#define MY_LIBC_H
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>


void insertTest();
void ctypeTest();
void errnoTest();
void floatTest();
void limitsTest();
void localeTest();
void mathTest();

extern jmp_buf jumpBuff;
void setjmpTest();
void setjmpFuna();
void setjmpFunb();
void setjmpFunc();

void signalTest();
void stdargsTest(int argc, char *argv[]);
void stddefTest();
void stdioTest();
#endif
