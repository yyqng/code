-- 13Debug.lua 文件

Rectangle = {area = 0, length = 0, breadth = 0}  -- Meta class


function Rectangle:new (o,length,breadth)        -- 派生类的方法 new
  o = o or {}
  setmetatable(o, self)
  self.__index = self
  self.length = length or 0
  self.breadth = breadth or 0
  self.area = length*breadth;
  return o
end

function Rectangle:printArea ()                  -- 派生类的方法 printArea
  print("Area of rectangle ",self.area)
end


r = Rectangle:new(nil,10,20)
print(r.length)
r:printArea()