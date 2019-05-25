--表
  --显示格式设置
    set linesize 200;
    set pagesize 300;
    --set wrap off
    col id format 9999;
    col name format a20;
    col url format a40;
    col alexa format a10;
    col country format a10;
  --查看表：
    --select table_name from user_tables;                     --当前用户的表 
    --select table_name from all_tables;                      --所有用户的表
    --select table_name from dba_tables;                      --包括系统表
    --select table_name from dba_tables where owner='用户名'   --根据用户名查看表
  --更改表名
    ALTER TABLE table_name RENAME TO new_table_name；
  --获取表字段：
    --select * from user_tab_columns where Table_Name='TB_FRIEND';
    --select * from all_tab_columns where Table_Name='用户表';
    --select * from dba_tab_columns where Table_Name='用户表';
  --获取表注释：
    --select * from user_tab_comments
    --user_tab_comments：table_name,table_type,comments
    --相应的还有dba_tab_comments，all_tab_comments，这两个比user_tab_comments多了ower列。 
  --获取字段注释：
    --select * from user_col_comments user_col_comments：table_name,column_name,comments


  --删除表：
    --DROP table Websites;
/*    CREATE TABLE Websites
    (
	id number,
	name varchar(255),
	url varchar(255),
	alexa varchar(255),
	country varchar(255)
    );
*/
  --删除表中的行
    --DELETE FROM Websites WHERE name='百度' OR country='CN';
    --DELETE FROM Websites ;
  --插入新行：
/*    INSERT INTO Websites (id, name, url, alexa, country)VALUES (2,'Google','https://www.google.com/','1','USA');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (1,'淘宝','https://www.taobao.com/','13','CN');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (5,'菜鸟教程','http://www.runoob.com/','4689','CN');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (4,'微博','http://weibo.com/','20','CN');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (3,'Facebook','https://www.facebook.com/','3','USA');
    INSERT INTO Websites (name, url, country) VALUES ('stackoverflow', 'http://stackoverflow.com/', 'IND');
    INSERT INTO Websites VALUES (7,'tencent', 'http://qq.com/','21', 'CN');
*/
  --更新记录
    --UPDATE Websites SET alexa='5000', country='USA' WHERE name='菜鸟教程';
  --删除记录
    --DELETE FROM Websites WHERE name='stackoverflow';
    --删除表test里的内容，但不删除表的结构，不释放空间，
    --DELETE * FROM Websites;
    --删除表test里的内容，但不删除表的结构，释放空间，数据不可以回滚恢复
    --TRUNCATE Websites;
  --选取数据，存储在结果表中，称为结果集
    SELECT * FROM Websites;
    --SELECT name,country FROM Websites;
    --SELECT DISTINCT country FROM Websites;
    --SELECT * FROM Websites WHERE alexa>=15 and (name='Google' OR country='CN');
    --SELECT * FROM Websites ORDER BY id;
    --SELECT * FROM Websites ORDER BY id DESC;
    --SELECT * FROM Websites ORDER BY country,alexa;
  --选取前若干条数据
    --SELECT * FROM Websites limit 5;--oracle不支持limit
    --SELECT * FROM Websites where rownum<=5;
    --SELECT * FROM Websites a WHERE ROWNUM <= 2;
    --SELECT * FROM Websites where rownum<=5 minus select * from Websites where rownum<2;
    --SELECT * FROM (SELECT a.*, ROWNUM rn FROM Websites a) WHERE rn >= 2 AND rn <= 5;
    --SELECT * FROM (SELECT a.*, ROWNUM rn FROM Websites a) WHERE rn >= (select count(*)*0.5 from Websites) AND rn <= 5; 
    --SELECT TOP 50 PERCENT * FROM Websites;--oracle不支持TOP
  --通配符
    --%表示 0 个或多个字符
    --SELECT * FROM Websites WHERE name LIKE 'G%';
    --SELECT * FROM Websites WHERE name LIKE '%k';
    --SELECT * FROM Websites WHERE name LIKE '%oo%';
    --SELECT * FROM Websites WHERE name NOT LIKE '%oo%';
    --_表示 1 个字符
    --SELECT * FROM Websites WHERE name LIKE '淘_';
    --SELECT * FROM Websites WHERE name LIKE '_宝';
    --SELECT * FROM Websites WHERE name LIKE '__';


delete from VOXER_USERINFO;
delete from VOXER_BUDDIES;
delete from USERA;
delete from TB_VOXER_USERINFO;
delete from TB_VOXER_BUDDIES;
delete from CITY;

delete from TB_USER;
delete from TB_TRIP;
delete from TB_TARGET;
delete from TB_SHOP;
delete from TB_READ;
delete from TB_FRIEND;
delete from TB_EMAIL;
delete from TB_BLOG;
delete from TB_ADDRESS;

delete from TB_PROTOCOL_CONFIG_BAK;
delete from TB_S_USER;

DROP table TB_VOXER_USERINFO_copy;
DROP table TB_VOXER_BUDDIES_copy;
DROP table AThis_is_release_system_128;

DROP table DEV_TB_USER;
DROP table DEV_TB_TRIP;
DROP table DEV_TB_SHOP;
DROP table DEV_TB_READ;
DROP table DEV_TB_FRIEND;
DROP table DEV_TB_EMAIL;
DROP table DEV_TB_BLOG;
DROP table DEV_TB_ADDRESS;
DROP table DEV_TB_USER;
DROP table DEV_TB_TRIP;
DROP table DEV_TB_TARGET;
DROP table DEV_TB_SHOP;
DROP table DEV_TB_READ;
DROP table DEV_TB_PROTOCOL_CONFIG_BAK;
DROP table DEV_TB_FRIEND;
DROP table DEV_TB_EMAIL;
DROP table DEV_TB_BLOG;
DROP table DEV_TB_ADDRESS;
DROP table DEV_TB_S_USER;

ALTER TABLE AThis_is_release_system_128 RENAME TO AThis_is_xj_102;

DROP table VOXER_USERINFO;
DROP table VOXER_BUDDIES;
DROP table USERA;
DROP table TB_VOXER_USERINFO;
DROP table TB_VOXER_BUDDIES;
DROP table TB_USER;
DROP table TB_TRIP;
DROP table TB_TARGET;
DROP table TB_SHOP;
DROP table TB_READ;
DROP table TB_FRIEND;
DROP table TB_EMAIL;
DROP table TB_BLOG;
DROP table TB_ADDRESS;
DROP table CITY;
DROP table TB_PROTOCOL_CONFIG_BAK;
DROP table TB_S_USER;
