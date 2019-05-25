 
-- __index 元方法：
mytable = { x = 3, y = 4 } 
-- metatable1  设置了元表，元方法 __index 为 mytable
metatable1  = setmetatable({}, { __index = mytable }) 

--在 metatable1  表中查找 x ，在表中未找到; 在元表中使用元方法 __index (表mytable) 查找，找到 3
--在 metatable1  表中查找 z ，在表中未找到; 在元表中使用元方法 __index (表mytable) 查找，未找到
print (metatable1 .x, metatable1 .z)
 


-- metatable2  表赋值为 {key1 = "value1"}
-- metatable2  设置了元表，元方法 __index 为 function 。
metatable2 = setmetatable({key1 = "value1"}, {
  __index = function( metatable2, key )
    if key == "key2" then
      return "metatablevalue"
    else
      return nil
    end
  end
})

--在 metatable2 表中查找 key1， 在表中查找， 找到 "value1"
--在 metatable2 表中查找 key2， 在表中查找， 未找到; 在元表中使用元方法 __index (可以是方法或表) 查找， 找到 "metatablevalue"
--在 metatable2 表中查找 key3， 在表中查找， 未找到; 在元表中使用元方法 __index (可以是方法或表) 查找， 未找到
print( metatable2.key1, metatable2.key2, metatable2.key3 )

metatable2.key1    = "new value1"
metatable2.newkey1 = "new value2"
metatable2.newkey2 = "new value3"
print( "After chage metatable2, metatable2: ", metatable2.key1, metatable2.newkey1, metatable2.newkey2)
print( "After chage metatable2, mytable: ",       mytable.key1,    mytable.newkey1,    mytable.newkey2)



-- __newindex 元方法：
-- __newindex 元方法用来对表更新，__index则用来对表访问 。
-- 当你给表的一个缺少的索引赋值，解释器就会查找__newindex 元方法：如果存在则调用这个函数而不进行赋值操作。
-- 以下实例演示了 __newindex 元方法的应用：

mytable = {}
metatable2 = setmetatable({key1 = "value1"}, { __newindex = mytable })

metatable2.key1    = "new value1"
metatable2.newkey1 = "new value2"
metatable2.newkey2 = "new value3"
print( "After chage metatable2, metatable2: ", metatable2.key1, metatable2.newkey1, metatable2.newkey2)
print( "After chage metatable2, mytable: ",       mytable.key1,    mytable.newkey1,    mytable.newkey2)



-- 为表添加操作符：
-- 计算表中最大值，table.maxn 在Lua5.2以上版本中已无法使用
-- 自定义计算表中最大键值函数 table_maxn ， 即计算表的元素个数
function table_maxn(t)
    local mn = 0
    for k, v in pairs(t) do
        if mn < k then
            mn = k
        end
    end
    return mn
end

-- 两表相加操作
mytable = setmetatable({ 10, 20, 30 }, {
  __add = function(mytable, newtable)
    for i = 1, table_maxn(newtable) do
      table.insert(mytable, table_maxn(mytable)+1,newtable[i])
    end
    return mytable
  end
})

secondtable = {40,50,60}

mytable = mytable + secondtable
    for k,v in ipairs(mytable) do
print(k,v)
end



-- __call 元方法:
-- __call 元方法在 Lua 调用一个值时调用。以下实例演示了计算表中元素的和：

-- 定义元方法 __call
mytable = setmetatable({10}, {
  __call = function(mytable, newtable)
    sum = 0
    for i = 1, table_maxn(mytable) do
        sum = sum + mytable[i]
    end
    for i = 1, table_maxn(newtable) do
        sum = sum + newtable[i]
    end
    return sum
  end
})
newtable = {10,20,30}
print(mytable(newtable))
-- print(mytable)

-- __tostring 元方法
-- __tostring 元方法用于修改表的输出行为。以下实例我们自定义了表的输出内容：

mytable = setmetatable({ 10, 20, 30 }, {
  __tostring = function(mytable)
    sum = 0
    for k, v in pairs(mytable) do
        sum = sum + v
    end
    return "Sum is : " .. sum
  end
})
print(mytable)