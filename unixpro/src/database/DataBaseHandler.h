#ifndef __DATA_BASE_HANDLER_H__
#define __DATA_BASE_HANDLER_H__

#include "DataBaseStatement.h"

typedef struct _DbConn
{
    char dbName[32];
    
    char dbUser[32];
    char dbPwd[32];
    char dbUrl[128];
    int timeout;
}DB_CONN;

class DataBaseHandler
{
public:
    DataBaseHandler()
    {
    }
    
    virtual ~DataBaseHandler()
    {
    }

public:
    virtual DataBaseHandler* Connect(DB_CONN *pConnStr) = 0;
    
    virtual void Close() = 0;
    
    virtual DataBaseStatement* PrepareSql(const char *strSql) = 0;
    
    virtual void* GetConnection() = 0;
    
    virtual void Begin() = 0;
    
    virtual void Commit() = 0;
    
    virtual void RollBack() = 0;
    
    virtual int SaveDbToFile()
    {
        return 0;
    }

    virtual int LoadFileToDb()
    {
        return 0;
    }
    
    virtual int ReLoadFileToMemory()
    {
        return 0;
    }

    // exist:true; not exist:false
    virtual bool SequenceExist(const char *seqName) = 0;
    
    // create succ:true; create failed:false
    virtual bool CreateSequence(const char *seqName) = 0;
    // exist:true; not exist:false
    virtual bool TableExist(const char *tableName) = 0;
    
    // create succ:true; create failed:false
    virtual bool CreateTable(const char **createSql, int count) = 0;

};

#endif  // __DATA_BASE_HANDLER_H__
