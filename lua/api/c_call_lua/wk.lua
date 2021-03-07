package.cpath = '/home/yoyu/hub/testcode/lua/api/?.so;'    --搜索so模块
local lib = require "libtest"

function wk(a, b)
    local res = lib.lsum(a, b)
    return res
end

function wkinit()
    local hello= "Hello from wkinit in wk.lua"
    print(hello)
    lib.lwkinit()
end

function wkmain()
    local hello= "Hello from wkmain in wk.lua"
    print(hello)
    lib.lwkmain()
end

--wk()
