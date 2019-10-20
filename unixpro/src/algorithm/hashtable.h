#include<stdlib.h>
#include<iostream>
using namespace std;
#define HASHSIZE 10
#define NULLKEY -32768
typedef struct hash
{
    int *element;
    int *extraElement;//溢出区表
    int count; // 溢出区的元素个数
}HashTable;
// 由于 通过哈希函数 计算后的地址重复几率很小，所以把重复部分用顺序表来存放，查找时遍历这个公共溢出区的顺序表，效率会更高。
void Init(HashTable *p);
//插入元素
void InsertHash(HashTable *p, int key);
int Search(HashTable *p, int key);
int hashtableTest(void);

