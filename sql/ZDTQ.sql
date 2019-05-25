--数据导出
create or replace function num_to_date(in_number NUMBER) return date is
begin
    return(TO_DATE('19700101','yyyymmdd')+ in_number/86400+TO_NUMBER(SUBSTR(TZ_OFFSET(sessiontimezone),1,3))/24 );
end num_to_date;

SELECT  decode(TB_ADDRESS.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_ADDRESS.CAPTURE_TIME)      "探取时间", 
        ACCOUNT                                   "用户账号",
        decode(TB_ADDRESS.ACCOUNT_TYPE, '0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                        '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                        '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        ADDRESS                                   "详细地址",
        POSTAL_CODE                               "邮政编码",
        CONTACTOR                                 "联系人姓名",
        CONTACTOR_TEL                             "联系人电话",
        FIXED_PHONE                               "固定电话",
        ADDRESS_TAG                               "地址标识",
        decode(TB_ADDRESS.IS_DEFAULT, '0','未知', '1','是', '2','其他地址', 0) "是否默认地址",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_ADDRESS.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                   "目标账号" 
FROM TB_ADDRESS

SELECT  decode(TB_BLOG.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_BLOG.CAPTURE_TIME)            "探取时间",
        ACCOUNT                                      "用户账号",
        decode(TB_BLOG.ACCOUNT_TYPE, '0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                     '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                     '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        BLOG_ID                                      "博客ID",
        num_to_date(TB_BLOG.CREATE_TIME)             "创建时间",
        LONGITUDE                                    "经度",
        LATITUDE                                     "纬度",
        COORDINATE_TYPE                              "坐标类型",
        TITLE                                        "博客标题",
        VIEW_TIMES                                   "浏览数",
        CONTENT                                      "内容(博客正文)",
        MAIN_FILE                                    "实体文件",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_BLOG.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                      "目标账号"  
FROM TB_BLOG

SELECT  decode(TB_READ.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_READ.CAPTURE_TIME)         "探取时间",
        ACCOUNT                                   "用户账号",
        decode(TB_READ.ACCOUNT_TYPE, '0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                     '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                     '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        CREATE_TIME                               "订阅时间",
        READ_TAG                                  "订阅标识",
        TITLE                                     "订阅标题",
        READ_URL                                  "媒体URL",
        CONTENT                                   "内容(媒体信息)",
        MAIN_FILE                                 "实体文件",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_READ.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                   "目标账号"
FROM TB_READ

SELECT  decode(TB_FRIEND.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_FRIEND.CAPTURE_TIME)          "探取时间",
        ACCOUNT                                      "用户账号",
        FRIEND_ACC                                   "好友帐号",
        decode(TB_FRIEND.ACCOUNT_TYPE, '0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                       '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                       '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        decode(TB_FRIEND.FRIEND_TYPE, 0,'普通好友', 101,'IM好友', 102,'邮件好友', 103,'游戏好友',
                                       104,'帖友', 105,'博客好友', 106,'微博好友', 107,'社交网络好友', 203,'同行',
                                       204,'狱友', 205,'同案', 206,'微信关注的公众帐号',
                                       999,'其他', 0) "好友类型",
        FRIEND_UID                                   "好友内部ID",
        FRIEND_NICK                                  "好友昵称",
        FRIEND_GROUP                                 "好友分组",
        FRIEND_TAG                                   "好友备注",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_FRIEND.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                      "目标账号"
FROM TB_FRIEND

SELECT  decode(TB_TRIP.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_TRIP.CAPTURE_TIME)              "探取时间",
        ACCOUNT                                        "用户账号",
        decode(TB_TRIP.ACCOUNT_TYPE, '0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                     '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                     '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        TRIP_ID                                        "出行订单ID",
        num_to_date(TB_TRIP.ORDER_TIME)                "出行订单时间",
        ORDER_TYPE                                     "出行订单类型",
        DEPART_ADDRESS                                 "出发地址",
        DESTINATION_ADDRESS                            "目的地址",
        ORDER_TAG                                      "出行订单标识",
        CONTENT                                        "内容",
        MAIN_FILE                                      "实体文件",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_TRIP.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                        "目标账号" 
FROM TB_TRIP

SELECT  decode(TB_USER.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_USER.CAPTURE_TIME)           "探取时间",
        ACCOUNT                                     "用户账号",
        decode(TB_USER.ACCOUNT_TYPE, '0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                     '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                     '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        USER_ID                                     "内部ID",
        NICKNAME                                    "昵称",
        PHONE                                       "手机号",
        REALNAME                                    "姓名",
        decode(TB_USER.SEX, '0','未知', '1','男', '2','女', '9','未说明的性别', 0) "性别",
        AGE                                         "年龄",
        ADDRESS                                     "地址",
        EMAIL                                       "邮箱",
        COMPANY                                     "公司",
        POSITION                                    "职位",
        BIRTH_PLACE                                 "家乡",
        SCHOOL                                      "学校",
        BIRTHDAY                                    "出生日期",
        num_to_date(TB_USER.REG_TIME)               "注册时间",
        num_to_date(TB_USER.LAST_LOGIN_TIME)        "上次登录时间",
        CONTENT                                     "内容(个性签名)",
        DESCRIPTION                                 "个人简介",
        MAIN_FILE                                   "实体文件(头像)",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_USER.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                     "目标账号" 
FROM TB_USER

SELECT  decode(TB_EMAIL.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_EMAIL.CAPTURE_TIME)             "探取时间",
        ACCOUNT                                       "用户账号",
        decode(TB_EMAIL.ACCOUNT_TYPE,'0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                     '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                     '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        MAIL_ID                                       "邮件ID",
        FROM_ID                                       "发件人帐号",
        FROM_NICK                                     "发件人昵称",
        TO_ID                                         "收件人帐号",
        TO_NICK                                       "收件人昵称",
        CC_ID                                         "抄送人帐号",
        BCC_ID                                        "密送人帐号",
        FOLDER                                        "邮件类别(所属文件夹)",
        SUBJECT                                       "邮件主题",
        num_to_date(TB_EMAIL.SEND_TIME)               "邮件发送时间",
        decode(TB_EMAIL.IS_READ,'0','未知', '1','已读', '2','未读', 0) "是否已读",
        decode(TB_EMAIL.IS_MARK,'0','未知', '1','已标记', '2','未标记', 0) "是否标记重要",
        CONTENT                                       "内容(邮件正文)",
        MAIN_FILE                                     "实体文件(邮件正文)",
        OTHER_FILES                                   "辅助文件列表",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_EMAIL.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                       "目标账号"
FROM TB_EMAIL

SELECT  decode(TB_SHOP.PRODUCT_ID, '1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
                                   '1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', '1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
                                   '1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0) "产品ID",
        num_to_date(TB_SHOP.CAPTURE_TIME)             "探取时间",
        ACCOUNT		                                  "用户账号",
        decode(TB_SHOP.ACCOUNT_TYPE, '0','上网帐号', '1','主叫号码', '2','手机号码', '3','IMSI',
                                     '4','MAC', '9','其他', '10','UID', '11','昵称', '12','IMEI',
                                     '13','BROAD_TEL', '14','BROAD_ACCOUNT', 0) "帐号类型",
        ORDER_ID		                              "订单ID",
        FROM_ID		                                  "发货人帐号",
        FROM_NICK		                              "发件人昵称",
        TO_ID		                                  "收货人帐号",
        TO_NICK		                                  "收货人昵称",
        TO_ADDRESS		                              "收货人地址",
        TO_PHONE		                              "收货人电话",
        MATERIALS_NAME		                          "商品名称",
        MATERIALS_COUNT		                          "商品数量",
        PURCHASE_PRICE		                          "商品总价",
        num_to_date(TB_SHOP.ORDER_TIME)               "订单时间",
        ORDER_TYPE		                              "订单类型",
        ORDER_TAG		                              "订单标识",
        CONTENT		                                  "内容",
        MAIN_FILE		                              "实体文件",
        TARGET_ID		                              "TARGET_ID",
        TARGET_TYPE		                              "TARGET_TYPE",
        decode(TB_SHOP.OPT_TYPE, '07','日志列表', '12','好友列表', '16','账号信息', '24','播放历史',
                                 '26','订阅列表', '49','订单信息', '57','相册列表', '61','通讯录', '62','邮件信息','71','关注列表', '72','粉丝列表',0) "OPT_TYPE",
        REMARKS                                       "目标账号"
FROM TB_SHOP
      
--数据统计
--'1030001','QQ', '1039379','脉脉', '1030047','VOXER', '1450031','滴滴',
--'1409026','抖音', '1400002','优酷', '1220023','美团', '1220002','京东', 
--'1220001','淘宝','1010019','163邮箱', '1010012','QQ邮箱', '1010018','126邮箱',
--'1330001','新浪','1140025','皇冠', '9780008','360', '9780010','萤石云',0)

--统计用户总数；
SELECT (REMARKS) FROM TB_ADDRESS  UNION 
SELECT (REMARKS) FROM TB_BLOG     UNION 
SELECT (REMARKS) FROM TB_EMAIL    UNION 
SELECT (REMARKS) FROM TB_FRIEND   UNION 
SELECT (REMARKS) FROM TB_READ     UNION 
SELECT (REMARKS) FROM TB_SHOP     UNION
SELECT (REMARKS) FROM TB_TRIP     UNION 
SELECT (REMARKS) FROM TB_USER     ; 

--按协议统计用户数和话单数
--不使用 count ：统计用户数； 使用 count ：统计话单数
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1030001 UNION --QQ
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1030001 UNION --QQ
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1030001 UNION --QQ
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1030001 UNION --QQ
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1030001 UNION --QQ
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1030001 UNION --QQ
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1030001 UNION --QQ
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1030001;      --QQ
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1039379 UNION --脉脉
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1039379 UNION --脉脉
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1039379 UNION --脉脉
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1039379 UNION --脉脉
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1039379 UNION --脉脉
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1039379 UNION --脉脉
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1039379 UNION --脉脉
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1039379;      --脉脉
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1030047 UNION --VOXER
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1030047 UNION --VOXER
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1030047 UNION --VOXER
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1030047 UNION --VOXER
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1030047 UNION --VOXER
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1030047 UNION --VOXER
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1030047 UNION --VOXER
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1030047;      --VOXER
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1450031 UNION --滴滴
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1450031 UNION --滴滴
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1450031 UNION --滴滴
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1450031 UNION --滴滴
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1450031 UNION --滴滴
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1450031 UNION --滴滴
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1450031 UNION --滴滴
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1450031;      --滴滴
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1409026 UNION --抖音
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1409026 UNION --抖音
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1409026 UNION --抖音
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1409026 UNION --抖音
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1409026 UNION --抖音
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1409026 UNION --抖音
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1409026 UNION --抖音
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1409026;      --抖音
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1400002 UNION --优酷
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1400002 UNION --优酷
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1400002 UNION --优酷
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1400002 UNION --优酷
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1400002 UNION --优酷
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1400002 UNION --优酷
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1400002 UNION --优酷
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1400002;      --优酷
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1220023 UNION --美团
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1220023 UNION --美团
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1220023 UNION --美团
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1220023 UNION --美团
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1220023 UNION --美团
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1220023 UNION --美团
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1220023 UNION --美团
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1220023;      --美团
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1220002 UNION --京东
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1220002 UNION --京东
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1220002 UNION --京东
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1220002 UNION --京东
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1220002 UNION --京东
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1220002 UNION --京东
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1220002 UNION --京东
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1220002;      --京东
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1220001 UNION --淘宝
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1220001 UNION --淘宝
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1220001 UNION --淘宝
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1220001 UNION --淘宝
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1220001 UNION --淘宝
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1220001 UNION --淘宝
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1220001 UNION --淘宝
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1220001;      --淘宝
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1010019 UNION --163邮箱
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1010019 UNION --163邮箱
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1010019 UNION --163邮箱
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1010019 UNION --163邮箱
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1010019 UNION --163邮箱
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1010019 UNION --163邮箱
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1010019 UNION --163邮箱
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1010019;      --163邮箱
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1010012 UNION --QQ邮箱
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1010012 UNION --QQ邮箱
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1010012 UNION --QQ邮箱
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1010012 UNION --QQ邮箱
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1010012 UNION --QQ邮箱
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1010012 UNION --QQ邮箱
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1010012 UNION --QQ邮箱
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1010012;      --QQ邮箱
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1010018 UNION --126邮箱
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1010018 UNION --126邮箱
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1010018 UNION --126邮箱
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1010018 UNION --126邮箱
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1010018 UNION --126邮箱
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1010018 UNION --126邮箱
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1010018 UNION --126邮箱
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1010018;      --126邮箱
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1330001 UNION --新浪微博
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1330001 UNION --新浪微博
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1330001 UNION --新浪微博
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1330001 UNION --新浪微博
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1330001 UNION --新浪微博
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1330001 UNION --新浪微博
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1330001 UNION --新浪微博
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1330001;      --新浪微博
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=1140025 UNION --皇冠
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=1140025 UNION --皇冠
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=1140025 UNION --皇冠
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=1140025 UNION --皇冠
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=1140025 UNION --皇冠
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=1140025 UNION --皇冠
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=1140025 UNION --皇冠
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=1140025;      --皇冠
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=9780008 UNION --360摄像头
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=9780008 UNION --360摄像头
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=9780008 UNION --360摄像头
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=9780008 UNION --360摄像头
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=9780008 UNION --360摄像头
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=9780008 UNION --360摄像头
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=9780008 UNION --360摄像头
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=9780008;      --360摄像头
SELECT count(REMARKS) FROM TB_ADDRESS WHERE PRODUCT_ID=9780010 UNION --萤石云视频
SELECT count(REMARKS) FROM TB_BLOG    WHERE PRODUCT_ID=9780010 UNION --萤石云视频
SELECT count(REMARKS) FROM TB_READ    WHERE PRODUCT_ID=9780010 UNION --萤石云视频
SELECT count(REMARKS) FROM TB_FRIEND  WHERE PRODUCT_ID=9780010 UNION --萤石云视频
SELECT count(REMARKS) FROM TB_TRIP    WHERE PRODUCT_ID=9780010 UNION --萤石云视频
SELECT count(REMARKS) FROM TB_USER    WHERE PRODUCT_ID=9780010 UNION --萤石云视频
SELECT count(REMARKS) FROM TB_EMAIL   WHERE PRODUCT_ID=9780010 UNION --萤石云视频
SELECT count(REMARKS) FROM TB_SHOP    WHERE PRODUCT_ID=9780010;      --萤石云视频
