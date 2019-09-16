#ifndef __TB_TRIP_DAO_H__
#define __TB_TRIP_DAO_H__

#include "DataBaseHandler.h"
#include "DataBaseStatement.h"
#include "DbTableData.h"
#include "comm.h"

#include <vector>

class TbTripDAO
{
public:
    TbTripDAO();
    ~TbTripDAO();

    int Init(DataBaseHandler *pDbHandler);

    void Destroy();

    //int SaveDbToFile();
public:
    int Insert(const SPYDATA_TRIP &data);

    int QueryByProductId(const char *account, std::vector<SPYDATA_TRIP> &vecData);

private:
    DataBaseHandler         *m_pDbHandler;
    DataBaseStatement       *m_pInsert;
    DataBaseStatement       *m_pQueryProductId;

    static const int        s_createCount = 1;
    static const char       *m_pCreateSql[s_createCount];
};

#endif
