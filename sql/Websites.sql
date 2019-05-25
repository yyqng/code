--start /sql/Websites.sql
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
  --删除表：
/*    DROP table Websites;
    CREATE TABLE Websites
    (
	id number,
	name varchar(255),
	url varchar(255),
	alexa varchar(255),
	country varchar(255)
    );

  --删除表中的行
    --DELETE FROM Websites WHERE name='百度' OR country='CN';
    --DELETE FROM Websites ;
  --插入新行：
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (2,'Google','https://www.google.com/','1','USA');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (1,'淘宝','https://www.taobao.com/','13','CN');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (5,'菜鸟教程','http://www.runoob.com/','4689','CN');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (4,'微博','http://weibo.com/','20','CN');
    INSERT INTO Websites (id, name, url, alexa, country)VALUES (3,'Facebook','https://www.facebook.com/','3','USA');
    INSERT INTO Websites (name, url, country) VALUES ('stackoverflow', 'http://stackoverflow.com/', 'IND');
    INSERT INTO Websites VALUES (7,'tencent', 'http://qq.com/','21', 'CN');
*/
    select * from Websites;

    


    
    
