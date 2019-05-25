--start /sql/tablespace.sql
--表空间
  --查看表空间：
    select * from v$tablespace;
  --查看表空间总大小：
    --select tablespace_name,sum(bytes)/1024/1024 from dba_data_files group by tablespace_name;
  --查看每个表空间有哪些数据文件：
    desc dba_data_files;
  --查看详细数据文件：
    --select file_name,tablespace_name from dba_data_files;
  --查看表空间已使用大小及分配情况：
    --select SEGMENT_TYPE,owner,sum(bytes)/1024/1024 from  dba_segments  where tablespace_name='USERS' group by segment_type,owner;
  --查看表空间路径：
    --select  * from dba_data_files;
  --增加表空间大小：
    --alter tablespace YWGOV add datafile '/u01/app/oracle/oradata/XE/YWGOV1.ora' size 10M;
  --创建一个表空间：
    create tablespace paul datafile '/u01/app/oracle/oradata/XE/paul01.dbf' size 1024M;
  --删除表空间
    --drop tablespace paul;
  --删除表空间同时删除对应的数据文件
    --drop tablespace paul including contents and datafiles;
  --设置默认表空间
    alter database default tablespace paul;


