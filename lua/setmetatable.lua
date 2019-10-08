-- 定义一个数字
local aNumber = 100

-- 定义一个普通的元表
local tab1 = { 
    x = 13,
    y = 36,
}

-- 不能设置数字的元表
-- setmetatable(aNumber, tab1) -- 'setmetatable' (table expected, got number)

-- 设置元表后打印变量
local m1 = { z = 36}
print(type(tab1))
setmetatable(tab1, {__index = m1})
print("\ntab1.z =", tab1.z)

-- 设置元表为空后打印变量
setmetatable(tab1, nil)
print("\ntab1.z =", tab1.z)

-- 设置为有字段"__metatable"的元表
setmetatable(tab1, {__index = m1, __metatable = 'I have metatable'})
print(type(tab1))
print("\ntab1.z =", tab1.z)

-- 再次设置元表会报错，因为原来的元表有'__metatable',起到保护作用
--setmetatable(tab1, {__index = m1})
