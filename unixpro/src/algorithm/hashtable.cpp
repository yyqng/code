#include "hashtable.h"
// 由于 通过哈希函数 计算后的地址重复几率很小，所以把重复部分用顺序表来存放，查找时遍历这个公共溢出区的顺序表，效率会更高。
void Init(HashTable *p)
{
    p->element = (int*)malloc(sizeof(int)*HASHSIZE);
    p->extraElement = (int*)malloc(sizeof(int)*HASHSIZE);
    for (int i = 0; i < HASHSIZE; ++i)
    {
        p->element[i] = NULLKEY;
        p->extraElement[i] = NULLKEY; 
    }
    p->count = 0; 
}
// 除留余数法
int HASH(int key)
{
    return key%HASHSIZE;
}
//插入元素
void InsertHash(HashTable *p, int key)
{
    int addr = HASH(key);
    //处理冲突, 使用公共溢出法
    if (p->element[addr] == NULLKEY)
        p->element[addr] = key;
    else //如果元素内已经有值了，就放到溢出部分的表中，且把count加 1
        p->extraElement[p->count++] = key;
}
int Search(HashTable *p, int key)
{
    int addr = HASH(key);
    if (key == p->element[addr])
        return addr;
    else
    {
        for (int i = 0; i < p->count; ++i)
            if (p->extraElement[i] == key)
            {
                cout << "溢出表" << endl;
                return i;
            }
    }
    return -1;
}

int hashtableTest(void)
{
    int a[10] = { 12,45,2,6,78,9,0,1,15 };
    HashTable table;
    Init(&table);
    for (int i = 0; i < 10; i++)
        InsertHash(&table, a[i]);
 
    int res = Search(&table, 2);
    if (res != -1)
        std::cout << "查找成功！地址为： " << res << std::endl;
    else
        std::cout << "查找失败！ " << std::endl;
    return 0;
}
