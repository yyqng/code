#ifndef __GAJZSTD_H__
#define __GAJZSTD_H__

#include <map>
#include "Singleton.hpp"




#define GAJZ_ACTION_TYPE_CHAT                       "01"    // 聊天/私聊
#define GAJZ_ACTION_TYPE_LOGIN                      "02"    // 上线/登录
#define GAJZ_ACTION_TYPE_LOGOUT                     "03"    // 下线/离线/退出
#define GAJZ_ACTION_TYPE_ONLINE                     "04"    // 在线
#define GAJZ_ACTION_TYPE_STEALTH_ONLINE             "05"    // 隐身上线
#define GAJZ_ACTION_TYPE_STEALTH                    "06"    // 隐身
#define GAJZ_ACTION_TYPE_NEW_ARTICLE                "07"    // 发贴/发微博
#define GAJZ_ACTION_TYPE_REPLY_ARTICLE              "08"    // 回帖
#define GAJZ_ACTION_TYPE_MODIFY_ARTICLE             "09"    // 修改帖子
#define GAJZ_ACTION_TYPE_DEL_ARTICLE                "10"    // 删除帖子
#define GAJZ_ACTION_TYPE_FORWARD_ARTICLE            "11"    // 转载/分享/转发
#define GAJZ_ACTION_TYPE_UPDATE_BUDDY_LIST          "12"    // 更新好友列表
#define GAJZ_ACTION_TYPE_GROUP_CHAT                 "13"    // 群聊/群操作/发微群消息
#define GAJZ_ACTION_TYPE_UPDATE_GROUP_MEMBER_LIST   "14"    // 更新群成员列表
#define GAJZ_ACTION_TYPE_VIEW_DATA                  "15"    // 查看资料
#define GAJZ_ACTION_TYPE_UPDATE_ACCT_DATA           "16"    // 更新帐号信息
#define GAJZ_ACTION_TYPE_ADD_BUDDY                  "17"    // 新增好友
#define GAJZ_ACTION_TYPE_DEL_BUDDY                  "18"    // 删除好友
#define GAJZ_ACTION_TYPE_ACCEPT_BUDDY_INVITE        "19"    // 接受好友邀请
#define GAJZ_ACTION_TYPE_AUDIO_CHAT                 "20"    // 语音视频通信
#define GAJZ_ACTION_TYPE_AUDIO_CHAT_BEGIN           "21"    // 开始语音视频
#define GAJZ_ACTION_TYPE_AUDIO_CHAT_END             "22"    // 停止语音视频
//#define GAJZ_ACTION_TYPE_FILE_TRANSFER              "23"    // 文件传输
#define GAJZ_ACTION_TYPE_PLAY                       "24"    // 播放
#define GAJZ_ACTION_TYPE_COMMENT                    "25"    // 评论
#define GAJZ_ACTION_TYPE_ATTENTION                  "26"    // 关注/跟随
#define GAJZ_ACTION_TYPE_ATTENTION_CANCEL           "27"    // 撤销关注/跟随
#define GAJZ_ACTION_TYPE_UPLOAD                     "28"    // 上传
#define GAJZ_ACTION_TYPE_DOWNLOAD                   "29"    // 下载
#define GAJZ_ACTION_TYPE_UPDATE_DATA                "30"    // 更新/切换（认证数据）
#define GAJZ_ACTION_TYPE_RECV                       "31"    // 收邮件/收彩信
#define GAJZ_ACTION_TYPE_SEND                       "32"    // 发邮件/发彩信
#define GAJZ_ACTION_TYPE_BET                        "33"    // 投注
#define GAJZ_ACTION_TYPE_SEND_MSG                   "34"    // 发信息
#define GAJZ_ACTION_TYPE_RECV_FILE                  "35"    // 收文件
#define GAJZ_ACTION_TYPE_SEND_FILE                  "36"    // 发文件
#define GAJZ_ACTION_TYPE_REGISTER                   "37"    // 注册
#define GAJZ_ACTION_TYPE_CANCEL                     "38"    // 注销
#define GAJZ_ACTION_TYPE_LOCATE                     "39"    // 定位
#define GAJZ_ACTION_TYPE_SIGNIN                     "40"    // 签到
#define GAJZ_ACTION_TYPE_BACKUP                     "41"    // 备份
#define GAJZ_ACTION_TYPE_RESTORE                    "42"    // 恢复
#define GAJZ_ACTION_TYPE_ADD_CONTACT                "43"    // 增加联系人
#define GAJZ_ACTION_TYPE_DEL_CONTACT                "44"    // 删除联系人
#define GAJZ_ACTION_TYPE_REFER_OTHER                "45"    // 提及相关人（@）
#define GAJZ_ACTION_TYPE_ADD_WEIQUN                 "46"    // 加微群
#define GAJZ_ACTION_TYPE_VOTE                       "47"    // 投票
#define GAJZ_ACTION_TYPE_ORDER                      "48"    // 下订单
#define GAJZ_ACTION_TYPE_QUERY_ORDER                "49"    // 订单查询
#define GAJZ_ACTION_TYPE_VIEW_MAILLIST              "50"    // 查看邮件列表
//#define GAJZ_ACTION_TYPE_ORDER                      "51"  // 提交订单/在线下单,跟48下订单冲突
#define GAJZ_ACTION_TYPE_USUAL_OTEL                 "52"    // 常住酒店
#define GAJZ_ACTION_TYPE_PASSENGER_INFO             "53"    // 旅客信息
#define GAJZ_ACTION_TYPE_BOOK                       "54"    // 酒店/机票预定
#define GAJZ_ACTION_TYPE_WAYBILL_QUERY              "55"    // 运单查询
#define GAJZ_ACTION_TYPE_ONLINE_CHECKIN             "56"    // 网上值机
#define GAJZ_ACTION_TYPE_POSITION_PIC               "57"    // 位置图片
#define GAJZ_ACTION_TYPE_TRADE_HISTORY              "58"    // 交易历史
#define GAJZ_ACTION_TYPE_INDEX_WEB                  "59"    // 主页面
#define GAJZ_ACTION_TYPE_SEARCH                     "60"    // 搜索
#define GAJZ_ACTION_TYPE_ADDRBOOK                   "61"    // 通讯录
#define GAJZ_ACTION_TYPE_MAIL_LIST                  "62"    // 邮件列表
#define GAJZ_ACTION_TYPE_DISCUSS_GROUP              "63"    // 讨论组聊天
#define GAJZ_ACTION_TYPE_ORIGIN_DATA                "64"    // 原始数据包文件
#define GAJZ_ACTION_TYPE_LOGIN_PACKET               "65"    // 登陆包用于破解密码
#define GAJZ_ACTION_TYPE_ENCRYPTION_MAIL            "66"    // 加密邮件
#define GAJZ_ACTION_TYPE_BUDDY_ONLINE               "67"    // 好友上线
#define GAJZ_ACTION_TYPE_BUDDY_OFFLINE              "68"    // 好友下线
#define GAJZ_ACTION_TYPE_GROUP_LIST                 "69"    // 群列表
#define GAJZ_ACTION_TYPE_UPDATE_DATA_FILE           "70"    // 更新数据文件
#define GAJZ_ACTION_TYPE_INTEREST_LIST              "71"    // 关注列表
#define GAJZ_ACTION_TYPE_FANS_LIST                  "72"    // 粉丝列表
#define GAJZ_ACTION_TYPE_SHOPPING_CART              "73"    // 购物车
#define GAJZ_ACTION_TYPE_NEARBY_LIST                "74"    // 附近列表
#define GAJZ_ACTION_TYPE_OTHERS                     "99"    // 其他
#define GAJZ_ACTION_TYPE_BUDDYZONE                  "A0"    // 朋友圈




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



#define SEPERATESTRING      "|++|"

#define XML_END "== XML END ==\r\n"

#define XML_COMMON "\
<ITEM key=\"10A0006\" eng=\"INDEX_NAME\"/>\r\n\
<ITEM key=\"08A0014\" eng=\"CAPTURE_TIME\"/>\r\n\
<ITEM key=\"02D0007\" eng=\"CONTACT_ACCOUNT\"/>\r\n\
<ITEM key=\"02D0006\" eng=\"CONTACT_ACCOUNT_TYPE\"/>\r\n\
<ITEM key=\"08A0001\" eng=\"PROTOCOL\"/>\r\n\
<ITEM key=\"08A0003\" eng=\"ACTION_TYPE\"/>\r\n\
<ITEM key=\"08D0001\" eng=\"CONTENT\"/>\r\n\
<ITEM key=\"08A0019\" eng=\"MAINFILE\"/>\r\n\
<ITEM key=\"08A0020\" eng=\"FILE_NAME\"/>\r\n\
<ITEM key=\"09B0030\" eng=\"BUSINESS_SURVEY_RESULT\"/>\r\n\
<ITEM key=\"02D0002\" eng=\"USERNAME\"/>\r\n\
<ITEM key=\"02D0008\" eng=\"REG_ACCOUNT_TYPE\"/>\r\n\
"


#define XML_USER "\
<ITEM key=\"02D0019\" eng=\"ACCOUNT_ID\"/>\r\n\
<ITEM key=\"02D0004\" eng=\"NICKNAME\"/>\r\n\
<ITEM key=\"02B0005\" eng=\"USER_MOBILE\"/>\r\n\
<ITEM key=\"02D0026\" eng=\"USER_NAME\"/>\r\n\
<ITEM key=\"02C0234\" eng=\"ADDRESS\"/>\r\n\
<ITEM key=\"02D0023\" eng=\"EMAIL\"/>\r\n\
<ITEM key=\"05A0002\" eng=\"COMPANY\"/>\r\n\
<ITEM key=\"05B0006\" eng=\"POSITION\"/>\r\n\
<ITEM key=\"02A0026\" eng=\"BIRTH_PLACE\"/>\r\n\
<ITEM key=\"02C0129\" eng=\"SCHOOL_NAME\"/>\r\n\
<ITEM key=\"03A0009\" eng=\"CHARACTERISTIC_DESC\"/>\r\n\
<ITEM key=\"02A0011\" eng=\"SEXCODE\"/>\r\n\
<ITEM key=\"02A0015\" eng=\"AGE\"/>\r\n\
<ITEM key=\"02G0011\" eng=\"BIRTHDAY\"/>\r\n\
<ITEM key=\"07B0026\" eng=\"REGIS_TIME\"/>\r\n\
<ITEM key=\"03F0004\" eng=\"LAST_LOGIN_TIME\"/>\r\n\
"


#define XML_FRIEND "\
<ITEM key=\"02F0001\" eng=\"FRIEND_RELATION_TYPE\"/>\r\n\
<ITEM key=\"02F0002\" eng=\"FRIEND_ACCOUNT\"/>\r\n\
<ITEM key=\"02F0004\" eng=\"FRIEND_ID\"/>\r\n\
<ITEM key=\"02F0005\" eng=\"FRIEND_NICKNAME\"/>\r\n\
<ITEM key=\"02F0006\" eng=\"FRIEND_GROUP\"/>\r\n\
<ITEM key=\"02F0003\" eng=\"FRIEND_REMARK\"/>\r\n\
"


#define XML_SHOP "\
<ITEM key=\"08I0001\" eng=\"ORDER_NUM\"/>\r\n\
<ITEM key=\"02E0004\" eng=\"A_IDEN_STRING\"/>\r\n\
<ITEM key=\"02E0005\" eng=\"A_IDEN_NICKNAME\"/>\r\n\
<ITEM key=\"02E0009\" eng=\"B_IDEN_STRING\"/>\r\n\
<ITEM key=\"02E0010\" eng=\"B_IDEN_NICKNAME\"/>\r\n\
<ITEM key=\"02B0008\" eng=\"POSTAL_ADDRESS\"/>\r\n\
<ITEM key=\"05B0020\" eng=\"CONTACTOR_TEL\"/>\r\n\
<ITEM key=\"03A0001\" eng=\"MATERIALS_NAME\"/>\r\n\
<ITEM key=\"03A0006\" eng=\"MATERIALS_COUNT\"/>\r\n\
<ITEM key=\"03A0007\" eng=\"PURCHASE_PRICE\"/>\r\n\
<ITEM key=\"08I0004\" eng=\"ORDER_TIME\"/>\r\n\
<ITEM key=\"08I0017\" eng=\"EXTRACT_DESC\"/>\r\n\
<ITEM key=\"03B0002\" eng=\"MATERIALS_CODE\"/>\r\n\
"


#define XML_EMAIL "\
<ITEM key=\"08G0001\" eng=\"TOPIC_ID\"/>\r\n\
<ITEM key=\"02E0004\" eng=\"A_IDEN_STRING\"/>\r\n\
<ITEM key=\"02E0005\" eng=\"A_IDEN_NICKNAME\"/>\r\n\
<ITEM key=\"02E0009\" eng=\"B_IDEN_STRING\"/>\r\n\
<ITEM key=\"02E0010\" eng=\"B_IDEN_NICKNAME\"/>\r\n\
<ITEM key=\"08C0004\" eng=\"CC\"/>\r\n\
<ITEM key=\"08C0005\" eng=\"BCC\"/>\r\n\
<ITEM key=\"08C0008\" eng=\"MAIL_SEND_TIME\"/>\r\n\
<ITEM key=\"08A0029\" eng=\"DELETE_STATUS\"/>\r\n\
<ITEM key=\"09A0025\" eng=\"ROLE_TYPE\"/>\r\n\
<ITEM key=\"08C0010\" eng=\"FOLDER\"/>\r\n\
<ITEM key=\"08C0001\" eng=\"MAIL_SUBJECT\"/>\r\n\
"


#define XML_BLOG "\
<ITEM key=\"08G0001\" eng=\"TOPIC_ID\"/>\r\n\
<ITEM key=\"03K0002\" eng=\"CREATE_TIME\"/>\r\n\
<ITEM key=\"06A0001\" eng=\"LONGITUDE\"/>\r\n\
<ITEM key=\"06A0002\" eng=\"LATITUDE\"/>\r\n\
<ITEM key=\"06A0017\" eng=\"MSC_NAME\"/>\r\n\
<ITEM key=\"08B0001\" eng=\"TITLE\"/>\r\n\
<ITEM key=\"09A0028\" eng=\"TIMES\"/>\r\n\
"


#define XML_TRIP "\
<ITEM key=\"08I0001\" eng=\"ORDER_NUM\"/>\r\n\
<ITEM key=\"08I0004\" eng=\"ORDER_TIME\"/>\r\n\
<ITEM key=\"08I0017\" eng=\"EXTRACT_DESC\"/>\r\n\
<ITEM key=\"06A0014\" eng=\"DEPART_ADDRESS\"/>\r\n\
<ITEM key=\"06A0015\" eng=\"DESTINATION_ADDRESS\"/>\r\n\
<ITEM key=\"03B0002\" eng=\"MATERIALS_CODE\"/>\r\n\
"


#define XML_ADDRESS "\
<ITEM key=\"02B0008\" eng=\"POSTAL_ADDRESS\"/>\r\n\
<ITEM key=\"02B0009\" eng=\"POSTAL_CODE\"/>\r\n\
<ITEM key=\"05B0017\" eng=\"CONTACTOR\"/>\r\n\
<ITEM key=\"05B0020\" eng=\"CONTACTOR_TEL\"/>\r\n\
<ITEM key=\"02B0004\" eng=\"FIXED_PHONE\"/>\r\n\
<ITEM key=\"08I0017\" eng=\"EXTRACT_DESC\"/>\r\n\
<ITEM key=\"10B0002\" eng=\"DATA_STATUS\"/>\r\n\
"


#define XML_READ "\
<ITEM key=\"03K0002\" eng=\"CREATE_TIME\"/>\r\n\
<ITEM key=\"08I0017\" eng=\"EXTRACT_DESC\"/>\r\n\
<ITEM key=\"08B0001\" eng=\"TITLE\"/>\r\n\
<ITEM key=\"07A0006\" eng=\"LINK_URL\"/>\r\n\
"




#define PRODUCT_TEST          "1039999"
#define PRODUCT_XICIPROXY     "1110009"
#define PRODUCT_89PROXY       "1110010"
#define PRODUCT_KUAIPROXY     "1110011"
#define PRODUCT_QQ            "1030001"
#define PRODUCT_VOXER         "1030047"
#define PRODUCT_TAOBAO        "1220001"
#define PRODUCT_JINGDONG      "1220002"
#define PRODUCT_MEITUAN       "1220023"
#define PRODUCT_QQMAIL        "1010012"
#define PRODUCT_126MAIL       "1010018"
#define PRODUCT_163MAIL       "1010019"
#define PRODUCT_SINAWEIBO     "1330001"
#define PRODUCT_DIDI          "1450031"
#define PRODUCT_360CAMERA     "9780008"
#define PRODUCT_YSYCAMERA     "9780010"
#define PRODUCT_YOUKU         "1400002"
#define PRODUCT_DOUYIN        "1409026"
#define PRODUCT_MAIMAI        "1039379"
#define PRODUCT_HUANGGUAN     "1140025"




#define PRODUCT_NAME_TEST          "Test"
#define PRODUCT_NAME_XICIPROXY     "XiciProxy"
#define PRODUCT_NAME_89PROXY       "89Proxy"
#define PRODUCT_NAME_KUAIPROXY     "KuaiProxy"
#define PRODUCT_NAME_QQ            "QQ"
#define PRODUCT_NAME_VOXER         "Voxer"
#define PRODUCT_NAME_TAOBAO        "TaoBao"
#define PRODUCT_NAME_JINGDONG      "JingDong"
#define PRODUCT_NAME_MEITUAN       "MeiTuan"
#define PRODUCT_NAME_QQMAIL        "QQMail"
#define PRODUCT_NAME_126MAIL       "126Mail"
#define PRODUCT_NAME_163MAIL       "163Mail"
#define PRODUCT_NAME_SINAWEIBO     "SinaWeibo"
#define PRODUCT_NAME_DIDI          "Didi"
#define PRODUCT_NAME_360CAMERA     "360Camera"
#define PRODUCT_NAME_YSYCAMERA     "YsyCamera"
#define PRODUCT_NAME_YOUKU         "YouKu"
#define PRODUCT_NAME_DOUYIN        "DouYin"
#define PRODUCT_NAME_MAIMAI        "Maimai"
#define PRODUCT_NAME_HUANGGUAN     "HuangGuan"




enum ACCOUNT_TYPE
{
	ACCOUNT_REAL         = 0,	 // 上网帐号(默认)
	ACCOUNT_CALL         = 1,    // 主叫号码
	ACCOUNT_MSISDN       = 2,    // 手机号码
	ACCOUNT_IMSI         = 3,    // IMSI
	ACCOUNT_MAC          = 4,    // MAC
	ACCOUNT_IP           = 5,    // IP
	ACCOUNT_OTHERS       = 9,    // 其他
    ACCOUNT_UID          = 10,	 // ......以下是自定义
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


enum FRIEND_TYPE
{
	FRIEND_UNKNOWN	   = 0,	    // 普通好友(默认)
	FRIEND_IM          = 101,	// IM好友
	FRIEND_MAIL        = 102,   // 邮件好友
	FRIEND_GAME        = 103,   // 游戏好友
	FRIEND_TOPIC       = 104,   // 帖友
	FRIEND_BLOG        = 105,   // 博客好友
	FRIEND_MBLOG       = 106,   // 微博好友
    FRIEND_SOCIAL      = 107,	// 社交网络好友// ......以下是自定义
	FRIEND_GROUP       = 108,   // 群列表
	FRIEND_GMEMBERS    = 109,   // 群成员
    FRIEND_TRIP        = 203,   // 同行（同一个交通工具，同航班、同火车多次）
	FRIEND_PRISON      = 204,   // 狱友
	FRIEND_CASE        = 205,   // 同案
	FRIEND_WXPUBLIC    = 206,   // 微信关注的公众帐号
	FRIEND_OTHERS      = 999    // 其他
};


enum SEX_TYPE
{
	SEX_UNKNOWN  = 0,           // 未知的性别
	SEX_MALE     = 1,           // 男性
	SEX_FEMALE   = 2,           // 女性
	SEX_UNSTATED = 9            // 未说明的性别
};


enum READ_TYPE
{
	READ_UNKNOWN  = 0,           // 未知
	READ_YES      = 1,           // 已读
	READ_NO       = 2,           // 未读
};


enum MARK_TYPE
{
	MARK_UNKNOWN  = 0,           // 未知
	MARK_YES      = 1,           // 已标记
	MARK_NO       = 2,           // 未标记
};


enum ADDRESS_TYPE
{
	ADDRESS_UNKNOWN  = 0,        // 未知
	ADDRESS_DEFAULT  = 1,        // 默认地址
	ADDRESS_ELSE     = 2,        // 其他地址
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


//好友类
struct SPYDATA_FRIEND:ZeroStruct<SPYDATA_FRIEND> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容(个性签名)
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    FRIEND_TYPE       FriendType;                            // 好友类型
    char              FriendAcc[MAX_02F0002_C_LEN];          // 好友账号
    char              FriendUid[MAX_02F0004_C_LEN];          // 好友UID
    char              FriendNick[MAX_02F0005_C_LEN];         // 好友昵称
    char              FriendGroup[MAX_02F0006_C_LEN];        // 好友分组
    char              FriendTag[MAX_02F0003_C_LEN];          // 好友备注
};


//购物类
struct SPYDATA_SHOP:ZeroStruct<SPYDATA_SHOP> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件(商品图片)
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
	char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    char              OrderId[MAX_08I0001_C_LEN];            // 订单ID
    char              From[MAX_02E0004_C_LEN];               // 发货人帐号
    char              FromNick[MAX_02E0005_C_LEN];           // 发货人昵称
    char              To[MAX_02E0009_C_LEN];                 // 收货人帐号
    char              ToNick[MAX_02E0010_C_LEN];             // 收货人昵称
    char              ToAddress[MAX_02B0008_C_LEN];          // 收货人地址
    char              ToPhone[MAX_05B0020_C_LEN];            // 收货人电话
    char              Name[MAX_03A0001_C_LEN];               // 商品名称
    float             Count;                                 // 商品数量
    float             Price;                                 // 商品总价
    time_t            OrderTime;                             // 订单时间
    char              OrderType[MAX_08I0017_C_LEN];          // 订单类型
    char              OrderTag[MAX_03B0002_C_LEN];           // 订单标识

};


//邮件类
struct SPYDATA_EMAIL:ZeroStruct<SPYDATA_EMAIL> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容(邮件正文)
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    char              MailId[MAX_08G0001_C_LEN];             // 邮件ID
    char              From[MAX_08C0002_C_LEN];               // 发件人
    char              FromNick[MAX_02E0005_C_LEN];           // 发件人昵称
    char              To[MAX_08C0003_C_LEN];                 // 收件人
    char              ToNick[MAX_02E0010_C_LEN];             // 收件人昵称
    char              Cc[MAX_08C0004_C_LEN];                 // 抄送人
    char              Bcc[MAX_08C0005_C_LEN];                // 密送人
    time_t            SendTime;                              // 发送时间
    READ_TYPE         IsRead;                                // 是否已读，0未知，1已读，2未读
    MARK_TYPE         IsMark;                                // 是否标记重要，0未知，1已标记，2未标记
    char              Folder[MAX_08C0010_C_LEN];             // 邮件所属文件夹
    char              Subject[MAX_08C0001_C_LEN];            // 邮件主题
};


//博客类
struct SPYDATA_BLOG:ZeroStruct<SPYDATA_BLOG> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容(博客正文)
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    char              BlogId[MAX_08G0001_C_LEN];             // 博客ID
    time_t            CreateTime;                            // 创建时间
    char              Longitude[MAX_06A0001_C_LEN];          // 经度
    char              Latitude[MAX_06A0002_C_LEN];           // 纬度
    char              CoordinateType[MAX_06A0017_C_LEN];     // 坐标类型
    char              Title[MAX_08B0001_C_LEN];              // 博客标题
    int               ViewTimes;          // 浏览数
};


//出行类
struct SPYDATA_TRIP:ZeroStruct<SPYDATA_TRIP> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    char              TripId[MAX_08I0001_C_LEN];             // 出行订单ID
    time_t            OrderTime;                             // 出行订单时间
    char              OrderType[MAX_08I0017_C_LEN];          // 订单类型
    char              Depart[MAX_06A0014_C_LEN];             // 出发地址
    char              Destination[MAX_06A0015_C_LEN];        // 目的地址
    char              OrderTag[MAX_03B0002_C_LEN];           // 出行订单标识
};


//地址类
struct SPYDATA_ADDRESS:ZeroStruct<SPYDATA_ADDRESS> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    char              Address[MAX_02B0008_C_LEN];            // 详细地址
    char              PostalCode[MAX_02B0009_C_LEN];         // 邮政编码
    char              Contactor[MAX_05B0017_C_LEN];          // 联系人姓名
    char              Phone[MAX_05B0020_C_LEN];              // 联系人电话
    char              FixedPhone[MAX_02B0004_C_LEN];         // 固定电话
    char              Tag[MAX_08I0017_C_LEN];                // 地址标识
    ADDRESS_TYPE      IsDefault;                             // 是否默认地址，0未知，1默认地址，2其他地址
};


//订阅类
struct SPYDATA_READ:ZeroStruct<SPYDATA_READ> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              ProductId[MAX_08A0001_C_LEN];          // 产品号
    char              OptType[MAX_08A0003_C_LEN];            // 动作类型
    char              Content[MAX_08D0001_C_LEN];            // 内容(媒体信息)
    char              MainFile[MAX_08A0019_C_LEN];           // 实体文件
    char              OtherFiles[MAX_08A0020_C_LEN];         // 辅助文件列表
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    char              Account[MAX_02D0002_C_LEN];            // 用户账号
    ACCOUNT_TYPE      AccountType;                           // 帐号类型
    time_t            CreateTime;                            // 创建时间
    char              Tag[MAX_08I0017_C_LEN];                // 订阅标识
    char              Title[MAX_08B0001_C_LEN];              // 订阅标题
    char              Url[MAX_07A0006_C_LEN];                // 媒体URL
};





//布控目标类
struct SPYDATA_TARGET:ZeroStruct<SPYDATA_TARGET> 
{
    SPYDATA_COMMON    Common;                                // 公共字段
    char              Remarks[MAX_09B0030_C_LEN];            // 备注
    short             Status;                                // 布控状态
    char              LoginId[MAX_02D0002_C_LEN];            // 登录用户帐号
};





class GajzStd
{
    friend class TSingletonClass<GajzStd>;

public:

    std::string GetProductName(const std::string& productId);

private:

    GajzStd();
    virtual ~GajzStd();

    void Init();
    void BuildProductTable();


    typedef std::map<std::string, std::string> ProductTable;
    ProductTable m_productTable;

};
    
#define sGajzStd TSingletonClass<GajzStd>::GetInstance()


#endif


