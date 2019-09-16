#ifndef __DATA_BASE_STATEMENT_H__
#define __DATA_BASE_STATEMENT_H__

#include "DataBaseResultSet.h"
#include <string>
#include <time.h>

class DataBaseStatement
{
public:
    DataBaseStatement()
    {
    }

    virtual ~DataBaseStatement()
    {
    }

    virtual void Destroy() = 0;

public:
    virtual void SetInt(unsigned int paramIndex, int x) = 0;
	
    virtual void SetIntNull(unsigned int paramIndex) = 0;

    virtual void SetLong(unsigned int paramIndex, long x) = 0;

    virtual void SetLongNull(unsigned int paramIndex) = 0;

    virtual void SetFloat(unsigned int paramIndex, float x) = 0;

    virtual void SetFloatNull(unsigned int paramIndex) = 0;

    virtual void SetString(unsigned int paramIndex, const std::string &x) = 0;

    virtual void SetString(unsigned int paramIndex, const char *x) = 0;

    virtual void SetStringNull(unsigned int paramIndex) = 0;

    virtual void SetTime(unsigned int paramIndex, time_t updateTime) = 0;

    virtual void SetTimeNull(unsigned int paramIndex) = 0;

    virtual void Close() = 0;

    virtual DataBaseResultSet* ExecuteQuery() = 0;

    virtual int ExecuteUpdate() = 0;

private:
};

#endif  // __DATA_BASE_STATEMENT_H__
