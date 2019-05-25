--用户
  --创建用户：
   --create user zdzc identified by ********;
   --CREATE USER zdzc IDENTIFIED BY ******** DEFAULT TABLESPACE PAUL;
  --用户赋予权限：
   --grant create session to zdzc;
   --grant connect,resource,dba to zdzc;--连接、创建数据库实体（表，过程等）、创建数据库结构
   --grant all privileges to zdzc;
   alter USER zdzc IDENTIFIED BY ******** DEFAULT TABLESPACE PAUL;
   SELECT * FROM all_users WHERE all_users.username = 'SCOTT';
重启
   shutdown immediate;
   startup;


