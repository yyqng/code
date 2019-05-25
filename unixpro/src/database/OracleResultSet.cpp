#include "OracleResultSet.h"
#include "Debug.h"
#include <stdio.h>
#include <string.h>


OracleResultSet::OracleResultSet(Statement *pStmt, ResultSet *pRs)
    : m_pStmt(pStmt)
    , m_pRs(pRs)
{
}

OracleResultSet::~OracleResultSet()
{
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleResultSet::Close()
{
    if (m_pStmt != NULL && m_pRs != NULL)
    {
        m_pRs->cancel();
        m_pStmt->closeResultSet(m_pRs);
        m_pRs = NULL;
    }
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
int OracleResultSet::GetInt(unsigned int paramIndex, int &x)
{
    try
    {
        x = m_pRs->getInt(paramIndex);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(GetInt) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(GetInt) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return x;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
long OracleResultSet::GetLong(unsigned int paramIndex, long &x)
{
    try
    {
        x = (long)m_pRs->getNumber(paramIndex);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(GetLong) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(GetLong) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return x;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
float OracleResultSet::GetFloat(unsigned int paramIndex, float &x)
{
    try
    {
        x = m_pRs->getFloat(paramIndex);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(GetFloat) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(GetFloat) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return x;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
double OracleResultSet::GetDouble(unsigned int paramIndex, double &x)
{
    try
    {
        x = m_pRs->getDouble(paramIndex);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(GetDouble) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(GetDouble) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return x;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
char* OracleResultSet::GetString(unsigned int paramIndex, char *x)
{
    if (x == NULL)
    {
        return NULL;
    }
    std::string str;

    try
    {
        str = m_pRs->getString(paramIndex);
        strcpy(x, str.data());
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(GetString) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(GetString) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return x;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
std::string& OracleResultSet::GetString(unsigned int paramIndex, std::string &x)
{
    try
    {
        x = m_pRs->getString(paramIndex);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(GetString) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(GetString) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return x;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
time_t OracleResultSet::GetTime(unsigned int paramIndex, time_t &x)
{
    try
    {
        Date ts = m_pRs->getDate(paramIndex);
        StampToTime(ts, x);
    }
    catch(SQLException &sqlExcp)
    {
        //LogGroup(LOG_ERR, "SQLException(GetTime) %d:%s.\n",sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        DebugPrint("SQLException(GetTime) %d:%s.\n", sqlExcp.getErrorCode(), sqlExcp.getMessage().c_str());
        throw sqlExcp;
    }
    return x;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
int OracleResultSet::Next()
{
    return m_pRs->next();
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void OracleResultSet::StampToTime(Date &src, time_t &dst)
{
    std::string str = src.toText("YYYYMMDDHH24MISS");
    struct tm tm1;

    sscanf(str.data(), "%4d%2d%2d%2d%2d%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);
    tm1.tm_year -= 1900;
    tm1.tm_mon--;
    tm1.tm_isdst = -1;

    dst = mktime(&tm1);
}



