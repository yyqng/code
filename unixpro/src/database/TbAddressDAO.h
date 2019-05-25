#ifndef __TB_ADDRESS_DAO_H__
#define __TB_ADDRESS_DAO_H__

#include "DataBaseHandler.h"
#include "DataBaseStatement.h"
#include "DbTableData.h"
#include "comm.h"

#include <vector>

class TbAddressDAO
{
public:
    TbAddressDAO();
    ~TbAddressDAO();

    int Init(DataBaseHandler *pDbHandler);

    void Destroy();

    //int SaveDbToFile();
public:
    int Insert(const SPYDATA_ADDRESS &data);

    int QueryByProductId(const char *account, std::vector<SPYDATA_ADDRESS> &vecData);

private:
    DataBaseHandler         *m_pDbHandler;
    DataBaseStatement       *m_pInsert;
    DataBaseStatement       *m_pQueryProductId;

    static const int        s_createCount = 1;
    static const char       *m_pCreateSql[s_createCount];
};

#endif
