#include "oracle.h"


SINGLETON_CLASS_INIT(DB)
DB::DB( ): m_user(USER), m_pssw(PSSW), m_conns(CONNS)
{
    m_env  = Environment::createEnvironment();                      //创建环境变量;
    m_conn = m_env->createConnection(m_user, m_pssw, m_conns);      //创建数据库连接对象;
    m_stmt = m_conn->createStatement();                             //创Statement对象;
    cout << "construct sucess" << endl;
}
DB::~DB()
{
    cout << "destruct  sucess" << endl;
}

void DB::stop()
{
    m_conn->terminateStatement(m_stmt);                              //终止Statement对象
    m_env->terminateConnection(m_conn);                              //断开数据库连接
    Environment::terminateEnvironment(m_env);                        //终止环境变量
    cout << "stop  sucess" << endl;
}

int DB::oracle_select()
{
    string sql = "SELECT CAPTURE_TIME,PRODUCT_ID,ACCOUNT,FRIEND_NICK,FRIEND_ACC,FRIEND_UID FROM TB_FRIEND \
                        where product_id='1010019' and ACCOUNT='m2015yaya@163.com' ";
    m_stmt->setSQL(sql);                                            //准备SQL语句
    try
    {
        ResultSet* rs =  m_stmt->executeQuery();                    //执行SQL语句，返回结果集
        while (rs->next())                                        //取数据
        {
            cout << "CAPTURE_TIME:"        << rs->getInt(1) 
                 << "||" << "PRODUCT_ID:"  <<  rs->getString(2) 
                 << "||" << "ACCOUNT:"     <<  rs->getString(3) 
                 << "||" << "FRIEND_NICK:" <<  rs->getString(4) 
                 << "||" << "FRIEND_ACC:"  <<  rs->getString(5) 
                 << "||" << "FRIEND_UID:"  <<  rs->getString(6) 
                 << endl;
        }
        cout <<"SELECT  SUCCESS" << endl;
    }
    catch(SQLException ex) //异常处理
    {
            cout << " Error Number "<< ex.getErrorCode() << endl;
            cout << ex.getMessage() << endl;
    }
    return 1;
}

/*
int DB::oracle_insert()
{
    string sql = "INSERT INTO TB_FRIEND (MD5_UUID, CAPTURE_TIME, PRODUCT_ID, OPT_TYPE, ACCOUNT, FRIEND_NICK ,FRIEND_ACC,FRIEND_UID ) \
                        VALUES ('MD5_UUIDm2015yaya', 1532420899,'1010019', '12', 'm2015yaya@163.com','m2015yaya@qq.com',\
                                'm2015yaya@qq.com', 'test')";
    m_stmt->setSQL(sql);                                            //准备SQL语句
    try
    {
        m_stmt->executeQuery();                                     //执行SQL语句，返回结果集
        cout <<"INSERT  SUCCESS" << endl;
    }
    catch(SQLException ex) //异常处理
    {
            cout << " Error Number "<< ex.getErrorCode() << endl;
            cout << ex.getMessage() << endl;
    }
    return 1;
}*/
int DB::oracle_insert()
{
    //int SEQ_UUID = 1532420899;
    std::string Md5Uuid = "MD5_UUIDm2015yaya";
    int CaptureTime = 1532420899;
    //std::string TargetId = "";
    //std::string targettype = "";
    std::string ProductId = "1010019";
    std::string OptType = "12";
    //std::string Content = "";
    //std::string MainFile = "";
    //std::string OtherFiles = "";
    //std::string Remarks = "";
    std::string Account = "m2015yaya@163.com";
    //std::string acctype = "";
    //std::string friendtype = "";
    std::string FriendAcc = "m2015yaya@qq.com";
    std::string FriendUid = "m2015yaya@qq.com";
    std::string FriendNick = "testnick";
    //std::string FriendGroup = "";
    //std::string FriendTag = "";
    /*
    try
    {
        m_stmt->setInt( 0,  SEQ_UUID);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 0 SEQ_UUID "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }*/

    try
    {
        m_stmt->setString(1, Md5Uuid);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 1 Md5Uuid"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setInt( 2,  CaptureTime);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 2 CaptureTime "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(3,  OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 3 OCCI_SQLT_STR "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(4,  OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 4 OCCI_SQLT_STR "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setString(5, ProductId);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 5 ProductId "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setString(6, OptType);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 6 OptType "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(7,  OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 7 OCCI_SQLT_STR "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(8,  OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 8 OCCI_SQLT_STR"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(9,  OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 9 OCCI_SQLT_STR"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(10, OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 10 OCCI_SQLT_STR"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setString(11, Account);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 11 Account"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    /*
    try
    {
        m_stmt->setString(12, acctype);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 12 acctype"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setString(13, friendtype);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 13 friendtype"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }*/

    try
    {
        m_stmt->setString(14, FriendAcc);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 14 FriendAcc"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setString(15, FriendUid);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 15 FriendUid"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setString(16, FriendNick);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 16 FriendNick"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(17, OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 17 OCCI_SQLT_STR"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        m_stmt->setNull(18, OCCI_SQLT_STR);
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error 18 OCCI_SQLT_STR"<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    try
    {
        //m_stmt->executeUpdate();
        m_stmt->execute();
    }
    catch(SQLException &sqlExcp)
    {
        cout << " Error executeUpdate "<< sqlExcp.getErrorCode()  << sqlExcp.getMessage() << endl;
    }

    cout <<"INSERT  SUCCESS" << endl;
    return 1;
}


int DB::oracle_delete()
{
    string sql = "DELETE FROM TB_FRIEND WHERE MD5_UUID='MD5_UUIDm2015yaya' and FRIEND_UID='test'";
    m_stmt->setSQL(sql);                                            //准备SQL语句
    try
    {
        m_stmt->executeQuery();                                     //执行SQL语句，返回结果集
        cout <<"DELETE  SUCCESS" << endl;
    }
    catch(SQLException ex) //异常处理
    {
            cout << " Error Number "<< ex.getErrorCode() << endl;
            cout << ex.getMessage() << endl;
    }
    return 1;
}

