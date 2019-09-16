#include "OracleHandler.h"
#include "AutoClosePtr.h"
#include "Debug.h"
#include <stdio.h>
#include <exception>
#include "DbTableData.h"


OracleHandler::OracleHandler()
    : m_pEnv(NULL)
    , m_pConn(NULL)
{
}

OracleHandler::~OracleHandler()
{
    Close();
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
DataBaseHandler* OracleHandler::Connect(DB_CONN *pConnStr)
{
    if (pConnStr == NULL)
    {
        return NULL;
    }

    try
    {
        // 创建OCCI上下文环境
        m_pEnv = Environment::createEnvironment("UTF8", "UTF8", Environment::Mode(Environment::OBJECT|Environment::THREADED_MUTEXED));
        if (NULL == m_pEnv)
        {
            //LogGroup(LOG_ERR, "createEnvironment error.\n");
            DebugPrint("createEnvironment error.\n");
            return NULL;
        }
        // 创建数据库连接
        m_pConn = m_pEnv->createConnection(pConnStr->dbUser, pConnStr->dbPwd, pConnStr->dbUrl);
        if(NULL == m_pConn)
        {
            //LogGroup(LOG_ERR, "createConnection error.\n");
            DebugPrint("createConnection error.\n");
            return NULL;
        }
    }
    // 捕获数据库操作异常
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(Connect) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(Connect) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        return NULL;
    }
    // 捕获其他异常
    catch(std::exception &ex)
    {
        //LogGroup(LOG_ERR, "other exception %s.\n", ex.what());
        DebugPrint("other exception %s.\n", ex.what());
        return NULL;
    }
    return this;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
OracleStatement* OracleHandler::PrepareSql(const char *strSql)
{
    OracleStatement *pOraStatement = NULL;
    try
    {
        Statement *pStmt = m_pConn->createStatement();
        pStmt->setSQL(strSql);

        pOraStatement = new OracleStatement(m_pEnv, m_pConn, pStmt);
        if (pOraStatement == NULL)
        {
            return NULL;
        }
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(PrepareSql) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(PrepareSql) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        return NULL;
    }
    catch(...)
    {
        pOraStatement->Close();
        DELETE_OBJ(pOraStatement);
        return NULL;
    }
    return pOraStatement;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleHandler::Close()
{
    if (m_pConn != NULL)
    {
        // 断开数据库连接
        m_pConn->commit();
        m_pEnv->terminateConnection(m_pConn);
        m_pConn = NULL;
    }
    if (m_pEnv != NULL)
    {
        // 释放OCCI上下文环境
        Environment::terminateEnvironment(m_pEnv);
        m_pEnv = NULL;
    }
}


bool OracleHandler::SequenceExist(const char *seqName)
{
    bool isExistTable = false;
    char sqlBuffer[1024];
    sprintf(sqlBuffer, SEQ_SEQUENCE_EXIST_SQL, seqName);
    OracleStatement *pOraStatement = PrepareSql(sqlBuffer);
    if (pOraStatement == NULL)
    {
        return isExistTable;
    }

    try
    {
        AutoClosePtr<DataBaseResultSet> pRs(NULL);
        pRs.reset(pOraStatement->ExecuteQuery());

        while(pRs->Next())
        {
            int isExist;
            pRs->GetInt(1, isExist);
            isExistTable = (isExist == 0 ? false : true);
        }
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SequenceExist) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SequenceExist) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        pOraStatement->Close();
        delete pOraStatement;
        pOraStatement = NULL;
        return isExistTable;
    }

    pOraStatement->Close();
    delete pOraStatement;
    pOraStatement = NULL;
    return isExistTable;
}


bool OracleHandler::CreateSequence(const char *seqName)
{
    char sqlBuffer[1024];
    sprintf(sqlBuffer, SEQ_SEQUENCE_CREATE_SQL, seqName);
    OracleStatement *pOraStatement = PrepareSql(sqlBuffer);
    if (pOraStatement == NULL)
    {
        return false;
    }

    try
    {
        pOraStatement->ExecuteUpdate();
    }
    catch(SQLException &sqlExcp)
    {
       	//LogGroup(LOG_ERR, "SQLException(CreateSequence) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
       	DebugPrint("SQLException(CreateSequence) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        pOraStatement->Close();
        delete pOraStatement;
        pOraStatement = NULL;
        return false;
    }

    pOraStatement->Close();
    delete pOraStatement;
    pOraStatement = NULL;


    return true;
}


bool OracleHandler::TableExist(const char *tableName)
{
    bool isExistTable = false;
    char sqlBuffer[1024];
    sprintf(sqlBuffer, TB_TABLE_EXIST_SQL, tableName);
    OracleStatement *pOraStatement = PrepareSql(sqlBuffer);
    if (pOraStatement == NULL)
    {
        return isExistTable;
    }

    try
    {
        AutoClosePtr<DataBaseResultSet> pRs(NULL);
        pRs.reset(pOraStatement->ExecuteQuery());

        while(pRs->Next())
        {
            int isExist;
            pRs->GetInt(1, isExist);
            isExistTable = (isExist == 0 ? false : true);
        }
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(TableExist) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(TableExist) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        pOraStatement->Close();
        delete pOraStatement;
        pOraStatement = NULL;
        return isExistTable;
    }

    pOraStatement->Close();
    delete pOraStatement;
    pOraStatement = NULL;
    return isExistTable;
}


bool OracleHandler::CreateTable(const char **createSql, int count)
{
    for (int i=0; i<count; i++)
    {
        OracleStatement *pOraStatement = PrepareSql(createSql[i]);
        if (pOraStatement == NULL)
        {
            return false;
        }

        try
        {
            pOraStatement->ExecuteUpdate();
        }
        catch(SQLException &sqlExcp)
        {
           	//LogGroup(LOG_ERR, "SQLException(CreateTable) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
           	DebugPrint("SQLException(CreateTable) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
            pOraStatement->Close();
            delete pOraStatement;
            pOraStatement = NULL;
            return false;
        }

        pOraStatement->Close();
        delete pOraStatement;
        pOraStatement = NULL;
    }

    return true;
}



