--start /sql/access_log.sql
  --显示格式设置
    set linesize 200;
    set pagesize 300;
    --set wrap off
    col aid format 99999999;
    col site_id format 99999999;
    col icount format 99999999;
    col ddate format a40;
    select * from access_log;
    select * from user_tab_columns where Table_Name='access_log';
    select * from all_tab_columns where Table_Name='access_log'; 
    select * from dba_tab_columns where Table_Name='access_log'; 
/*
    DROP TABLE access_log;
    CREATE TABLE access_log
    (
	aid int ,
	site_id int DEFAULT '0',
	icount int DEFAULT '0',
	ddate date ,
 	PRIMARY KEY (aid)--主键不能为空
    );
    alter table access_log modify site_id not null;
    alter table access_log modify icount not null;
    alter table access_log modify ddate not null;
    comment on column access_log.site_id is '网站id字段';
    comment on column access_log.icount is '访问次数字段';
    comment on table access_log  is  '访问统计表';
    --INSERT INTO access_log VALUES (100,NULL,45,to_date('2015-7-18 11:42:56','yyyy-mm-dd hh24:mi:ss'));
    INSERT INTO access_log VALUES (1,1,45 ,to_date('2016-05-10','yyyy-mm-dd'));
    INSERT INTO access_log VALUES (2,3,100,to_date('2016-05-13','yyyy-mm-dd')); 
    INSERT INTO access_log VALUES (3,1,230,to_date('2016-05-14','yyyy-mm-dd'));
    INSERT INTO access_log VALUES (4,2,10 ,to_date('2016-05-14','yyyy-mm-dd')); 
    INSERT INTO access_log VALUES (5,5,205,to_date('2016-05-14','yyyy-mm-dd'));
    INSERT INTO access_log VALUES (6,4,13 ,to_date('2016-05-15','yyyy-mm-dd')); 
    INSERT INTO access_log VALUES (7,3,220,to_date('2016-05-15','yyyy-mm-dd'));
    INSERT INTO access_log VALUES (8,5,545,to_date('2016-05-16','yyyy-mm-dd')); 
    INSERT INTO access_log VALUES (9,3,201,to_date('2016-05-17','yyyy-mm-dd'));
*/

