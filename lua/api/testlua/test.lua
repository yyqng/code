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


--test_lua_func()
--test_lua_func()
--test_lua_func()
co = coroutine.wrap(function() print(pcall(coroutine.yield)) end)
co()
--~/hub/lua/lua-5.1.4/src/lua testlua/test.lua ---> false attempt to yield across metamethod/C-call boundary
--~/hub/lua/lua-5.3.6/src/lua testlua/test.lua ---> OK


