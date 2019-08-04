#pragma once
#include <iostream>
#define LINUXOCCI //避免函数重定义错误
#include <occi.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <sstream>
#include "occi.h"
using namespace std;
using namespace oracle::occi;


const string username = "zdzc";//用户名
const string password = "zdzc";//密码
const string connstring = "127.0.0.1:1521/orcl";//数据库连接字符串
class orcl
{
    public:
        orcl();
        ~orcl();
        int oracle_select();
    private:
        Environment *env;
        Connection *conn;
        Statement *stmt;
};


