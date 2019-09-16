#include "TbTargetDAO.h"
#include "AutoClosePtr.h"
#include <stdio.h>
#include "Debug.h"


const char* TbTargetDAO::m_pCreateSql[s_createCount] = {TB_TARGET_CREATE_TABLE_SQL};


TbTargetDAO::TbTargetDAO()
    : m_pDbHandler(NULL)
    , m_pInsert(NULL)
    , m_pQueryTargetId(NULL)
{
}

TbTargetDAO::~TbTargetDAO()
{
    Destroy();
    m_pDbHandler = NULL;
}


int TbTargetDAO::Init(DataBaseHandler *pDbHandler)
{
    if (pDbHandler == NULL)
    {
        return -1;
    }
    m_pDbHandler = pDbHandler;

    char sqlBuffer[1024];

    // table exist sql
    if (m_pDbHandler->TableExist("TB_TARGET") == false)
    {// table create sql
        DebugPrint("%s table is not exist,should create!\n", "TB_TARGET");

        if (m_pDbHandler->CreateTable(m_pCreateSql, s_createCount) == false)
        {
            DebugPrint("create table %s failed!\n", "TB_TARGET");
        }
		else
        {
            DebugPrint("create table %s success!\n", "TB_TARGET");
        }
    }

    // insert sql
    sprintf(sqlBuffer, TB_TARGET_INSERT_SQL);
    m_pInsert = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pInsert == NULL)
    {
        return -1;
    }

    // select sql
    sprintf(sqlBuffer, TB_TARGET_SELECT_TARGETID_SQL);
    m_pQueryTargetId = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pQueryTargetId == NULL)
    {
        return -1;
    }

    return 0;
}


void TbTargetDAO::Destroy()
{
    DELETE_STMT_OBJ(m_pInsert);
    DELETE_STMT_OBJ(m_pQueryTargetId);

    m_pDbHandler = NULL;
}


int TbTargetDAO::Insert(const SPYDATA_TARGET &data)
{
    char targettype[8] = "";
    snprintf(targettype, 8, "%u", data.Common.TargetType);
    try
    {
        m_pInsert->SetString(1, data.Common.Md5Uuid);
        m_pInsert->SetInt(2, data.Common.CaptureTime);
        m_pInsert->SetString(3, data.Common.TargetId);
        m_pInsert->SetString(4, targettype);
        m_pInsert->SetString(5, data.Remarks);
        m_pInsert->SetInt(6, data.Status);
        m_pInsert->SetString(7, data.LoginId);

        m_pInsert->ExecuteUpdate();
    }
    catch(...)
    {
        return -1;
    }
    return 0;
}


int TbTargetDAO::QueryByTargetId(const char *id, std::vector<SPYDATA_TARGET> &vecData)
{
    int count = 0;
	int CaptureTime, Status;
	std::string targettype;
    try
    {
        m_pQueryTargetId->SetString(1, id);

        AutoClosePtr<DataBaseResultSet> pRs(NULL);
        pRs.reset(m_pQueryTargetId->ExecuteQuery());

        while (pRs->Next())
        {
            SPYDATA_TARGET data;
			pRs->GetString(2, data.Common.Md5Uuid);
			pRs->GetInt(3, CaptureTime);
			pRs->GetString(4, data.Common.TargetId);
			pRs->GetString(5, targettype);
			pRs->GetString(6, data.Remarks);
			pRs->GetInt(7, Status);
			pRs->GetString(8, data.LoginId);

			data.Common.TargetType = (ACCOUNT_TYPE)atoi(targettype.data());
			data.Common.CaptureTime = CaptureTime;
			data.Status = (short)Status;
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


