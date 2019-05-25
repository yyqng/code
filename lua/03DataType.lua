#!/usr/local/bin/lua
    s = "string： 换行\
         转义\\"
    print(    "s                                   ->\n", s)
    print(    "type(type)                          -> " .. type(type))                 
    print(    "type(nil)                           -> " .. type(nil))                  
    print(    "type(X)                             -> " .. type(X))                    
    print(  'type(\"Hello world\")                 -> ' .. type("Hello world"))        
    print(  '\"5\" + 2                             = ' .. ( "5" + 2))                   
    print(  'string.upper(\"Hello world\")         -> ', string.upper("Hello world"))  
    print(    'string.lower("HELLO WORLD")         -> ', string.lower("HELLO WORLD"))  
    print(    'string.gsub( "aaaa", "a", "z", 3)   -> ', string.gsub( "aaaa", "a", "z", 3))
    print(    'string.gsub( "aaaa", "a", "z")      -> ', string.gsub( "aaaa", "a", "z"))   
    print(    'string.find( "Hello Lua user", "Lua", "1")      -> ', string.find( "Hello Lua user", "Lua", "1")) 
    print(    'string.reverse("Helllo")            -> ', string.reverse( "Hello" ) ) 
    print(    'string.char(97,98,99,100)           -> ', string.char(97,98,99,100) ) 
    print(    'string.byte("ABCD")                 -> ', string.byte("ABCD") ) 
    print(    'string.rep("ABCD")                  -> ', string.rep("ABCD", 3) ) 
    --print(    'string.gmatch("from=world, to=Lua", "(%w+)=(%w+)"))    -> ', string.gmatch("from=world, to=Lua", "(%w+)=(%w+)"))  
	--string.gmatch(str, pattern)  -->string.match(str, pattern, init)
    print(    'type((10.4*3))                      -> ', type((10.4*3)) ) --> number，默认的number类型为double（可在luaconf.h里修改）
    print(    'type( print )                       -> ', type( print ) )
    print(    'type( true )                        -> ', type( true ) )
    print(    'type( type(X) )                     -> ', type( type(X) ) )
	print(    '#"www"                              -> ', #"www") 
	
	local tbl2 = {"apple", "pear", "orange", "grape"}   --> 创建一个 table，索引以1开始
	tbl2["key"] = "value"                               --> 创建一个 table是必要的，否则无法使用
	tbl2[10] = 22                                       --> table 长度会自动增长，没初始化的为nil
    print(    'tbl2[1]                             -> ', tbl2[1] )
    print(    'tbl2[10]                            -> ', tbl2[10] )
    print(    'tbl2["key"]                         -> ', tbl2["key"] )
    print(    'tbl2.key                            -> ', tbl2.key )
	
    -- function_test.lua 脚本文件
	function factorial1(n)
		if n == 0 then
			return 1
		else
			return n * factorial1(n - 1)
		end
	end
	factorial2 = factorial1
	print(    'factorial1(5)                       -> ',factorial1(5) )
	print(    'factorial2(5)                       -> ',factorial2(5) )


    function testFun(tab,fun)
        for k ,v in pairs(tab) do
            print("fun(k,v)                            -> ", fun(k,v));
        end
    end
    tab={key1="val1",key2="val2"};
    testFun(tab,
    function(key,val)--匿名函数
        return key.."="..val;
    end
    );
