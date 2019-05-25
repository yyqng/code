#ifndef __DATA_BASE_RESULT_SET_H__
#define __DATA_BASE_RESULT_SET_H__

#include <string>
#include <time.h>

class DataBaseResultSet
{
public:
    DataBaseResultSet()
    {
    }
    
    virtual ~DataBaseResultSet()
    {
    }
    
    virtual void Close() = 0;

public:
    virtual int GetInt(unsigned int paramIndex, int &x) = 0;
    
    virtual long GetLong(unsigned int paramIndex, long &x) = 0;
    
    virtual float GetFloat(unsigned int paramIndex, float &x) = 0;
    
    virtual char* GetString(unsigned int paramIndex, char *x) = 0;
    
    virtual std::string& GetString(unsigned int paramIndex, std::string &x) = 0;
    
    virtual time_t GetTime(unsigned int paramIndex, time_t &x) = 0;
    
    virtual int Next() = 0;
};

#endif  // __DATA_BASE_RESULT_SET_H__
