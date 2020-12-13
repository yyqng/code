print( #{ [1] = 1, [2] = 2 } )
print( #{ [1] = 1, [2] = 2, [5] = 5 } )
print( #{ [1] = 1, [2] = 2, 1, 2, 3 } )

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
