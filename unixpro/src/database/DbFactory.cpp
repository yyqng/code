#include "DbFactory.h"
#include "DataBaseHandler.h"
#include <string.h>
#include "Debug.h"

DbFactory::DbFactory()
    : m_pDbHandler(NULL)
{
    memset(&m_connStr, 0, sizeof(m_connStr));
}

DbFactory::~DbFactory()
{
    Destroy();
    m_pDbHandler = NULL;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
int DbFactory::Init(DB_CONN *pConnStr)
{
    if (pConnStr == NULL)
    {
        return -1;
    }
    
    memcpy(&m_connStr, pConnStr, sizeof(DB_CONN));
    
    if (strcmp(m_connStr.dbName, "oracle") == 0)
    {
        m_pDbHandler = new OracleHandler();
        if (m_pDbHandler == NULL)
        {
            return -1;
        }
        
        if (m_pDbHandler->Connect(&m_connStr) == NULL)
        {
            delete m_pDbHandler;
            m_pDbHandler = NULL;
            return -1;
        }

	    // sequence exist sql
	    if (m_pDbHandler->SequenceExist("SEQ_ID") == false)
	    {// sequence create sql
	        DebugPrint("%s sequence is not exist,should create!\n", "SEQ_ID");

	        if (m_pDbHandler->CreateSequence("SEQ_ID") == false)
	        {
	            DebugPrint("create sequence %s failed!\n", "SEQ_ID");
	        }
			else
	        {
	            DebugPrint("create sequence %s success!\n", "SEQ_ID");
	        }
	    }
    }
    else
    {
        return -1;
    }
    return 0;
}

////////////// THIS IS A PUBLIC FUNCTION ///////////////////
void DbFactory::Destroy()
{
    if (m_pDbHandler != NULL)
    {
        m_pDbHandler->Close();
        
        delete m_pDbHandler;
        m_pDbHandler = NULL;
    }
}
