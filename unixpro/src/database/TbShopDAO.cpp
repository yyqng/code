#include "TbShopDAO.h"
#include "AutoClosePtr.h"
#include <stdio.h>
#include "Debug.h"


const char* TbShopDAO::m_pCreateSql[s_createCount] = {TB_SHOP_CREATE_TABLE_SQL};


TbShopDAO::TbShopDAO()
    : m_pDbHandler(NULL)
    , m_pInsert(NULL)
    , m_pQueryProductId(NULL)
{
}

TbShopDAO::~TbShopDAO()
{
    Destroy();
    m_pDbHandler = NULL;
}


int TbShopDAO::Init(DataBaseHandler *pDbHandler)
{
    if (pDbHandler == NULL)
    {
        return -1;
    }
    m_pDbHandler = pDbHandler;

    char sqlBuffer[1024];

    // table exist sql
    if (m_pDbHandler->TableExist("TB_SHOP") == false)
    {// table create sql
        DebugPrint("%s table is not exist,should create!\n", "TB_SHOP");

        if (m_pDbHandler->CreateTable(m_pCreateSql, s_createCount) == false)
        {
            DebugPrint("create table %s failed!\n", "TB_SHOP");
        }
		else
        {
            DebugPrint("create table %s success!\n", "TB_SHOP");
        }
    }

    // insert sql
    sprintf(sqlBuffer, TB_SHOP_INSERT_SQL);
    m_pInsert = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pInsert == NULL)
    {
        return -1;
    }

    // select sql
    sprintf(sqlBuffer, TB_SHOP_SELECT_PRODUCTID_SQL);
    m_pQueryProductId = m_pDbHandler->PrepareSql(sqlBuffer);
    if (m_pQueryProductId == NULL)
    {
        return -1;
    }

    return 0;
}


void TbShopDAO::Destroy()
{
    DELETE_STMT_OBJ(m_pInsert);
    DELETE_STMT_OBJ(m_pQueryProductId);

    m_pDbHandler = NULL;
}


int TbShopDAO::Insert(const SPYDATA_SHOP &data)
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
        m_pInsert->SetString(13, data.OrderId);
        m_pInsert->SetString(14, data.From);
        m_pInsert->SetString(15, data.FromNick);
        m_pInsert->SetString(16, data.To);
        m_pInsert->SetString(17, data.ToNick);
        m_pInsert->SetString(18, data.ToAddress);
        m_pInsert->SetString(19, data.ToPhone);
        m_pInsert->SetString(20, data.Name);
		
		if (0 != data.Count)
		    m_pInsert->SetFloat(21, data.Count);
		else
			m_pInsert->SetFloatNull(21);

		if (0 != data.Price)
	        m_pInsert->SetFloat(22, data.Price);
		else
			m_pInsert->SetFloatNull(22);
		
		if (0 != data.OrderTime)
	        m_pInsert->SetInt(23, data.OrderTime);
		else
			m_pInsert->SetIntNull(23);
		
        m_pInsert->SetString(24, data.OrderType);
        m_pInsert->SetString(25, data.OrderTag);

        m_pInsert->ExecuteUpdate();
    }
    catch(...)
    {
        return -1;
    }
    return 0;
}


int TbShopDAO::QueryByProductId(const char *account, std::vector<SPYDATA_SHOP> &vecData)
{
    int count = 0;
	int CaptureTime, OrderTime;
	std::string targettype, acctype;
    try
    {
        m_pQueryProductId->SetString(1, account);

        AutoClosePtr<DataBaseResultSet> pRs(NULL);
        pRs.reset(m_pQueryProductId->ExecuteQuery());

        while (pRs->Next())
        {
            SPYDATA_SHOP data;
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
	        pRs->GetString(14, data.OrderId);
	        pRs->GetString(15, data.From);
	        pRs->GetString(16, data.FromNick);
	        pRs->GetString(17, data.To);
	        pRs->GetString(18, data.ToNick);
	        pRs->GetString(19, data.ToAddress);
	        pRs->GetString(20, data.ToPhone);
	        pRs->GetString(21, data.Name);
	        pRs->GetFloat(22, data.Count);
	        pRs->GetFloat(23, data.Price);
	        pRs->GetInt(24, OrderTime);
	        pRs->GetString(25, data.OrderType);
	        pRs->GetString(26, data.OrderTag);

			data.Common.CaptureTime = CaptureTime;
			data.Common.TargetType = (ACCOUNT_TYPE)atoi(targettype.data());
			data.AccountType = (ACCOUNT_TYPE)atoi(acctype.data());
			data.OrderTime = OrderTime;
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



