--Name of this file can't be lualib.lua because of lualib.so
local lib = require "mylib"
--local lib = package.loadlib("mylib", "luaopen_mylib")
--lib()
print(type(lib))
print(lib.l_sum(23,17))
print(lib.l_sin(3.14159265354))
print(mysin(3.14159265354))
print(lib.l_dir("."))

mytable = {}
mytable[1]= "element 1"
mytable[1]= "element 2"
mytable[2]= "element 2"
myprint = function(param)
   print("myprint:",param)
end
print(lib.l_map(mytable, myprint))
