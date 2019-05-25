--start /sql/beta-user.sql
    set linesize 200;
    set pagesize 300;
    --set wrap off
    col LAST_LOGIN_TIME format a2;
    col SEQ_UUID format 99999999999;
    col MD5_UUID format a2;
    col REG_TIME format a2;
    col BIRTHDAY format a2;
    col AGE format a2;
    col SEX format a2;
    col DESCRIPTION format a2;
    col SCHOOL format a2;
    col REMARKS format a10;
    col ACCOUNT format a20;
    col ACCOUNT_TYPE format a2;
    col USER_ID format a2;
    col NICKNAME format a2;
    col PHONE format a2;
    col REALNAME format a10;
    col ADDRESS format a2;
    col EMAIL format a2;
    col COMPANY format a2;
    col POSITION format a2;
    col BIRTH_PLACE format a2;
    col OTHER_FILES format a2;
    col MAIN_FILE format a2;
    col CONTENT format a2;
    col OPT_TYPE format a2;
    col PRODUCT_ID format a10;
    col TARGET_TYPE format a18;
    col TARGET_ID format a2;
    col CAPTURE_TIME format 99999999999;
--start /sql/beta-user.sql
    --SELECT PRODUCT_ID,TARGET_TYPE,NICKNAME,REALNAME,ACCOUNT FROM TB_USER where product_id='1010019' and REALNAME='yyq163';
    --select table_name from user_tables;
    --select * from user_tab_columns t where t.Table_Name='TB_USER';
	--DELETE FROM TB_USER WHERE product_id='1010018' and ACCOUNT='yyqngg@126.com';
    --SELECT PRODUCT_ID,TARGET_TYPE,REMARKS,ACCOUNT FROM TB_USER where product_id='1140025';
    --SELECT PRODUCT_ID,TARGET_TYPE,REMARKS,ACCOUNT FROM TB_USER where product_id='1010018';
    --SELECT * FROM TB_USER where product_id='1140025';
    --SELECT * FROM TB_TRIP;
  
