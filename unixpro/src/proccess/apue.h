#pragma once
#include <errno.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>


static volatile sig_atomic_t sigflag;
static sigset_t newmask;
static sigset_t oldmask;
static sigset_t zeromask;

extern void err_sys(const char * s);
extern void sig_usr(int signo);
extern void TELL_WAIT(void);
