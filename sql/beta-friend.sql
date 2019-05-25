--start /sql/beta-friend.sql
    set linesize 200;
    set pagesize 300;
    --set wrap off
    col SEQ_UUID format a20;
    col MD5_UUID format a2;
    col CAPTURE_TIME format 99999999999;
    col TARGET_ID format a2;
    col TARGET_TYPE format a2;
    col PRODUCT_ID format a10;
    col OPT_TYPE format a2;
    col CONTENT format a2;
    col MAIN_FILE format a2;
    col OTHER_FILES format a2;
    col REMARKS format a2;
    col ACCOUNT format a20;
    col ACCOUNT_TYPE format a2;
    col FRIEND_TYPE format a2;
    col FRIEND_ACC format a20;
    col FRIEND_UID format a20;
    col FRIEND_NICK format a20;
    col FRIEND_GROUP format a2;
    col FRIEND_TAG format a2;
--start /sql/beta-user.sql
    SELECT PRODUCT_ID,ACCOUNT,FRIEND_NICK,FRIEND_ACC,FRIEND_UID FROM TB_FRIEND where product_id='1010019';
    
    



