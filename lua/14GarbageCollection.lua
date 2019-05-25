-- 13Debug.lua 文件

mytable = {"apple", "orange", "banana"}
print(collectgarbage("count"))           --返回 Lua 使用的总内存数( KB )
mytable = nil
print(collectgarbage("count"))
print(collectgarbage("collect"))         --做一次完整的垃圾收集循环。通过参数 opt 它提供了一组不同的功能
print(collectgarbage("count"))