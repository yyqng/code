--Name of this file can't be lualib.lua because of lualib.so
local lib = require "mylib"

l_mapTest = function()
    mytable = {}
    mytable[1]= "element 1"
    mytable[2]= "element 2"
    myprint = function(param)
       print("myprint:",param)
    end
    print(lib.l_map(mytable, myprint))
end

l_ctableTest = function(n)
    local ctable = lib.l_newarray(n)
    for i=1,n do
        lib.l_setarray(ctable, i, i + 100)
    end
    for i=1,n do
        print("ctable["..i.."] = ", lib.l_getarray(ctable, i))
    end
    print("Size of ctable:", lib.l_getsize(ctable))
end

l_ctableBadTest = function(n)
    for i=1,n do
        lib.l_setarray(io.stdin, i, i + 100)
    end
    for i=1,n do
        print("io.stdin["..i.."] = ", lib.l_getarray(io.stdin, i))
    end
    print("Size of io.stdin:", lib.l_getsize(io.stdin))
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

--    local ctable = lib.l_newarrayV2(n)
    for i=1,n do
        lib.l_setarrayV2(ctable, i, i + 100)
    end
    for i=1,n do
        print("ctable["..i.."] = ", lib.l_getarrayV2(ctable, i))
    end
    print("Size of ctable:", lib.l_getsizeV2(ctable))
end

l_ctableBadTestV2 = function(n)
    for i=1,n do
        lib.l_setarrayV2(io.stdin, i, i + 100)
    end
    for i=1,n do
        print("io.stdin["..i.."] = ", lib.l_getarrayV2(io.stdin, i))
    end
    print("Size of io.stdin:", lib.l_getsizeV2(io.stdin))
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
--print(lib.l_sum(23,17))
--print(lib.l_sin(3.14159265354))
--print(mysin(3.14159265354))
--print(lib.l_dir("."))
--l_mapTest() 
--print(lib.l_split("hi,,there", ","))
--print(lib.l_ctest())
--l_stdinTest()
--l_ctableTest(2)
--l_ctableBadTest(2)
--l_ctableTestV2(2)     --------wrong
--l_ctableBadTestV2(2)
metaTest()
