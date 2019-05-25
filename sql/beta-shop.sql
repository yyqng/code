--start /sql/beta-shop.sql
    set linesize 200;
    set pagesize 300;
    --set wrap off
    col ORDER_TAG format a20;
    col ORDER_TYPE format 9999;
    col ORDER_TIME format 99999999999;
    col PURCHASE_PRICE format 99999999999.00;
    col MATERIALS_COUNT format 9999;
    col MATERIALS_NAME format a20;
    col TO_PHONE format a20;
    col TO_ADDRESS format a20;
    col TO_NICK format a20;
    col TO_ID format a10;
    col FROM_NICK format a10;
    col FROM_ID format a20;
    col ORDER_ID format a20;
    col ACCOUNT_TYPE format a20;
    col ACCOUNT format a10;
    col REMARKS format a20;
    col OTHER_FILES format a20;
    col MAIN_FILE format a20;
    col CONTENT format a20;
    col OPT_TYPE format a20;
    col PRODUCT_ID format a20;
    col TARGET_TYPE format a20;
    col TARGET_ID format a20;
    col CAPTURE_TIME format a20;
    col MD5_UUID format a20;
    col SEQ_UUID format a10;
--start /sql/beta-shop.sql
    --select table_name from user_tables;
    --select * from user_tab_columns t where t.Table_Name='TB_SHOP';
    SELECT ACCOUNT,ORDER_TIME,PURCHASE_PRICE,REMARKS FROM TB_SHOP where PRODUCT_ID=1290001; 
    SELECT ACCOUNT, CONTENT, ORDER_TAG FROM TB_SHOP where PRODUCT_ID=1290001; 
    SELECT * FROM TB_SHOP where PRODUCT_ID=1280008; 
    --SELECT ACCOUNT,ORDER_TIME,PURCHASE_PRICE,REMARKS FROM TB_SHOP where ACCOUNT='8fff7';
    --SELECT * FROM TB_USER where product_id='1140025';
   
    


