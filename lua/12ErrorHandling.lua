-- 12ErrorHandling.lua �ļ�


local function add(a,b)
   assert(type(a) == "number", "a is not a number.")
   assert(type(b) == "number", "b is not a number.")
   return a+b
end

-- add(10)
add(10, 20)


if pcall(add, 1) then
    -- û�д���
    print("OK")
else
    -- һЩ����
    print("Not OK")
end
    
--	pcall(function(i) print(i) end, 33, 44)
--	pcall(function(i) print(i) error('error..') end, 33, 44)
	

n = 10
function myfunction ()
   n = n/nil
end

function myerrorhandler( err )
   print( "myerrorhandler ERROR:", err )
end

status = xpcall( myfunction, myerrorhandler )
print( status)

