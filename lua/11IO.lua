-- 11IO.lua 文件

--[[
-- 简单模式：
file = io.open("test.txt", "r")   -- 以只读方式打开文件
io.input(file)                    -- 设置默认输入文件为 test.lua
print(io.read())                  -- 输出文件前两行
print(io.read())
io.close(file)                    -- 关闭打开的文件


file = io.open("test.txt", "a")   -- 以附加的方式打开只写文件
io.output(file)                   -- 设置默认输出文件为 test.lua
io.write("Append 1\n")            -- 在文件最后添加两行
io.write("Append 2\n")
io.close(file)                    -- 关闭打开的文件
--]]


-- 完全模式：同时读取多个文件这样的操作，使用完全模式则较为合适
file = io.open("test.txt", "r")   -- 以只读方式打开文件
print(file:read())                -- 输出文件前两行
print(file:read())
file:seek("end",-28)
print(file:read("*a"))
file:close()                      -- 关闭打开的文件

file = io.open("test.txt", "a")   -- 以附加的方式打开只写文件
file:write("Append 3\n")          -- 在文件最后添加两行
file:write("Append 4\n")
file:close()                      -- 关闭打开的文件

