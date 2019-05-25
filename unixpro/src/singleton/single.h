#pragma once
#include <iostream>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <sstream>
#include "Singleton.hpp"

using namespace std;

class Single
{
    friend class TSingletonClass<Single>;
    public:
    private:
        Single() { }
        ~Single(){ };
};
typedef TSingletonClass<Single> STSingleton;
#define sST STSingleton::GetInstance()
