#ifndef __TB_USER_DAO_H__
#define __TB_USER_DAO_H__

#include "DataBaseHandler.h"
#include "DataBaseStatement.h"
#include "DbTableData.h"
#include "comm.h"

#include <vector>

class TbUserDAO
{
public:
    TbUserDAO();
    ~TbUserDAO();

    int Init(DataBaseHandler *pDbHandler);

    void Destroy();

    //int SaveDbToFile();
public:
    int Insert(const SPYDATA_USER &data);

    int QueryByProductId(const char *account, std::vector<SPYDATA_USER> &vecData);

private:
    DataBaseHandler         *m_pDbHandler;
    DataBaseStatement       *m_pInsert;
    DataBaseStatement       *m_pQueryProductId;

    static const int        s_createCount = 1;
    static const char       *m_pCreateSql[s_createCount];
};

#endif
