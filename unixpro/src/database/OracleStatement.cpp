#include "OracleStatement.h"
#include "Debug.h"
#include <stdio.h>
#include <string.h>


OracleStatement::OracleStatement(Environment *pEnv, Connection *pConn, Statement *pStmt)
    : m_pEnv(pEnv)
    , m_pConn(pConn)
    , m_pStmt(pStmt)
{
    m_pStmt->setAutoCommit(true);
}

OracleStatement::~OracleStatement()
{

}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::Destroy()
{
    if (m_pConn != NULL && m_pStmt != NULL)
    {
        m_pConn->terminateStatement(m_pStmt);
        m_pStmt = NULL;
    }
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::SetInt(unsigned int paramIndex, int x)
{
    try
    {
        m_pStmt->setInt(paramIndex, x);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetInt) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetInt) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}
	
void OracleStatement::SetIntNull(unsigned int paramIndex)
{
	try
	{
		m_pStmt->setNull(paramIndex, OCCIINT);
	}
	catch(SQLException &sqlExcp)
	{
		//LogGroup(LOG_ERR, "SQLException(SetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
		DebugPrint("SQLException(SetNull) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
		throw sqlExcp;
	}
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::SetLong(unsigned int paramIndex, long x)
{
    try
    {
        Number val(x);
        m_pStmt->setNumber(paramIndex, val);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetLong) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetLong) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}
	
void OracleStatement::SetLongNull(unsigned int paramIndex)
{
	try
	{
		m_pStmt->setNull(paramIndex, OCCI_SQLT_LNG);
	}
	catch(SQLException &sqlExcp)
	{
		//LogGroup(LOG_ERR, "SQLException(SetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
		DebugPrint("SQLException(SetNull) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
		throw sqlExcp;
	}
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::SetFloat(unsigned int paramIndex, float x)
{
    try
    {
        m_pStmt->setFloat(paramIndex, x);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetFloat) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetFloat) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

void OracleStatement::SetFloatNull(unsigned int paramIndex)
{
    try
    {
        m_pStmt->setNull(paramIndex, OCCIFLOAT);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetNull) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::SetDouble(unsigned int paramIndex, double x)
{
    try
    {
        m_pStmt->setDouble(paramIndex, x);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetDouble) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetDouble) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

void OracleStatement::SetDoubleNull(unsigned int paramIndex)
{
    try
    {
        m_pStmt->setNull(paramIndex, OCCIBDOUBLE);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetNull) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::SetString(unsigned int paramIndex, const std::string &x)
{
    try
    {
        m_pStmt->setString(paramIndex, x);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetString) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetString) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::SetString(unsigned int paramIndex, const char *x)
{
    try
    {
        std::string str(x, strlen(x));
        m_pStmt->setString(paramIndex, str);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetString) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetString) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

void OracleStatement::SetStringNull(unsigned int paramIndex)
{
    try
    {
        m_pStmt->setNull(paramIndex, OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetNull) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::SetTime(unsigned int paramIndex, time_t x)
{
    try
    {
        Date ts;
        TimeToStamp(x, ts);
        m_pStmt->setDate(paramIndex, ts);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetTime) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

void OracleStatement::SetTimeNull(unsigned int paramIndex)
{
    try
    {
        m_pStmt->setNull(paramIndex, OCCIDATE);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(SetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(SetNull) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleStatement::Close()
{
    // 关闭一个结果集

    Destroy();
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
OracleResultSet* OracleStatement::ExecuteQuery()
{
    ResultSet *rs;
    OracleResultSet *pRs = NULL;
    try
    {
        rs = m_pStmt->executeQuery();

        pRs = new OracleResultSet(m_pStmt, rs);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(ExecuteQuery) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(ExecuteQuery) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return pRs;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
int OracleStatement::ExecuteUpdate()
{
    int ret = -1;
    try
    {
        ret = m_pStmt->executeUpdate();
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(ExecuteUpdate) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(ExecuteUpdate) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return ret;
}

////////////// THIS IS A PRIVATE FUNCTION ///////////////////
void OracleStatement::TimeToStamp(time_t src, Date &dst)
{
    struct tm *tmp = localtime(&src);
    dst = Date(m_pEnv, tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

    //std::string printDate = dst.toText("YYYYMMDDHH24MISS");
}



