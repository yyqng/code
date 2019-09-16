local bit = require "bit"
local num = bit.tobit(0x08040201)
print(num)

--第一组Blue数据的取得：
local t_num = num
local blue = bit.band(t_num, 0x000000ff)
print("blue:"..blue)

--第二组Green数据的取得：
local t_num = bit.rshift(num, 8)
local green = bit.band(t_num, 0x000000ff)
print("green:"..green)

--第三组Red数据的取得：
local t_num = bit.rshift(num, 16)
local red = bit.band(t_num, 0x000000ff)
print("red:"..red)

--第四组Alpha数据的取得：
local t_num = bit.rshift(num, 24)
local alpha = bit.band(t_num, 0x000000ff)
print("alpha:"..alpha)
