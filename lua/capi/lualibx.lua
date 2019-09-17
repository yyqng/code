--Name of this file can't be lualib.lua because of lualib.so
local mylib = require "lualib"
print(type(mylib))
print(mylib.sum(23,17))
print(mylib.l_sin(3.14159265354))
--print(mylib.l_sin(3.141592653))
