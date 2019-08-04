#include "oracle.h"

orcl::orcl()
{
    env  = Environment::createEnvironment();                      //创建环境变量;
    conn = env->createConnection(username,password,connstring);   //创建数据库连接对象;
    stmt = conn->createStatement();                               //创Statement对象;
}

orcl::~orcl()
{
    conn->terminateStatement(stmt);                               //终止Statement对象
    env->terminateConnection(conn);                               //断开数据库连接
    Environment::terminateEnvironment(env);                       //终止环境变量
}

int orcl::oracle_select()
{

    string sql = "SELECT CAPTURE_TIME,PRODUCT_ID,ACCOUNT,FRIEND_NICK,FRIEND_ACC,FRIEND_UID FROM TB_FRIEND \
                        where product_id='1010019' and ACCOUNT='m2015yaya@163.com' ";
    stmt->setSQL(sql);                                            //准备SQL语句
    try
    {
        ResultSet* rs =  stmt->executeQuery();                    //执行SQL语句，返回结果集
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

