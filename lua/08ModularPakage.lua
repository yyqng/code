#!/usr/local/bin/lua

--require("module")           --  加载module.lua,搜索路径为package.path 
--print(module.constant)      --> 定义一个常量，能从外部访问
----module.func1()              --> 定义一个私有函数，不能从外部访问！
--print(module.func2())
--
--local m = require("module") --  别名变量 m
----m.func1()              --> 定义一个私有函数，不能从外部访问！
--print(m.constant)
--m.func2()



local mylib = require("mytestlib")  --对应于mytestlib.c中的包名      
print(mylib.add(1.0,2.0))
print(mylib.sub(20.1,19))

require("mytestlib")                --对应于mytestlib.c中的包名      
print( mytestlib.add( 1.0,  2.0 ) )
print( mytestlib.sub( 20.1, 19  ) )
