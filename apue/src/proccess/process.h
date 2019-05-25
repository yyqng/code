#pragma once
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

void printXXID();
void fork_execlp();
void forktest();
void vforktest();
void exittest();
void competetest();
void nocompetetest();

