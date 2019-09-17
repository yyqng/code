--Name of this file can't be lualib.lua because of lualib.so
local lib = require "mylib"
print(type(lib))
print(lib.sum(23,17))
print(lib.l_sin(3.14159265354))
print(mysin(3.14159265354))
--print(lib.l_sin(3.141592653))
