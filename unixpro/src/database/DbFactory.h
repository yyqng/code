#ifndef _DB_FACTORY_H__
#define _DB_FACTORY_H__

#include "DataBaseHandler.h"
#include "OracleHandler.h"

class DbFactory
{
public:
    DbFactory();
    ~DbFactory();

    int Init(DB_CONN *pConnStr);

    void Destroy();

public:
    DataBaseHandler *GetCurrentHandler()
    {
        return m_pDbHandler;
    }

private:
    DB_CONN             m_connStr;
    DataBaseHandler     *m_pDbHandler;
};

#endif  // _DB_FACTORY_H__
