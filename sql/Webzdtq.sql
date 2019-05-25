--start /sql/Webzdtq.sql
--表
  --TB_ADDRESS
  --TB_BLOG
  --TB_EMAIL
  --TB_FRIEND
  --TB_READ
  --TB_SHOP
  --TB_TRIP
  --TB_USER
    select count(PRODUCT_ID) from TB_USER where PRODUCT_ID = '1030001';

--字段  
  --REMARKS
  --PRODUCT_ID
  
--协议
  --#define PRODUCT_QQ            "1030001"
  --#define PRODUCT_MAIMAI        "1039379"
  --#define PRODUCT_VOXER         "1030047"
  
  --#define PRODUCT_DIDI          "1450031"
  --#define PRODUCT_DOUYIN        "1409026"
  --#define PRODUCT_YOUKU         "1400002"
  
  --#define PRODUCT_MEITUAN       "1220023"
  --#define PRODUCT_JINGDONG      "1220002"
  --#define PRODUCT_TAOBAO        "1220001"
  
  --#define PRODUCT_163MAIL       "1010019"
  --#define PRODUCT_QQMAIL        "1010012"
  
  --#define PRODUCT_126MAIL       "1010018"
  --#define PRODUCT_SINAWEIBO     "1330001"
  --#define PRODUCT_HUANGGUAN     "1140025"
  --#define PRODUCT_CAMERA360     "9780008"
  --#define PRODUCT_YSYCAMERA     "9780010"

  --显示格式设置
    set linesize 200;
    set pagesize 300;
    --set wrap off
    col id format 9999;
    col name format a20;
    col url format a40;
    col alexa format a10;
    col country format a10;
    select * from Websites;
    select count(id) from 表 where id = '1'

    


    
    
