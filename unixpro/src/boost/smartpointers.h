#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <iostream>
#include <memory>


class A
{
public:
    A()
    {
        printf("A()\n");
    }
    ~A()
    {
        printf("~A()\n");
    }
};
void smartpTest();
void smartpboostTest();

