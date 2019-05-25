--start /sql/regexp.sql
--表
  --显示格式设置
    set linesize 200;
    set pagesize 300;
    --set wrap off
    col first_name format a20;
    col last_name format a20;
    col email format a32;
    col zip format a6;
/*  --删除表：
    DROP table person;
  --创建表：
    create table person
    (
        first_name varchar2(20),
        last_name varchar2(20),
        email varchar2(64),
        zip varchar(6)
     );
    insert into person values('Steven','Chen','steven@hp.com','123456');
    insert into person values('James','Li','jamesli@sum.com'||chr(10)||'lijames@oracle.com','1b3d5f');
    insert into person values('Tina','Zhang','chillaxzx@163.com','2456hd');
    insert into person values('Tom','Feng','Tomfeng@126.com','a654e5');
    insert into person values('Jonson','zhao','Jonson@google.com','edjksk');
    insert into person values('Vines','Wu','Vines@162.com','2djks4');
    commit;
*/    
    select * from person;
/*==============================================================
    regexp_like搜索值
    pattern 正则表达式元字符构成的匹配模式,长度限制在512字节内
    match_option是一个文本串，允许用户设置该函数的匹配行为。可以使用的选项有：
    c 匹配时，大小写敏感，默认值
    i 匹配时，大小写不敏感
    n 允许使用原点（.）匹配任何新增字符
    m 允许将源字符作为多个字符串对待 
================================================================*/
    --zip字段以数字开头
      --select * from person where regexp_like(zip,'^[[:digit:]]');
    --zip字段包含非数字
      --select * from person where regexp_like(zip,'[^[:digit:]]');
    --zip字段包含数字
      --select * from person where regexp_like(zip,'[[:digit:]]');
    --zip字段以数字结尾 
      --select * from person where regexp_like(zip,'[[:digit:]]$'); 
    --first_name字段以S开始，N结束的，不区分大小写
      --select * from person where regexp_like(first_name,'^t.*m$','i');
    --email字段,注意区别
      --select * from person where regexp_like(email, '^james.*com$');
      --select * from person where regexp_like(email, '^james.*com$', 'n');
      --select * from person where regexp_like(email, '^james.*com$', 'm');
      --select * from person where regexp_like(email, '^li.*com$');
      --select * from person where regexp_like(email, '^li.*com$', 'm');
      --select * from person where regexp_like(email, '^li.*com$', 'n');

/*==============================================================
	regexp_instr(x,pattern[,start[,occurrence[,return_option[,match_option]]]])
	参数说明：
	x 待匹配的字符串
	pattern 正则表达式元字符构成的匹配模式
	start 开始匹配位置，如果不指定默认为1
	occurrence 匹配的次数，如果不指定，默认为1
	return_option 指定返回的类型，若该参数为0，则返回值为匹配位置的第一个字符，若为非0，则返回匹配值的最后一个位置+1
	match_option 意义同regexp_like的一样
================================================================*/
    --查找zip中第一个非数字字符的位置
      select a.*, regexp_instr(zip,'[^[:digit:]]') as position from person a ; 
    --查找zip中，从第2位开始第2次匹配的最后一个字符位置+1
      --select a.*, regexp_instr(zip,'[^[:digit:]]',2,2,1) as position from person a ; 
    --查找zip中，从第1位开始第2次匹配的最后一个字符位置+1
      --select a.*, regexp_instr(zip,'[^[:digit:]]',1,2,1) as position from person a ; 
    --查找zip中，从第1位开始第1次匹配的最后一个字符位置+1
      --select a.*, regexp_instr(zip,'[^[:digit:]]',1,1,1) as position from person a ;
    --返回21，从第1个字符开始，找出以o开头 以e结尾 中间跟4个任意字母的单词 第1次匹配的第1个字符位置，这里是oracle中o的位置
      --select regexp_instr('i love http://www.52oracle.com','o[[:alpha:]]{4}e',1,1) as r from dual
    --返回24，从第1个字符开始，找出以o开头 后跟2个任意字母的单词 第2次匹配的第1个字符位置，这里是ora中o的位置
      --select regexp_instr('i love http://www.52oracle.com','o[[:alpha:]]{2}',1,2,1) as r from dual
    --返回17，从第1个字符开始，找出l开头的 后跟4个任意字母的单词 第1次匹配的第1个字符的位置，这里是light中l的位置 
      --SELECT REGEXP_INSTR('But, soft! What light through yonder window breaks？','l[[:alpha:]]{4}',1,1,0) FROM DUAL;
    --返回22，从第1个字符开始，找出l开头的 后跟4个任意字母的单词 第1次匹配的最后一个字符的位置+1，这里是light中t的位置+1
      --SELECT REGEXP_INSTR('But, soft! What light through yonder window breaks？','l[[:alpha:]]{4}',1,1,1) FROM DUAL; 

/*==============================================================
	regexp_substr(x,pattern[,start[,occurrence[match_option]]])
	参数说明：
	x 待匹配的字符串
	pattern 正则表达式元字符构成的匹配模式
	start 开始匹配位置，如果不指定默认为1
	occurrence 匹配的次数，如果不指定，默认为1
	match_option 意义同regexp_like的一样
================================================================*/
    --查找第一个非0字符值
      --select a.* , regexp_substr(zip, '[^[:digit:]]') as zip from person a ;
    --从第三个字符开始，查找第2个非0字符值
      --select a.* , regexp_substr(zip, '[^[:digit:]]', 3, 2) as zip from person a;
    --查找以o开始的，后面接4个字母的字符串
      --select regexp_substr('I love oracle very much','o[[:alpha:]]{4}') from dual;
    --查找以o开始的，后面至少接4个字母的字符串
      --select regexp_substr('I love oracle very much','o[[:alpha:]]{4,}') from dual;
    --查找以o开始，以e结尾的，后面接1个或多个除null之外字符的字符串
      --select regexp_substr('i love oracle very much','o.{1}e',1,1) from dual; 
      --select regexp_substr('i love oracle very much','o.*e',5,1) from dual;

/*==============================================================
	regexp_replace(x,pattern[,replace_string[,start[,occurrence[match_option]]]])
	参数说明：
	x 待匹配的字符串
	pattern 正则表达式元字符构成的匹配模式
	replace_string 替换字符串 
	start 开始匹配位置，如果不指定默认为1
	occurrence 匹配的次数，如果不指定，默认为1
	match_option 意义同regexp_like的一样
================================================================*/
    --把zip中所有非数字字符替换为0
      --update person set zip=regexp_replace(zip, '[^[:digit:]]', '0')where regexp_like(zip, '[^[:digit:]]');
      --select zip from person;
    --后向引用：
    --后向引用是 一个很有用的特性。它能够把子表达式的匹配部分保存在临时缓冲区中，供以后重用 。缓冲区从左至右进行编号，
    --并利用 \digit 符号进行访问。子表达式用一组圆括号来显示。利用后向引用可以实现较复杂的替换功能。
      --select regexp_replace('Steven Chen', '(.*) (.*)', '\2, \1') as reversed_name from dual;
    --修改person表，增加检查zip的第一个字符是否为数字的检查索引
      --alter table person add constraint constraint_zip check (regexp_like(zip, '^[[:digit:]]+$'));
    --根据姓的第一个大写字母创建索引
      --create index person_idx on person(regexp_substr(last_name, '^[[:upper:]]'));
      --select *
      --from person a
      --where regexp_substr(last_name, '^[[:upper:]]')='W'
    --用‘XXX’代替‘light’ , 返回But, soft! What XXX through yonder window breaks？ 
      --SELECT REGEXP_REPLACE('But, soft! What light through yonder window breaks？','l[[:alpha:]]{4}','XXX') FROM DUAL;
    --用’XXX‘代替以e开始,长度为3的字符串，从第5个字符开始，匹配2次
      --select regexp_replace('hello everybody,may I have your attention please?','e[[:alpha:]]{2}','XXX',5,2) from dual;
    --大小写敏感
      --select regexp_replace('hello Everybody,may I have your attention please?','e[[:alpha:]]{2}','XXX',5,1) from dual;
    --忽略大小写
      --select regexp_replace('hello Everybody,may I have your attention please?','e[[:alpha:]]{2}','XXX',5,2,'i') from dual;
    
    
