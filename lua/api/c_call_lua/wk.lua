package.cpath = '/home/yoyu/hub/testcode/lua/api/?.so;'    --搜索so模块
local lib = require "libtest"

local hello= "Hello from wk.lua"
print(hello)

function wk(a, b)
    local res = lib.lsum(a, b)
    return res
end

function wkinit()
    lib.lwkinit()
end

function wkmain()
    lib.lwkmain()
end

--wk()