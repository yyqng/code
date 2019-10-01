--Usage1:
package.path = package.path..";/home/yoyu/hub/testcode/lua/capi/?.lua"
require("a")
--1. Set LUA_PATH=.
--2. execute this script: lua -la -lb
--
--
--Usage2:
--1. enter lua interactive mode
--2. > dofile("a.lua")
--3. > dofile("b.lua"
print(x)
