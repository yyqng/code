#include "TbReadDAO.h"
#include "AutoClosePtr.h"
#include <stdio.h>
#include "Debug.h"


const char* TbReadDAO::m_pCreateSql[s_createCount] = {TB_READ_CREATE_TABLE_SQL};


TbReadDAO::TbReadDAO()
    : m_pDbHandler(NULL)
    , m_pInsert(NULL)
    , m_pQueryProductId(NULL)
{
}

TbReadDAO::~TbReadDAO()
{
    Destroy();
    m_pDbHandler = NULL;
}


int TbReadDAO::Init(DataBaseHandler *pDbHandler)
{
    if (pDbHandler == NULL)
    {
        return -1;
    }
    m_pDbHandler = pDbHandler;

    char sqlBuffer[1024];

    // table exist sql
    if (m_pDbHandler->TableExist("TB_READ") == false)
    {// table create sql
        DebugPrint("%s table is not exist,should create!\n", "TB_READ");

        if (m_pDbHandler->CreateTable(m_pCreateSql, s_createCount) == false)
        {
            DebugPrint("create table %s failed!\n", "TB_READ");
        }
		else
        {
            DebugPrint("create table %s success!\n", "TB_READ");
        }
    }

    // insert sql
    sprintf(sqlBuffer, TB_READ_INSERT_SQL);
    m_pInsert = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pInsert == NULL)
    {
        return -1;
    }

    // select sql
    sprintf(sqlBuffer, TB_READ_SELECT_PRODUCTID_SQL);
    m_pQueryProductId = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pQueryProductId == NULL)
    {
        return -1;
    }

    return 0;
}


void TbReadDAO::Destroy()
{
    DELETE_STMT_OBJ(m_pInsert);
    DELETE_STMT_OBJ(m_pQueryProductId);

    m_pDbHandler = NULL;
}


int TbReadDAO::Insert(const SPYDATA_READ &data)
{
	char targettype[8] = "";
    char acctype[8] = "";
	snprintf(targettype, 8, "%u", data.Common.TargetType);
    snprintf(acctype, 8, "%u", data.AccountType);
    try
    {
        m_pInsert->SetString(1, data.Common.Md5Uuid);
        m_pInsert->SetInt(2, data.Common.CaptureTime);
        m_pInsert->SetString(3, data.Common.TargetId);
        m_pInsert->SetString(4, targettype);
        m_pInsert->SetString(5, data.ProductId);
        m_pInsert->SetString(6, data.OptType);
        m_pInsert->SetString(7, data.Content);
        m_pInsert->SetString(8, data.MainFile);
        m_pInsert->SetString(9, data.OtherFiles);
        m_pInsert->SetString(10, data.Remarks);
        m_pInsert->SetString(11, data.Account);
        m_pInsert->SetString(12, acctype);

		if (0 != data.CreateTime)
	        m_pInsert->SetInt(13, data.CreateTime);
		else
			m_pInsert->SetIntNull(13);

        m_pInsert->SetString(14, data.Tag);
        m_pInsert->SetString(15, data.Title);
        m_pInsert->SetString(16, data.Url);

        m_pInsert->ExecuteUpdate();
    }
    catch(...)
    {
        return -1;
    }
    return 0;
}


int TbReadDAO::QueryByProductId(const char *account, std::vector<SPYDATA_READ> &vecData)
{
    int count = 0;
	int CaptureTime, CreateTime;
	std::string targettype, acctype;
    try
    {
        m_pQueryProductId->SetString(1, account);

        AutoClosePtr<DataBaseResultSet> pRs(NULL);
        pRs.reset(m_pQueryProductId->ExecuteQuery());

        while (pRs->Next())
        {
            SPYDATA_READ data;
			pRs->GetString(2, data.Common.Md5Uuid);
			pRs->GetInt(3, CaptureTime);
			pRs->GetString(4, data.Common.TargetId);
			pRs->GetString(5, targettype);
			pRs->GetString(6, data.ProductId);
			pRs->GetString(7, data.OptType);
			pRs->GetString(8, data.Content);
			pRs->GetString(9, data.MainFile);
			pRs->GetString(10, data.OtherFiles);
			pRs->GetString(11, data.Remarks);
			pRs->GetString(12, data.Account);
			pRs->GetString(13, acctype);
			pRs->GetInt(14, CreateTime);
			pRs->GetString(15, data.Tag);
			pRs->GetString(16, data.Title);
			pRs->GetString(17, data.Content);

			data.Common.CaptureTime = CaptureTime;
			data.Common.TargetType = (ACCOUNT_TYPE)atoi(targettype.data());
			data.AccountType = (ACCOUNT_TYPE)atoi(acctype.data());
			data.CreateTime = CreateTime;
            vecData.push_back(data);
            count++;
        }
    }
    catch(...)
    {
        return -1;
    }
    return count;
}



