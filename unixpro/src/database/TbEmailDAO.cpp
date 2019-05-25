#include "TbEmailDAO.h"
#include "AutoClosePtr.h"
#include <stdio.h>
#include "Debug.h"


const char* TbEmailDAO::m_pCreateSql[s_createCount] = {TB_EMAIL_CREATE_TABLE_SQL};


TbEmailDAO::TbEmailDAO()
    : m_pDbHandler(NULL)
    , m_pInsert(NULL)
    , m_pQueryProductId(NULL)
{
}

TbEmailDAO::~TbEmailDAO()
{
    Destroy();
    m_pDbHandler = NULL;
}


int TbEmailDAO::Init(DataBaseHandler *pDbHandler)
{
    if (pDbHandler == NULL)
    {
        return -1;
    }
    m_pDbHandler = pDbHandler;

    char sqlBuffer[1024];

    // table exist sql
    if (m_pDbHandler->TableExist("TB_EMAIL") == false)
    {// table create sql
        DebugPrint("%s table is not exist,should create!\n", "TB_EMAIL");

        if (m_pDbHandler->CreateTable(m_pCreateSql, s_createCount) == false)
        {
            DebugPrint("create table %s failed!\n", "TB_EMAIL");
        }
		else
        {
            DebugPrint("create table %s success!\n", "TB_EMAIL");
        }
    }

    // insert sql
    sprintf(sqlBuffer, TB_EMAIL_INSERT_SQL);
    m_pInsert = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pInsert == NULL)
    {
        return -1;
    }

    // select sql
    sprintf(sqlBuffer, TB_EMAIL_SELECT_PRODUCTID_SQL);
    m_pQueryProductId = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pQueryProductId == NULL)
    {
        return -1;
    }

    return 0;
}


void TbEmailDAO::Destroy()
{
    DELETE_STMT_OBJ(m_pInsert);
    DELETE_STMT_OBJ(m_pQueryProductId);

    m_pDbHandler = NULL;
}


int TbEmailDAO::Insert(const SPYDATA_EMAIL &data)
{
	char targettype[8] = "";
    char acctype[8] = "";
    char isread[2] = "";
    char ismark[2] = "";
	snprintf(targettype, 8, "%u", data.Common.TargetType);
    snprintf(acctype, 8, "%u", data.AccountType);
    snprintf(isread, 2, "%u", data.IsRead);
    snprintf(ismark, 2, "%u", data.IsMark);
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
        m_pInsert->SetString(13, data.MailId);
        m_pInsert->SetString(14, data.From);
        m_pInsert->SetString(15, data.FromNick);
        m_pInsert->SetString(16, data.To);
        m_pInsert->SetString(17, data.ToNick);
        m_pInsert->SetString(18, data.Cc);
        m_pInsert->SetString(19, data.Bcc);
		
		if (0 != data.SendTime)
		    m_pInsert->SetInt(20, data.SendTime);
		else
			m_pInsert->SetIntNull(20);

	    m_pInsert->SetString(21, isread);
	    m_pInsert->SetString(22, ismark);
        m_pInsert->SetString(23, data.Folder);
        m_pInsert->SetString(24, data.Subject);

        m_pInsert->ExecuteUpdate();
    }
    catch(...)
    {
        return -1;
    }
    return 0;
}


int TbEmailDAO::QueryByProductId(const char *account, std::vector<SPYDATA_EMAIL> &vecData)
{
    int count = 0;
	int CaptureTime, SendTime;
	std::string targettype, acctype, isread, ismark;
    try
    {
        m_pQueryProductId->SetString(1, account);

        AutoClosePtr<DataBaseResultSet> pRs(NULL);
        pRs.reset(m_pQueryProductId->ExecuteQuery());

        while (pRs->Next())
        {
            SPYDATA_EMAIL data;
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
			pRs->GetString(14, data.MailId);
			pRs->GetString(15, data.From);
			pRs->GetString(16, data.FromNick);
			pRs->GetString(17, data.To);
			pRs->GetString(18, data.ToNick);
			pRs->GetString(19, data.Cc);
			pRs->GetString(20, data.Bcc);
			pRs->GetInt(21, SendTime);
			pRs->GetString(22, isread);
			pRs->GetString(23, ismark);
			pRs->GetString(24, data.Folder);
			pRs->GetString(25, data.Subject);

			data.Common.CaptureTime = CaptureTime;
			data.Common.TargetType = (ACCOUNT_TYPE)atoi(targettype.data());
			data.AccountType = (ACCOUNT_TYPE)atoi(acctype.data());
			data.SendTime = SendTime;
			data.IsRead = (READ_TYPE)atoi(isread.data());
			data.IsMark = (MARK_TYPE)atoi(ismark.data());
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



