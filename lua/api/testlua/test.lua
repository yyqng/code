--print( #{ [1] = 1, [2] = 2 } )
--print( #{ [1] = 1, [2] = 2, [5] = 5 } )
--print( #{ [1] = 1, [2] = 2, 1, 2, 3 } )

count = 5
function GlobalFunction()
    count = count + 1
    print("GlobalFunction count = "..count)
end

test = {}
function test.test_lua_func(a, b)
    count = count + 1
    print("test.test_lua_func count = "..count)
end

function myprint()
    print("hello myprint")
    return 233;
end

function closure_test()
    test.test_lua_func()
    test.test_lua_func()
    test.test_lua_func()
end

function gloabal_test()
    cl1 = GlobalFunction()
    --cl1()
    cl2 = GlobalFunction()
end


--closure_test()
--gloabal_test()
--co = coroutine.wrap(function() print(pcall(coroutine.yield)) end)
--co()
--os.execute("/home/yoyu/hub/lua/lua-5.3.6/src/lua /home/yoyu/hub/testcode/lua/api/testlua/env.lua") ---> OK


