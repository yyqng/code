#ifndef __TB_TARGET_DAO_H__
#define __TB_TARGET_DAO_H__

#include "DataBaseHandler.h"
#include "DataBaseStatement.h"
#include "DbTableData.h"
#include "comm.h"

#include <vector>

class TbTargetDAO
{
public:
    TbTargetDAO();
    ~TbTargetDAO();

    int Init(DataBaseHandler *pDbHandler);

    void Destroy();

    //int SaveDbToFile();
public:
    int Insert(const SPYDATA_TARGET &data);

    int QueryByTargetId(const char *id, std::vector<SPYDATA_TARGET> &vecData);

private:
    DataBaseHandler         *m_pDbHandler;
    DataBaseStatement       *m_pInsert;
    DataBaseStatement       *m_pQueryTargetId;

    static const int        s_createCount = 1;
    static const char       *m_pCreateSql[s_createCount];
};

#endif
