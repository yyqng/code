#include "oracle.h"

//EXEC ORACLE OPTION(ORACA=YES);


//长度比标准全部加1，用于字符串结束
#define  MAX_08A0014_N_LEN    (20)        // 截获时间，CAPTURE_TIME
#define  MAX_02B0007_C_LEN    (65)        // 国际移动用户识别码，IMSI
#define  MAX_02B0036_C_LEN    (33)        // 移动手机号码，MSISDN
#define  MAX_08A0001_C_LEN    (8)         // 数据协议，PROTOCOL
#define  MAX_08A0003_C_LEN    (3)         // 数据协议动作类型，ACTION_TYPE
#define  MAX_02D0002_C_LEN    (65)        // 帐号，ACCOUNT
#define  MAX_02D0003_C_LEN    (33)        // 帐号ID，ACCOUNT_ID
#define  MAX_02D0004_C_LEN    (256)       // 昵称，REGIS_NICKNAME
#define  MAX_02D0005_C_LEN    (33)        // 移动电话，MSISDN
#define  MAX_02D0006_C_LEN    (8)         // 网络身份自类型/联系用帐号类型，CONTACT_ACCOUNT_TYPE
#define  MAX_02D0007_C_LEN    (65)        // 联系用帐号，CONTACT_ACCOUNT
#define  MAX_02D0008_C_LEN    (8)         // 注册用帐号类型，REG_ACCOUNT_TYPE
#define  MAX_02D0026_C_LEN    (65)        // 用户名，USER_NAME
#define  MAX_02B0004_C_LEN    (33)        // 固定电话，FIXED_PHONE
#define  MAX_02B0008_C_LEN    (256)       // 通信地址，POSTAL_ADDRESS
#define  MAX_02B0009_C_LEN    (7)         // 邮政编码，POSTAL_CODE
#define  MAX_02C0129_C_LEN    (256)       // 学校名称，SCHOOL_NAME
#define  MAX_02D0019_C_LEN    (65)        // 关联帐号，RELATE_ACCOUNT
#define  MAX_02D0023_C_LEN    (65)        // 邮箱地址，EMAIL_ACCOUNT
#define  MAX_02F0001_C_LEN    (4)         // 好友关系类型，FRIEND_RELATION_TYPE
#define  MAX_02F0002_C_LEN    (65)        // 好友帐号，FRIEND_ACCOUNT
#define  MAX_02F0003_C_LEN    (65)        // 好友备注项，FRIEND_REMARK
#define  MAX_02F0004_C_LEN    (65)        // 好友用户ID，FRIEND_ID
#define  MAX_02F0005_C_LEN    (65)        // 好友昵称，FRIEND_NICKNAME
#define  MAX_02F0006_C_LEN    (65)        // 好友分组，FRIEND_GROUP
#define  MAX_05A0002_C_LEN    (129)       // 单位/机构名称，UNIT
#define  MAX_05B0006_C_LEN    (33)        // 单位任职情况，EMPPOSIT
#define  MAX_05B0017_C_LEN    (129)       // 联系人姓名，CONTACTOR
#define  MAX_05B0020_C_LEN    (129)       // 联系人联系电话，CONTACTOR_TEL
#define  MAX_02A0011_C_LEN    (2)         // 性别，SEXCODE
#define  MAX_02A0015_N_LEN    (4)         // 年龄，AGE
#define  MAX_02A0014_D_LEN    (9)         // 出生日期，BIRTHDAY
#define  MAX_02A0026_C_LEN    (513)       // 出生地，BIRTH_PLACE
#define  MAX_07B0026_N_LEN    (21)        // 注册日期，REGIS_TIME
#define  MAX_03F0004_N_LEN    (21)        // 上次登录时间，LAST_LOGIN_TIME
#define  MAX_07A0006_C_LEN    (4001)      // 链接URL，LINK_URL
#define  MAX_08A0019_C_LEN    (256)       // 主实体文件名，MAINFILE
#define  MAX_08A0020_C_LEN    (4001)      // 文件名称，FILE_NAME
#define  MAX_08A0029_C_LEN    (2)         // 删除状态，DELETE_STATUS
#define  MAX_09A0028_N_LEN    (19)        // 使用次数，TIMES
#define  MAX_09B0030_C_LEN    (4001)      // 互联协查结果详情，BUSINESS_SURVEY_RESULT
#define  MAX_02E0004_C_LEN    (129)       // A身份的特征串，A_IDEN_STRING
#define  MAX_02E0005_C_LEN    (129)       // A身份的昵称，A_IDEN_NICKNAME
#define  MAX_02E0009_C_LEN    (129)       // B身份的特征串，B_IDEN_STRING
#define  MAX_02E0010_C_LEN    (129)       // B身份的昵称，B_IDEN_NICKNAME
#define  MAX_08B0001_C_LEN    (129)       // 标题，TITLE
#define  MAX_08C0001_C_LEN    (513)       // 信体主题，MAIL_SUBJECT
#define  MAX_08C0002_C_LEN    (129)       // 信体FROM段，FROM
#define  MAX_08C0003_C_LEN    (129)       // 信体TO段，TO
#define  MAX_08C0004_C_LEN    (129)       // 信体CC段，CC
#define  MAX_08C0005_C_LEN    (129)       // 信体BCC段，BCC
#define  MAX_08C0008_N_LEN    (21)        // 邮件发送时间，MAIL_SEND_TIME
#define  MAX_08C0010_C_LEN    (257)       // 存储位置，FOLDER
#define  MAX_08D0001_C_LEN    (4001)      // 通信内容，CONTENT
#define  MAX_08I0001_C_LEN    (129)       // 订单号，ORDER_NUM
#define  MAX_08I0004_N_LEN    (21)        // 下订单时间，ORDER_TIME
#define  MAX_08I0017_C_LEN    (513)       // 提取内容描述，EXTRACT_DESC
#define  MAX_08G0001_C_LEN    (65)        // 帖子ID，TOPIC_ID
#define  MAX_03A0001_C_LEN    (129)       // 物品名称，MATERIALS_NAME
#define  MAX_03A0006_N_LEN    (11)        // 物品数量，MATERIALS_COUNT
#define  MAX_03A0007_N_LEN    (11)        // 购买价格，PURCHASE_PRICE
#define  MAX_03A0009_C_LEN    (4001)      // 特征描述，CHARACTERISTIC_DESC
#define  MAX_03B0002_C_LEN    (65)        // 物品编码，MATERIALS_CODE
#define  MAX_03K0002_C_LEN    (65)        // 创建时间，CREATE_TIME
#define  MAX_06A0001_C_LEN    (19)        // 经度，LONGITUDE
#define  MAX_06A0002_C_LEN    (19)        // 纬度，LATITUDE
#define  MAX_06A0014_C_LEN    (257)       // 出发详细地址，DEPART_ADDRESS
#define  MAX_06A0015_C_LEN    (257)       // 目的详细地址，DESTINATION_ADDRESS
#define  MAX_06A0017_C_LEN    (65)        // 交换机名称，MSC_NAME
#define  MAX_09A0025_C_LEN    (2)         // 角色类型，ROLE_TYPE
#define  MAX_10B0002_C_LEN    (2)         // 数据状态，DATA_STATUS
#define  MAX_10A0006_C_LEN    (33)        // 主键或索引名称，INDEX_NAME


//EXEC SQL BEGIN DECLARE SECTION;
//const char *serverid = "dzc/zdzc@orcl";
//EXEC SQL END DECLARE SECTION; 

#define STR_CPY(dst, src)\
{\
    if ((dst != NULL) && (src != NULL))\
    {\
        strncpy((char*)(dst), (const char*)(src), sizeof(dst)-1);\
        dst[sizeof(dst)-1] = '\0';\
    }\
}

enum ACCOUNT_TYPE
{
    ACCOUNT_REAL         = 0,    // 上网帐号(默认)
    ACCOUNT_CALL         = 1,    // 主叫号码
    ACCOUNT_MSISDN       = 2,    // 手机号码
    ACCOUNT_IMSI         = 3,    // IMSI
    ACCOUNT_MAC          = 4,    // MAC
    ACCOUNT_IP           = 5,    // IP
    ACCOUNT_OTHERS       = 9,    // 其他
    ACCOUNT_UID          = 10,   // ......以下是自定义
    ACCOUNT_NICK         = 11,
    ACCOUNT_IMEI         = 12,
    ACCOUNT_BROADTEL     = 13,
    ACCOUNT_BROADACC     = 14,
    ACCOUNT_VOXER        = 15,

    ACCOUNT_MD5_ALL         = 200,  // ......特控，现网只带MD5值出来
    ACCOUNT_MD5_MSISDN      = 201,
    ACCOUNT_MD5_IMSI        = 202,
    ACCOUNT_MD5_IMEI        = 203,
    ACCOUNT_MD5_BROADACC    = 204,
    ACCOUNT_MD5_BROADTEL    = 205,
    ACCOUNT_MD5_BROADMAC    = 206,
    ACCOUNT_MD5_BROADIP     = 207,

    ACCOUNT_TQ_MD5_ALL      = 220,  // ......ZDTQ临时单独布控
    ACCOUNT_TQ_MD5_MSISDN   = 221,
    ACCOUNT_TQ_MD5_IMSI     = 222,
    ACCOUNT_TQ_MD5_IMEI     = 223,
    ACCOUNT_TQ_MD5_BROADACC = 224,
    ACCOUNT_TQ_MD5_BROADTEL = 225,
    ACCOUNT_TQ_MD5_BROADMAC = 226,
    ACCOUNT_TQ_MD5_BROADIP  = 227,

    ACCOUNT_ALL_MD5_IMSI    = 246,  // ......以下是泛控
    ACCOUNT_ALL_MSISDN      = 247,
    ACCOUNT_ALL_IMSI        = 248,
    ACCOUNT_ALL_IMEI        = 249,
    ACCOUNT_ALL_BROADACC    = 250,
    ACCOUNT_ALL_BROADTEL    = 251,
    ACCOUNT_ALL_BROADMAC    = 252,
    ACCOUNT_ALL_BROADIP     = 253,
    ACCOUNT_ALL_TEST        = 254,
    
    ACCOUNT_EMPTY        = 255
};
enum SEX_TYPE
{
    SEX_UNKNOWN  = 0,           // 未知的性别
    SEX_MALE     = 1,           // 男性
    SEX_FEMALE   = 2,           // 女性
    SEX_UNSTATED = 9            // 未说明的性别
};

template <typename T> 
class ZeroStruct 
{ 
public: 
    ZeroStruct() 
    { 
        memset(this,0,sizeof(T)); 
    } 
};

//公共字段
struct SPYDATA_COMMON:ZeroStruct<SPYDATA_COMMON> 
{
    char              Md5Uuid[MAX_10A0006_C_LEN];            // MD5主键
    time_t            CaptureTime;                           // 截获时间
    char              TargetId[MAX_02D0007_C_LEN];           // 目标帐号
    ACCOUNT_TYPE      TargetType;                            // 目标类型    
};


//用户类
struct SPYDATA_USER:ZeroStruct<SPYDATA_USER> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容(个性签名)
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件(头像)
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    char              Uid[MAX_02D0019_C_LEN];                // UID
    char              Nickname[MAX_02D0004_C_LEN];           // 昵称
    char              Phone[MAX_02D0005_C_LEN];              // 手机号
    char              RealName[MAX_02D0026_C_LEN];           // 姓名
    char              Address[MAX_02B0008_C_LEN];            // 地址
    char              Email[MAX_02D0023_C_LEN];              // 邮箱
    char              Company[MAX_05A0002_C_LEN];            // 公司
    char              Position[MAX_05B0006_C_LEN];           // 职位
    char              BirthPlace[MAX_02A0026_C_LEN];         // 家乡
    char              School[MAX_02C0129_C_LEN];             // 学校
    char              Description[MAX_03A0009_C_LEN];        // 个人简介
    SEX_TYPE          Sex;                                   // 性别
    short             Age;                                   // 年龄
    time_t            Birthday;                              // 出生日期
    time_t            RegTime;                               // 注册时间
    time_t            LastLoginTime;                         // 上次登录时间
};

typedef struct _DbConn
{
    char dbName[32];
    
    char dbUser[32];
    char dbPwd[32];
    char dbUrl[128];
    int timeout;
}DB_CONN;

#define DB_NAME "oracle"
#define DB_USER "zdzc"
#define DB_PWD  "zdzc"

// oracle url
extern Option<std::string> g_optOracleUrl;


bool InitDb()
{
    DB_CONN conn;
    memset(&conn, 0, sizeof(DB_CONN));
    STR_CPY(conn.dbName, DB_NAME);
    STR_CPY(conn.dbUser, DB_USER);
    STR_CPY(conn.dbPwd, DB_PWD);
    STR_CPY(conn.dbUrl, g_optOracleUrl.Get().data());

    if (m_dbFactory.Init(&conn) != 0)
    {
        //sLog.Write(Log::ERR, s_dataBaseTag, "Init DB %s failed!\n", conn.dbName);
        return false;
    }

    m_pHandler = m_dbFactory.GetCurrentHandler();

    if (m_tbUser.Init(m_pHandler) != 0)
    {
        //sLog.Write(Log::ERR, s_dataBaseTag, "Init TbUserDAO failed!\n");
        return false;
    }


    return true;
}


bool PaserAccInfo( )
{
    InitDb();
    SPYDATA_USER spydata;
    STR_CPY( spydata.Account , "myacc" ); 
    STR_CPY( spydata.Remarks , "myremark" );

    //Fill Primary Key
    std::ostringstream oss;
    oss
        << spydata.Common.TargetId
        << spydata.Common.TargetType
        << spydata.ProductId
        << spydata.OptType
        << spydata.Content
        << spydata.MainFile
        << spydata.OtherFiles
        << spydata.Remarks
        << spydata.Account
        << spydata.AccountType
        << spydata.Uid
        << spydata.Nickname
        << spydata.Phone
        << spydata.RealName
        << spydata.Address
        << spydata.Email
        << spydata.Company
        << spydata.Position
        << spydata.BirthPlace
        << spydata.School
        << spydata.Description
        << spydata.Sex
        << spydata.Age
        << spydata.Birthday
        << spydata.RegTime
        << spydata.LastLoginTime
        ;


    //DebugPrint("\r\n======== SPYDATA_USER ========\r\n");
    //DebugPrint("%s\r\n", oss.str().data());
    //DebugPrint("======== SPYDATA_USER ========\r\n\r\n");

    return true;
}
int oracletest()
{
    printf("PaserAccInfo\n");
    PaserAccInfo();
    printf("PaserAccInfo end\n");
    int ret  = 0;
    //    printf("hello....\n");
    //    printf("serverid:%s \n", serverid);
    //    EXEC SQL connect :serverid; 
    //    if (sqlca.sqlcode != 0)
    //    {
    //            ret = sqlca.sqlcode;
    //            printf("EXEC SQL connect:err, %d\n", ret);
    //            return ret;
    //    }
    //    printf("connect ok\n");
    return ret;
}

