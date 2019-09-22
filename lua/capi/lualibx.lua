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
    ctable = lib.l_newarray(n)
    for i=1,n do
        lib.l_setarray(ctable, n, i + 100)
    end
        print(lib.l_getarray(ctable, 1))
        print(lib.l_getarray(ctable, 2))
    for i=1,n do
        print(lib.l_getarray(ctable, i))
    end
    print("Size of ctable:", lib.l_getsize(ctable))
end

--print(type(lib))
--print(lib.l_sum(23,17))
--print(lib.l_sin(3.14159265354))
--print(mysin(3.14159265354))
--print(lib.l_dir("."))
--l_mapTest() 
--print(lib.l_split("hi,,there", ","))
--print(lib.l_ctest())
l_ctableTest(2)


