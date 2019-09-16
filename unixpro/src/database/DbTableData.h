#ifndef __DB_TABLE_DATA_H__
#define __DB_TABLE_DATA_H__

#include <string.h>
#include "GajzStd.h"



#ifndef DELETE_STMT_OBJ
#define DELETE_STMT_OBJ(p) do{if (p != NULL) {p->Destroy(); delete p; p = NULL;}}while(0);
#endif


#define DB_NAME "orcl"
#define DB_USER "zdzc"
#define DB_PWD  "zdzc"
//#define DB_URL  "localhost:1521/orcl"
//#define DB_URL  "192.192.192.154:1521/broad"



#define SEQ_SEQUENCE_EXIST_SQL "SELECT COUNT(1) FROM USER_SEQUENCES WHERE SEQUENCE_NAME = '%s'"

#define SEQ_SEQUENCE_CREATE_SQL "CREATE SEQUENCE %s INCREMENT BY 1 START WITH 10000 NOMAXVALUE NOCYCLE NOCACHE"


#define TB_TABLE_EXIST_SQL "SELECT COUNT(1) FROM ALL_TABLES WHERE TABLE_NAME = '%s'"


#define TB_USER_CREATE_TABLE_SQL "\
CREATE TABLE TB_USER (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    USER_ID              VARCHAR(64),      \
    NICKNAME             VARCHAR(255),     \
    PHONE                VARCHAR(32),      \
    REALNAME             VARCHAR(64),      \
    ADDRESS              VARCHAR(255),     \
    EMAIL                VARCHAR(64),      \
    COMPANY              VARCHAR(128),     \
    POSITION             VARCHAR(32),      \
    BIRTH_PLACE          VARCHAR(512),     \
    SCHOOL               VARCHAR(255),     \
    DESCRIPTION          VARCHAR(4000),    \
    SEX                  CHAR(1),          \
    AGE                  SMALLINT,         \
    BIRTHDAY             DATE,             \
    REG_TIME             INTEGER,          \
    LAST_LOGIN_TIME      INTEGER           \
)"

#define TB_USER_INSERT_SQL "\
INSERT INTO TB_USER (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
    ACCOUNT_TYPE,    \
    USER_ID,         \
    NICKNAME,        \
    PHONE,           \
    REALNAME,        \
    ADDRESS,         \
    EMAIL,           \
    COMPANY,         \
    POSITION,        \
    BIRTH_PLACE,     \
    SCHOOL,          \
    DESCRIPTION,     \
    SEX,             \
    AGE,             \
    BIRTHDAY,        \
    REG_TIME,        \
    LAST_LOGIN_TIME  \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23,:24,:25,:26,:27,:28)"

#define TB_USER_SELECT_PRODUCTID_SQL "SELECT * FROM TB_USER where PRODUCT_ID = :1"



#define TB_FRIEND_CREATE_TABLE_SQL "\
CREATE TABLE TB_FRIEND (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    FRIEND_TYPE          CHAR(3),          \
    FRIEND_ACC           VARCHAR(64),      \
    FRIEND_UID           VARCHAR(64),      \
    FRIEND_NICK          VARCHAR(64),      \
    FRIEND_GROUP         VARCHAR(64),      \
    FRIEND_TAG           VARCHAR(64)       \
)"

#define TB_FRIEND_INSERT_SQL "\
INSERT INTO TB_FRIEND (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
    ACCOUNT_TYPE,    \
    FRIEND_TYPE,     \
    FRIEND_ACC,      \
    FRIEND_UID,      \
    FRIEND_NICK,     \
    FRIEND_GROUP,    \
    FRIEND_TAG       \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18)"

#define TB_FRIEND_SELECT_PRODUCTID_SQL "SELECT * FROM TB_FRIEND where PRODUCT_ID = :1"




#define TB_SHOP_CREATE_TABLE_SQL "\
CREATE TABLE TB_SHOP (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    ORDER_ID             VARCHAR(128),     \
    FROM_ID              VARCHAR(128),     \
    FROM_NICK            VARCHAR(128),     \
    TO_ID                VARCHAR(128),     \
    TO_NICK              VARCHAR(128),     \
    TO_ADDRESS           VARCHAR(255),     \
    TO_PHONE             VARCHAR(128),     \
    MATERIALS_NAME       VARCHAR(128),     \
    MATERIALS_COUNT      FLOAT,            \
    PURCHASE_PRICE       FLOAT,            \
    ORDER_TIME           INTEGER,          \
    ORDER_TYPE           VARCHAR(512),     \
    ORDER_TAG            VARCHAR(64)       \
)"

#define TB_SHOP_INSERT_SQL "\
INSERT INTO TB_SHOP (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
	ACCOUNT_TYPE,    \
    ORDER_ID,        \
    FROM_ID,         \
    FROM_NICK,       \
    TO_ID,           \
    TO_NICK,         \
    TO_ADDRESS,      \
    TO_PHONE,        \
    MATERIALS_NAME,  \
    MATERIALS_COUNT, \
    PURCHASE_PRICE,  \
    ORDER_TIME,      \
    ORDER_TYPE,      \
    ORDER_TAG        \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23,:24,:25)"

#define TB_SHOP_SELECT_PRODUCTID_SQL "SELECT * FROM TB_SHOP where PRODUCT_ID = :1"



#define TB_EMAIL_CREATE_TABLE_SQL "\
CREATE TABLE TB_EMAIL (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    MAIL_ID              VARCHAR(128),     \
    FROM_ID              VARCHAR(128),     \
    FROM_NICK            VARCHAR(128),     \
    TO_ID                VARCHAR(128),     \
    TO_NICK              VARCHAR(128),     \
    CC_ID                VARCHAR(128),     \
    BCC_ID               VARCHAR(128),     \
    SEND_TIME            INTEGER,          \
    IS_READ              CHAR(1),          \
    IS_MARK              CHAR(1),          \
    FOLDER               VARCHAR(256),     \
    SUBJECT              VARCHAR(512)      \
)"

#define TB_EMAIL_INSERT_SQL "\
INSERT INTO TB_EMAIL (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
    ACCOUNT_TYPE,    \
    MAIL_ID,         \
    FROM_ID,         \
    FROM_NICK,       \
    TO_ID,           \
    TO_NICK,         \
    CC_ID,           \
    BCC_ID,          \
    SEND_TIME,       \
    IS_READ,         \
    IS_MARK,         \
    FOLDER,          \
    SUBJECT          \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23,:24)"

#define TB_EMAIL_SELECT_PRODUCTID_SQL "SELECT * FROM TB_EMAIL where PRODUCT_ID = :1"



#define TB_BLOG_CREATE_TABLE_SQL "\
CREATE TABLE TB_BLOG (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    BLOG_ID              VARCHAR(64),      \
    CREATE_TIME          INTEGER,          \
    LONGITUDE            VARCHAR(18),      \
    LATITUDE             VARCHAR(18),      \
    COORDINATE_TYPE      VARCHAR(64),      \
	TITLE                VARCHAR(128),     \
	VIEW_TIMES           INTEGER           \
)"

#define TB_BLOG_INSERT_SQL "\
INSERT INTO TB_BLOG (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
    ACCOUNT_TYPE,    \
    BLOG_ID,         \
    CREATE_TIME,     \
    LONGITUDE,       \
    LATITUDE,        \
    COORDINATE_TYPE, \
    TITLE,           \
    VIEW_TIMES       \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19)"

#define TB_BLOG_SELECT_PRODUCTID_SQL "SELECT * FROM TB_BLOG where PRODUCT_ID = :1"



#define TB_TRIP_CREATE_TABLE_SQL "\
CREATE TABLE TB_TRIP (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    TRIP_ID              VARCHAR(128),     \
    ORDER_TIME           INTEGER,          \
    ORDER_TYPE           VARCHAR(512),     \
    DEPART_ADDRESS       VARCHAR(256),     \
    DESTINATION_ADDRESS  VARCHAR(256),     \
    ORDER_TAG            VARCHAR(64)       \
)"

#define TB_TRIP_INSERT_SQL "\
INSERT INTO TB_TRIP (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
    ACCOUNT_TYPE,    \
    TRIP_ID,         \
    ORDER_TIME,      \
    ORDER_TYPE,      \
    DEPART_ADDRESS,          \
    DESTINATION_ADDRESS,     \
    ORDER_TAG        \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18)"

#define TB_TRIP_SELECT_PRODUCTID_SQL "SELECT * FROM TB_TRIP where PRODUCT_ID = :1"



#define TB_ADDRESS_CREATE_TABLE_SQL "\
CREATE TABLE TB_ADDRESS (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    ADDRESS              VARCHAR(255),     \
    POSTAL_CODE          CHAR(6),          \
    CONTACTOR            VARCHAR(128),     \
    CONTACTOR_TEL        VARCHAR(128),     \
    FIXED_PHONE          VARCHAR(32),      \
    ADDRESS_TAG          VARCHAR(512),     \
    IS_DEFAULT           CHAR(1)           \
)"

#define TB_ADDRESS_INSERT_SQL "\
INSERT INTO TB_ADDRESS (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
    ACCOUNT_TYPE,    \
    ADDRESS,         \
    POSTAL_CODE,     \
    CONTACTOR,       \
    CONTACTOR_TEL,   \
    FIXED_PHONE,     \
    ADDRESS_TAG,     \
    IS_DEFAULT       \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19)"

#define TB_ADDRESS_SELECT_PRODUCTID_SQL "SELECT * FROM TB_ADDRESS where PRODUCT_ID = :1"



#define TB_READ_CREATE_TABLE_SQL "\
CREATE TABLE TB_READ (\
    SEQ_UUID             INTEGER,          \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,      \
    CAPTURE_TIME         INTEGER NOT NULL, \
    TARGET_ID            VARCHAR(64),      \
    TARGET_TYPE          VARCHAR(7),       \
    PRODUCT_ID           CHAR(7) NOT NULL, \
    OPT_TYPE             CHAR(2) NOT NULL, \
    CONTENT              VARCHAR(4000),    \
    MAIN_FILE            VARCHAR(255),     \
    OTHER_FILES          VARCHAR(4000),    \
    REMARKS              VARCHAR(4000),    \
    ACCOUNT              VARCHAR(64),      \
    ACCOUNT_TYPE         VARCHAR(7),       \
    CREATE_TIME          INTEGER,          \
    READ_TAG             VARCHAR(512),     \
	TITLE                VARCHAR(128),     \
    READ_URL             VARCHAR(4000)     \
)"

#define TB_READ_INSERT_SQL "\
INSERT INTO TB_READ (\
	SEQ_UUID,        \
	MD5_UUID,	     \
    CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    PRODUCT_ID,      \
    OPT_TYPE,        \
    CONTENT,         \
    MAIN_FILE,       \
    OTHER_FILES,     \
    REMARKS,         \
    ACCOUNT,         \
    ACCOUNT_TYPE,    \
    CREATE_TIME,     \
    READ_TAG,        \
    TITLE,           \
    READ_URL         \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16)"

#define TB_READ_SELECT_PRODUCTID_SQL "SELECT * FROM TB_READ where PRODUCT_ID = :1"






#define TB_TARGET_CREATE_TABLE_SQL "\
CREATE TABLE TB_TARGET (\
    SEQ_UUID             INTEGER,                    \
    MD5_UUID             VARCHAR(32) PRIMARY KEY,    \
    CAPTURE_TIME         INTEGER NOT NULL,           \
    TARGET_ID            VARCHAR(64) NOT NULL,       \
    TARGET_TYPE          VARCHAR(7) NOT NULL,        \
    REMARKS              VARCHAR(4000),              \
    STATUS               SMALLINT NOT NULL,          \
    LOGIN_ID             VARCHAR(64) NOT NULL        \
)"

#define TB_TARGET_INSERT_SQL "\
INSERT INTO TB_TARGET (\
	SEQ_UUID,		 \
	MD5_UUID,		 \
	CAPTURE_TIME,    \
    TARGET_ID,       \
    TARGET_TYPE,     \
    REMARKS,         \
    STATUS,          \
    LOGIN_ID         \
)\
VALUES(SEQ_ID.NEXTVAL,:1,:2,:3,:4,:5,:6,:7)"

#define TB_TARGET_SELECT_TARGETID_SQL "SELECT * FROM TB_TARGET where TARGET_ID = :1"




#endif  // __DB_TABLE_DATA_H__
