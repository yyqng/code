#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
import sys

#可变参数
def cacl1(numbers):
    sum = 0
    for n in numbers:
        sum = sum + n
    return sum
#mylist=[1,2,3]
#print (cacl1([1]))
#print (cacl1([1,2]))
#print (cacl1(mylist))

#可变参数 : *numbers
def cacl2(*numbers):
    sum = 0
    for n in numbers:
        sum = sum + n
    return sum
#mylist=[1,2,3]
#print (cacl2(1))
#print (cacl2(1,2))
#print (cacl2(1,2,3))
#print (cacl2(*mylist))

#默认参数
def enrool1(name, gender, age=6, city="guangdong"):
    print(name, gender, age, city)
#enrool1("Jim", "male")
#enrool1("Jim", "male", 7)
#enrool1("Jim", "male", 7, "Shandong")
#enrool1("Jim", "male", city="Shandong")

#关键字参数：**kw
def enrool2(name, gender, **kw):
    if 'age' in kw:
        print("age exsit")
        pass
    if 'city' in kw:
        print("city exsit")
        pass
    print('name:', name, ', gender:', gender, ', other:', kw)
other={"age":7, "city": "Shandong"}
#other={"age:7", "city:Shandong"} ####wrong
#enrool2("Jim", "male", **other)

#命名关键字参数:city job
def enrool3(name, gender, *, city, job):
    print('name:', name, ', gender:', gender, ', job:', job, ', city:', city)
#other={"age":7, "city": "Shandong"} ####wrong
#other={"city": "Shandong"} ####wrong
#other={"job":"monkey", "city": "Shandong"}
#enrool3("Jim", "male", **other)
#enrool3("Jim", "male", job='Enginner', city='Beijing')

#若干种参数
def enrool4(a, b, c=0, *, d, **kw):
    print('a:', a, ', b:', b, ', c:', c, ', d:', d, ", other:" , kw)
#para={"A":"B"}
#other={"age":7, "city": "Shandong"}
#enrool4("A", "B", "C", d="D", **other)
#enrool4("A", "B", d="D", **para)

#sys.setrecursionlimit(1000000) #例如这里设置为一百万
#print(sys.getrecursionlimit())
#递归
def fact1(n):
    if n==1:
        return 1
    return n*fact(n-1)
#print(fact1(998))

#尾递归:若有尾递归优化，栈不会增长:python没有优化
def fact2(n):
    return fact_iter(n, 1)
def fact_iter(n, product):
    if n==1:
        return product
    return fact_iter(n-1, n*product)
print(fact2(1000))

def move(x, y, step, angle=0):
    nx = x + step * math.cos(angle)
    ny = y - step * math.sin(angle)
    return nx, ny
#x, y = move(100, 100, 60, math.pi / 6)
#print(x, y)

# TypeError: bad operand type:
# my_abs('123')


def addEnd1(L=[]):
    L.append("END")
    return L
#print(addEnd1(["hi",1,2,3]))
#print(addEnd1())
#print(addEnd1())

def addEnd2(L=None):
    if L is None:
        L = []
    L.append("END")
    return L
#print(addEnd2(["he",'x','y','z']))
#print(addEnd2())
#print(addEnd2())

def emptyFun():
    pass
emptyFun()

def my_abs(x):
    if not isinstance(x, (int, float)):
        raise TypeError('bad operand type')
    if x >= 0:
        return x
    else:
        return -x
#n = my_abs(-20)
#print(n)
#print(my_abs("A"))
#a = abs
#n = a(-20)
#print(n)
