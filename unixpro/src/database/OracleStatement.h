#ifndef __ORACLE_STATEMENT_H__
#define __ORACLE_STATEMENT_H__

#include "DataBaseStatement.h"
#include <occi.h>
#include <string>
#include <time.h>
#include "OracleResultSet.h"

#ifndef DELETE_OBJ
#define DELETE_OBJ(obj) do{if (obj != NULL) {delete obj; obj = NULL;}}while(0);
#endif

using namespace oracle::occi;
class OracleStatement : public DataBaseStatement
{
public:
    OracleStatement(Environment *pEnv, Connection *pConn, Statement *pStmt);

    virtual ~OracleStatement();

    void Destroy();


public:
    void SetInt(unsigned int paramIndex, int x);

    void SetIntNull(unsigned int paramIndex);

    void SetLong(unsigned int paramIndex, long x);

    void SetLongNull(unsigned int paramIndex);

    void SetFloat(unsigned int paramIndex, float x);

    void SetFloatNull(unsigned int paramIndex);

    void SetDouble(unsigned int paramIndex, double x);

    void SetDoubleNull(unsigned int paramIndex);

    void SetString(unsigned int paramIndex, const std::string &x);

    void SetString(unsigned int paramIndex, const char *x);

	void SetStringNull(unsigned int paramIndex);

    void SetTime(unsigned int paramIndex, time_t x);

    void SetTimeNull(unsigned int paramIndex);

    void Close();

    OracleResultSet* ExecuteQuery();

    int ExecuteUpdate();

private:
    void TimeToStamp(time_t src, Date &dst);

private:
    Environment         *m_pEnv;        // Environment obj
    Connection          *m_pConn;       // Connection obj
    Statement           *m_pStmt;       // Statement obj
};

#endif  // __ORACLE_STATEMENT_H__

