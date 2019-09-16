#ifndef __ORACLE_HANDLE_H__
#define __ORACLE_HANDLE_H__

#include <occi.h>
#include <string>

#include "DataBaseHandler.h"
#include "OracleStatement.h"

#ifndef DELETE_OBJ
#define DELETE_OBJ(obj) do{if (obj != NULL) {delete obj; obj = NULL;}}while(0);
#endif

using namespace oracle::occi;
class OracleHandler : public DataBaseHandler
{
public:
    OracleHandler();
    virtual ~OracleHandler();

public:
    DataBaseHandler* Connect(DB_CONN *pConnStr);

    void Close();

    OracleStatement* PrepareSql(const char *strSql);

    void* GetConnection()
    {
        return this;
    }

    void Begin()
    {
        return;
    }

    void Commit()
    {
        m_pConn->commit();
    }

    void RollBack()
    {
        m_pConn->rollback();
    }

    bool SequenceExist(const char *seqName);

    bool CreateSequence(const char *seqName);

    bool TableExist(const char *tableName);

    bool CreateTable(const char **createSql, int count);


private:

private:
    Environment         *m_pEnv;             // OCCI 上下文环�?
    Connection          *m_pConn;            // 数据库连�?
    
};

#endif  // __ORACLE_HANDLE_H__
