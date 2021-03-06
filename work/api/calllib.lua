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
local lib = require "libtest"

l_structTest = function()
    pStudent = lib.lnew_Student()
    lib.lStudent_print(pStudent)
    lib.lStudent_print(pStudent)
    lib.lNumArray_print(pStudent) -- May cause core dump
    
    pNumArray = lib.lnew_NumArray()
    lib.lNumArray_print(pNumArray)
    lib.lNumArray_print(pNumArray)

end

l_mapTest = function()
    mytable = {}
    mytable[1]= "ele1"
    mytable[2]= "ele2"
    myprint = function(param)
       print("myprint:",param)
       return 2222
    end
    print("mytable = {", mytable[1], mytable[2], "}")
    lib.lmap(mytable, myprint)
end

l_ctableTestV1 = function(n)
    local ctable = lib.lnewarray(n)
    for i=1,n do
        lib.lsetarray(ctable, i, i + 100)
    end
    for i=1,n do
        print("ctable["..i.."] = "..lib.lgetarray(ctable, i))
    end
    print("Size of ctable:", lib.lgetsize(ctable))
end

l_ctableTestV2 = function(n)
    local ctable = lib.lnewarrayV2(n)
    for i=1,n do
        lib.lsetarrayV2(ctable, i, i + 100)
    end
    for i=1,n do
        print("ctable["..i.."] = "..lib.lgetarrayV2(ctable, i))
    end
    print("Size of ctable:", lib.lgetsizeV2(ctable))
end

l_ctableBadTestV1 = function(n)
    for i=1,n do
        lib.lsetarray(io.stdin, i, i + 100)
    end
    for i=1,n do
        print("io.stdin["..i.."] = "..lib.lgetarray(io.stdin, i))
    end
    print("Size of io.stdin:", lib.lgetsize(io.stdin))
end

l_ctableBadTestV2 = function(n)
    for i=1,n do
        lib.lsetarrayV2(io.stdin, i, i + 100)
    end
    for i=1,n do
        print("io.stdin["..i.."] = "..lib.lgetarray(io.stdin, i))
    end
    print("Size of io.stdin:", lib.lgetsize(io.stdin))
end

l_ctableTest = function(n)
    print("l_ctableTestV1:")
    l_ctableTestV1(n)
    print("l_ctableTestV2:")
    l_ctableTestV2(n)
    print("l_ctableBadTestV2:")
    l_ctableBadTestV2(n)
    print("l_ctableBadTestV1:")
    l_ctableBadTestV1(n)
end

l_stdinTest = function()
    io.stdin="in"
    print("io.stdin = ", io.stdin)
end

l_classTest = function()
    --local metaarray = getmetatable(array.new(1))
    --metaarray.__index = metaarray
    --metaarray.set = array.set
    --metaarray.size = array.size

     a = lib.new(1000)
    --a[10] = 3.4
    print(a)
    print(lib.size(a)) --> 1000
    for i=1,1000 do
        lib.set(a, i, 1/i)
    end
--    a:set(10, 3.4)
    print(lib.get(a, 10)) --> 1/10
    lib.set(io.stdin, 1, 0)
end

function Luaf(x, y)
    return (x^2 )/(1 - y)
--    return (x^2 * math.sin(y))/(1 - x)
end

--print(type(lib))
--print(lib.lsum(23,17))
--print(lib.lsin(3.14159265354))
--print(mysin(3.14159265354))
--print(lib.ldir("."))
--l_mapTest() 
--l_structTest()

--print(lib.lsplit("hi,,there", ","))
--lib.lregref()
--l_ctableTest(2)
--l_stdinTest()
l_classTest()   ------wrong
