#include "TbUserDAO.h"
#include "AutoClosePtr.h"
#include <stdio.h>
#include "Debug.h"


const char* TbUserDAO::m_pCreateSql[s_createCount] = {TB_USER_CREATE_TABLE_SQL};


TbUserDAO::TbUserDAO()
    : m_pDbHandler(NULL)
    , m_pInsert(NULL)
    , m_pQueryProductId(NULL)
{
}

TbUserDAO::~TbUserDAO()
{
    Destroy();
    m_pDbHandler = NULL;
}


int TbUserDAO::Init(DataBaseHandler *pDbHandler)
{
    if (pDbHandler == NULL)
    {
        return -1;
    }
    m_pDbHandler = pDbHandler;

    char sqlBuffer[1024];

    // table exist sql
    if (m_pDbHandler->TableExist("TB_USER") == false)
    {// table create sql
        DebugPrint("%s table is not exist,should create!\n", "TB_USER");

        if (m_pDbHandler->CreateTable(m_pCreateSql, s_createCount) == false)
        {
            DebugPrint("create table %s failed!\n", "TB_USER");
        }
		else
        {
            DebugPrint("create table %s success!\n", "TB_USER");
        }
    }

    // insert sql
    sprintf(sqlBuffer, TB_USER_INSERT_SQL);
    m_pInsert = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pInsert == NULL)
    {
        return -1;
    }

    // select sql
    sprintf(sqlBuffer, TB_USER_SELECT_PRODUCTID_SQL);
    m_pQueryProductId = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pQueryProductId == NULL)
    {
        return -1;
    }

    return 0;
}


void TbUserDAO::Destroy()
{
    DELETE_STMT_OBJ(m_pInsert);
    DELETE_STMT_OBJ(m_pQueryProductId);

    m_pDbHandler = NULL;
}


int TbUserDAO::Insert(const SPYDATA_USER &data)
{
    char targettype[8] = "";
    char acctype[8] = "";
    char sex[2] = "";
    snprintf(targettype, 8, "%u", data.Common.TargetType);
    snprintf(acctype, 8, "%u", data.AccountType);
    snprintf(sex, 2, "%u", data.Sex);
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
        m_pInsert->SetString(13, data.Uid);
        m_pInsert->SetString(14, data.Nickname);
        m_pInsert->SetString(15, data.Phone);
        m_pInsert->SetString(16, data.RealName);
        m_pInsert->SetString(17, data.Address);
        m_pInsert->SetString(18, data.Email);
        m_pInsert->SetString(19, data.Company);
        m_pInsert->SetString(20, data.Position);
        m_pInsert->SetString(21, data.BirthPlace);
        m_pInsert->SetString(22, data.School);
        m_pInsert->SetString(23, data.Description);
        m_pInsert->SetString(24, sex);
		
		if (0 != data.Age)
			m_pInsert->SetInt(25, data.Age);
		else 
			m_pInsert->SetIntNull(25);
		
		if (0 != data.Birthday)
			m_pInsert->SetTime(26, data.Birthday);
		else 
			m_pInsert->SetTimeNull(26);		
		
		if (0 != data.RegTime)
			m_pInsert->SetInt(27, data.RegTime);
		else 
			m_pInsert->SetIntNull(27);
		
		if (0 != data.LastLoginTime)
			m_pInsert->SetInt(28, data.LastLoginTime);
		else 
			m_pInsert->SetIntNull(28);
		

        m_pInsert->ExecuteUpdate();
    }
    catch(...)
    {
        return -1;
    }
    return 0;
}


int TbUserDAO::QueryByProductId(const char *account, std::vector<SPYDATA_USER> &vecData)
{
    int count = 0;
	int CaptureTime, RegTime, LastLoginTime, Age;
	std::string targettype, acctype, sex;
    try
    {
        m_pQueryProductId->SetString(1, account);

        AutoClosePtr<DataBaseResultSet> pRs(NULL);
        pRs.reset(m_pQueryProductId->ExecuteQuery());

        while (pRs->Next())
        {
            SPYDATA_USER data;
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
            pRs->GetString(14, data.Uid);
            pRs->GetString(15, data.Nickname);
            pRs->GetString(16, data.Phone);
            pRs->GetString(17, data.RealName);
            pRs->GetString(18, data.Address);
            pRs->GetString(19, data.Email);
            pRs->GetString(20, data.Company);
            pRs->GetString(21, data.Position);
            pRs->GetString(22, data.BirthPlace);
            pRs->GetString(23, data.School);
            pRs->GetString(24, data.Description);
            pRs->GetString(25, sex);
            pRs->GetInt(26, Age);
            pRs->GetTime(27, data.Birthday);
            pRs->GetInt(28, RegTime);
            pRs->GetInt(29, LastLoginTime);


			data.Common.CaptureTime = CaptureTime;
			data.Common.TargetType = (ACCOUNT_TYPE)atoi(targettype.data());
			data.RegTime = RegTime;
			data.LastLoginTime = LastLoginTime;
			data.Age = (short)Age;
			data.AccountType = (ACCOUNT_TYPE)atoi(acctype.data());
			data.Sex = (SEX_TYPE)atoi(sex.data());
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



