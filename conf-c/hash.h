//哈希函数库头文件
#ifndef _HASH_H
#define _HASH_H

#include "conf.h"

//插入数据,arg为hash数组，value为值,len为数组长度
int conf_value_insert(CONF_ARG *arg,CONF_VALUE *value,int len);

//动态更新哈希表
int conf_hash_update(CONF *conf);

//置空哈希表
void conf_hash_zero(CONF_ARG *arg,int len);

#endif
