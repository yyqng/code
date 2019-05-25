#ifndef __ORACLE_RESTULT_SET_H__
#define __ORACLE_RESTULT_SET_H__

#include "DataBaseResultSet.h"
#include <occi.h>

#include <string>

using namespace oracle::occi;
class OracleResultSet : public DataBaseResultSet
{
public:
    OracleResultSet(Statement *pStmt, ResultSet *pRs);
    virtual ~OracleResultSet();

    void Close();

public:
    int GetInt(unsigned int paramIndex, int &x);

    long GetLong(unsigned int paramIndex, long &x);

    float GetFloat(unsigned int paramIndex, float &x);

    double GetDouble(unsigned int paramIndex, double &x);

    char* GetString(unsigned int paramIndex, char *x);

    std::string& GetString(unsigned int paramIndex, std::string &x);

    time_t GetTime(unsigned int paramIndex, time_t &x);

    int Next();

private:
    void StampToTime(Date &src, time_t &dst);

private:
    Statement           *m_pStmt;
    ResultSet           *m_pRs;
};

#endif  // __ORACLE_RESTULT_SET_H__
