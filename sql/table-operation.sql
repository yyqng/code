--start /sql/table-operation.sql
--表
  --显示格式设置
    set linesize 200;
    SET WRAP OFF 
    set pagesize 300;
    col id format 9999;
    col name format a20;
    col url format a40;
    col alexa format a10;
    col country format a10;

    set linesize 200;
    set pagesize 300;
    set wrap off
    col aid format 99999999;
    col site_id format 99999999;
    col icount format 99999999;
    col ddate format a40;
  --查看表：
    --select table_name from user_tables;                     --当前用户的表 
    --select table_name from all_tables;                      --所有用户的表
    --select table_name from dba_tables;                      --包括系统表
    --select table_name from dba_tables where owner='用户名'   --根据用户名查看表
  --获取表字段：
    --select * from user_tab_columns where Table_Name='用户表';
    --select * from all_tab_columns where Table_Name='用户表';
    --select * from dba_tab_columns where Table_Name='用户表';
  --获取表注释：
    --select * from user_tab_comments
    --user_tab_comments：table_name,table_type,comments
    --相应的还有dba_tab_comments，all_tab_comments，这两个比user_tab_comments多了ower列。 
  --获取字段注释：
    --select * from user_col_comments user_col_comments：table_name,column_name,comments
  --更新记录
    --UPDATE Websites SET alexa='5000', country='USA' WHERE name='菜鸟教程';
  --删除记录
    --DELETE FROM Websites WHERE name='stackoverflow';
    --删除表test里的内容，但不删除表的结构，不释放空间，
    --DELETE * FROM Websites;
    --删除表test里的内容，但不删除表的结构，释放空间，数据不可以回滚恢复
    --TRUNCATE Websites;
  --选取数据，存储在结果表中，称为结果集
    --SELECT * FROM Websites;
    --SELECT name,country FROM Websites;
    --SELECT DISTINCT country FROM Websites;
    --SELECT * FROM Websites WHERE alexa>=15 and (name='Google' OR country='CN');
    --SELECT * FROM Websites ORDER BY id;
    --SELECT * FROM Websites ORDER BY id DESC;
    --SELECT * FROM Websites ORDER BY country,alexa;
    --SELECT * FROM Websites WHERE name IN ('Google','菜鸟教程');
    --SELECT * FROM Websites WHERE name='Google' or name='菜鸟教程';
    --SELECT * FROM Websites WHERE alexa BETWEEN 1 AND 20;
    --SELECT * FROM Websites WHERE alexa not BETWEEN 1 AND 20;
    --SELECT * FROM Websites WHERE (alexa BETWEEN 1 AND 20) AND NOT country IN ('USA', 'IND');
    --SELECT * FROM Websites WHERE name BETWEEN 'A' AND 'H';
    --SELECT * FROM Websites WHERE name not BETWEEN 'A' AND 'H';

--start /sql/table.sql
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
    --SELECT * FROM Websites WHERE name LIKE 'G_o_le';
    --select * from Websites where regexp_like(name,'^[GFs]');
    --select * from Websites where regexp_like(name,'^[A-H]');
    --select * from Websites where regexp_like(name,'^[^A-H]');
    
--start /sql/table-operation.sql
 
    --SELECT * FROM access_log t WHERE t.ddate >= to_date('2016-05-10','yyyy-MM-dd') and t.ddate <= to_date('2016-05-14','yyyy-MM-dd'); 
    --SELECT * FROM access_log t WHERE t.ddate between to_date('2016-05-10','yyyy-MM-dd') and to_date('2016-05-14','yyyy-MM-dd'); 
    --别名
    --col n format a20;
    --col c format a10;
    --SELECT name AS n, country AS c FROM Websites;
    --SELECT name, concat(url, ', ', alexa, ', ', country) AS site_info FROM Websites;--oracle不支持：
    select * from access_log;
    select * from Websites;
    --SELECT w.name, w.url, a.icount, a.ddate FROM Websites w, access_log a WHERE a.site_id=w.id and (w.name='菜鸟教程');

    --JOIN
    --SELECT w.id, w.name, a.icount, a.ddate FROM Websites w INNER JOIN access_log a ON  w.id=a.site_id;
    --SELECT w.id, w.name, a.icount, a.ddate FROM Websites w LEFT JOIN access_log a ON  w.id=a.icount;
    --SELECT w.id, w.name, a.icount, a.ddate FROM Websites w RIGHT JOIN access_log a ON  w.id=a.icount;
    --SELECT w.id, w.name, a.icount, a.ddate FROM Websites w FULL JOIN access_log a ON  w.id=a.icount;
    
    
