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
--package.path = '/usr/local/share/lua/5.1/?.lua;/home/resty/?.lua;'    --搜索lua模块
package.path = '/home/yoyu/hub/testcode/lua/api/lua_call_c/?.lua;'    --搜索lua模块
package.cpath = '/home/yoyu/hub/testcode/lua/api/?.so;'    --搜索so模块
local lib = require "libtest"
local lualib = require "module"
--lualib.testmodule()

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
    local t = {}
    t[1]= "ele1"
    t[2]= "ele2"
    print("t = {", t[1], t[2], "}")
    f = function(param)
       print("f:",param)
       return 2222
    end
    lib.lmap(t, f)
    print("t = {", t[1], t[2], "}")
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
    asize = 1000
    a = lib.new(asize)
    --a[10] = 3.4
    for i = 1, asize do
        lib.set(a, i, 1/i)
    end
    print(lib.size(a)) --> 1000
--    a:set(10, 3.4)
    print(lib.get(a, 10)) --> 0.1
    --lib.set(io.stdin, 1, 0) --直接崩溃：report error
end

l_classTestV2 = function()
    local metaarray = getmetatable(lib.new(1))
    metaarray.__index = metaarray
    metaarray.set = lib.set
    metaarray.get = lib.get
    metaarray.size = lib.size

    asize = 1000
    a = lib.new(asize)
    print(#a)
    for i = 1, asize do
        a[i] = 1 / i --a.set(a, i, 1/i) -- or a:set(i, 1/i)
    end
    print(a:get(10)) --> 0.1 -- or a.get(a, 10)
    --a.set(io.stdin, 1, 0) --直接崩溃：report error
end

l_classTestV3 = function()
    asize = 1000
    a = lib.new(asize)
    print(#a)
    for i = 1, asize do
        a[i] = 1 / i --a.set(a, i, 1/i) -- or a:set(i, 1/i)
    end
    print(a[10]) -- print(a.size(a)) --> 1000
end

function Luaf(x, y)
    return (x^2 )/(1 - y)
--    return (x^2 * math.sin(y))/(1 - x)
end

function printAll(var, name, table_depth, suf)
    if ("string"~=type(name) and "number"~=type(name)) then name="UNKNOWN" end
    if ("string"~=type(suf)) then suf="  " end
    local ending = ""
    --if ("userdata"==type(var) and not is_model) then ending=DT.get(var) end
    print (suf .. name .. " = ", var, ending)
    if ("table"==type(var)) then
        print(suf .. name .. " = {")
        if ("number"==type(table_depth)) then
            table_depth = table_depth-1
        else
            table_depth = 5
        end
        if ("number"~=type(table_depth) or table_depth>=0) then
            local subsuf = suf.."  "
            for subname,subvar in pairs(var) do
                if ("sgm_pw_model"~=name) then
                    printAll(subvar, subname, table_depth, subsuf)
                else
                    printAll(subvar, subname, table_depth, subsuf)
                end
            end
        end
        print(suf .. "}")
    end
end

function test_reg()
    local key1, key2 = lib.lset_regref()
    print(string.format("%x", key1))
    print(string.format("%x", key2))
    lib.lget_regref(key1, key2)
end

function test_counter()
    local c1 = lib.lnewCounter()
    local c2 = lib.lnewCounter()
    print(c1(), c2(), c1(), c2(), c1(), c2())
end

function tupple_test()
    x = lib.lnew(10, "hi tupple", {}, 3)
    print(x(1))
    print(x(2))
    print(x())
    print(x(256))
end

function dir_test()
    --local files = lib.ldir(".")
    --printAll(files, "files", 2, "hh ")
    for fname in lib.ldir(".") do
        print(fname)
    end
end
--print(type(lib))

--local a, b = lib.lsum(23, 17)
--print(a)
--print(b)

--lib.lpush_test();
--lib.lpop_test();


--print(lib.lsin(3.14159265354))
--print(mysin(3.14159265354))
--l_mapTest() 
--l_structTest()

--local s = "hi,,there"
--print("will split:"..s)
--local split_result = lib.lsplit(s, "i")
--printAll(split_result, "split_result", 2, "hh ")

--local s = {"Hi,", "Lua"}
--print("in lua : b = "..lib.ltconcat(s))
--
--print(lib.lstr_upper("Up"))

--l_ctableTest(2)
--l_stdinTest()
--l_classTest()
--l_classTestV2()
--print("-----------Don't call V2 and V3 at the same time")
--l_classTestV3()

--test_reg()
--lib.lregref_test2()
--test_counter()
--tupple_test()
dir_test()