--Name of this file can't be mylib.lua because of mylib.so
--Usage:
--
--1. Set env:
--package.cpath = package.path..";/home/yoyu/hub/testcode/lua/capi/?.so"
--
--or in .bashrc:
--export LUA_CPATH="$TESTCODE_PATH/lua/capi/?.so;$TESTCODE_PATH/lua/?.so"
--
--2. execute this script: lua callclib.lua
local lib = require "lib"

l_mapTest = function()
    mytable = {}
    mytable[1]= "initial element 1"
    mytable[2]= "initial element 2"
    myprint = function(param)
       print("myprint:",param)
       return 1111
    end
    lib.lmap(mytable, myprint)
    print("l_mapTest:", mytable[1], mytable[2])
end

l_ctableTest = function(n)
    local ctable = lib.lnewarray(n)
    for i=1,n do
        lib.lsetarray(ctable, i, i + 100)
    end
    for i=1,n do
        print("ctable["..i.."] = ", lib.lgetarray(ctable, i))
    end
    print("Size of ctable:", lib.lgetsize(ctable))
end

l_ctableBadTest = function(n)
    for i=1,n do
        lib.lsetarray(io.stdin, i, i + 100)
    end
    for i=1,n do
        print("io.stdin["..i.."] = ", lib.lgetarray(io.stdin, i))
    end
    print("Size of io.stdin:", lib.lgetsize(io.stdin))
end

l_stdinTest = function()
    io.stdin="in"
    print("io.stdin = ", io.stdin)
end

l_ctableTestV2 = function(n)
    mt={__name="LuaBook.array"}
    --mt={__name="Luook.array"}
    ctable={}
    setmetatable(ctable,mt)
    print(type(ctable),ctable)

--    local ctable = lib.lnewarrayV2(n)
    for i=1,n do
        lib.lsetarrayV2(ctable, i, i + 100)
    end
    for i=1,n do
        print("ctable["..i.."] = ", lib.lgetarrayV2(ctable, i))
    end
    print("Size of ctable:", lib.lgetsizeV2(ctable))
end

l_ctableBadTestV2 = function(n)
    for i=1,n do
        lib.lsetarrayV2(io.stdin, i, i + 100)
    end
    for i=1,n do
        print("io.stdin["..i.."] = ", lib.lgetarrayV2(io.stdin, i))
    end
    print("Size of io.stdin:", lib.lgetsizeV2(io.stdin))
end

metaTest = function()
    a = array.new(1000)
    print(a:size())
    --> 1000
    a:set(10, 3.4)
    print(a:get(10))
    --> 3.4
end

--print(type(lib))
--print(lib.lsum(23,17))
--print(lib.lsin(3.14159265354))
--print(mysin(3.14159265354))
--print(lib.ldir("."))
l_mapTest() 
--print(lib.lsplit("hi,,there", ","))
--print(lib.lctest())
--l_stdinTest()
--l_ctableTest(2)
--l_ctableBadTest(2)
--l_ctableTestV2(2)     --------wrong
--l_ctableBadTestV2(2)
--metaTest()
