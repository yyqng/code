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
#include "Singleton.hpp"

using namespace std;
using namespace oracle::occi;

const string USER = "zdzc";
const string PSSW = "zdzc";
const string CONNS = "127.0.0.1:1521/orcl";

class DB
{
    friend class TSingletonClass<DB>;
    public:
        void stop();
        DB(const DB&)=delete;
        DB& operator=(const DB&)=delete;
        int oracle_select();
        int oracle_insert();
        int oracle_delete();
        ~DB();
    private:
        DB();
        Environment *m_env;
        Connection  *m_conn;
        Statement   *m_stmt;
        string m_user ;
        string m_pssw ;
        string m_conns;
};
typedef TSingletonClass<DB> DBSingleton;
#define sDB DBSingleton::GetInstance()
