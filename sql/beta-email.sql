--start /sql/beta-email.sql
    set linesize 300;
    set pagesize 300;
    set wrap off
    col LAST_LOGIN_TIME format a2;
    col SEQ_UUID format 99999999999;
    col MD5_UUID format a2;
    col CAPTURE_TIME format a20;
    col TARGET_ID format a2;
    col TARGET_TYPE format a2;
    col PRODUCT_ID format a20;
    col OPT_TYPE format a20;
    col CONTENT format a20;
    col MAIN_FILE format a10;
    col OTHER_FILES format a10;
    col REMARKS format a2;
    col ACCOUNT format a20;
    col ACCOUNT_TYPE format a2;
    col MAIL_ID format a2;
    col FROM_ID format a10;
    col FROM_NICK format a10;
    col TO_ID format a10;
    col TO_NICK format a10;
    col CC_ID format a10;
    col BCC_ID format a10;
    col SEND_TIME format 99999999999;
    col IS_READ format a10;
    col IS_MARK format a10;
    col FOLDER format a10;
    col SUBJECT format a30;
    --select * from user_tab_columns where Table_Name='TB_EMAIL';
--start /sql/beta-email.sql
	--DELETE FROM TB_EMAIL WHERE product_id='1010018' and ACCOUNT='yyqngg@126.com';
    --SELECT PRODUCT_ID,TARGET_TYPE,REMARKS,ACCOUNT FROM TB_EMAIL where product_id='1010018';
    SELECT PRODUCT_ID,ACCOUNT,FROM_ID,FROM_NICK,TO_ID,TO_NICK,CC_ID,BCC_ID,SEND_TIME,IS_READ,FOLDER,SUBJECT FROM TB_EMAIL where product_id='1010019';
    
    


