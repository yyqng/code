r = {}
local mtG = {
    __index = function(t, k)
	    return r[k] and r[k] * 2 or nil
	end,
    __newindex = function(t, k, v)
	    r[k] = v
	end,
}

setmetatable(_G, mtG)
a = 100
print(a) -- 200

setmetatable(_G, nil)
b = 100
print(b) -- 100
