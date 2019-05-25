#!/usr/local/bin/lua

local function add(x, y)  --局部函数
    return x + y
end
print(" add(5, 6) = ", add(5, 6))

myprint = function( param )
   print("这是打印函数 -   ##",param,"##")
end

function add(num1,num2,funcPrint)
   result = num1 + num2
   funcPrint(result)
end

myprint(10)
add(2,5,myprint)


s, e = string.find("www.runoob.com", "runoob") 
print(s, e)

function maximum (a)
    local mi = 1             -- 最大值索引
    local m = a[mi]          -- 最大值
    for i,val in ipairs(a) do
       if val > m then
           mi = i
           m = val
       end
    end
    return m, mi
end

print(maximum({8,10,23,12,5}))


function add(...)  
local s = 0  
  for i, v in ipairs{...} do   --> {...} 表示一个由所有变长参数构成的数组  
    s = s + v  
  end  
  return s  
end  
print(add(3,4,5,6,7))  --->25


function average(...)
   result = 0
   local arg={...}    --> arg 为一个表，局部变量
   for i,v in ipairs(arg) do
      result = result + v
   end
   print("总共传入 " .. #arg .. " 个数")
   return result/#arg
end

print("平均值为",average(10,5,3,4,5,6))


function fwrite(fmt, ...)  ---> 固定的参数fmt
    return io.write(string.format(fmt, ...))     
end

fwrite("runoob\n")       --->fmt = "runoob", 没有变长参数。  
fwrite("%d   %d\n", 1, 2)   --->fmt = "%d%d", 变长参数为 1 和 2


function foo(...)  
    for i = 1, select('#', ...) do  -->获取参数总数
        local arg = select(i, ...); -->读取参数
        print("arg", arg);  
    end  
end  

foo(1, 2, 3, 4);  



i = 1
if ( i ~= 0)
then
    print (" i ~= 0")
end
