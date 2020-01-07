Set = {}

function Set.new(t)
    local set = {}
    for _, l in ipairs(t) do
        set[l] = true
    end
    return set
end

function Set.union(a, b)
    local res = Set.new{}
    for k in pairs(a) do res[k] = true end
    for k in pairs(b) do res[k] = true end
    return res
end

function Set.intersection (a,b)
	local res = Set.new{}
	for k in pairs(a) do res[k] = b[k] end
	return res
end

function Set.tostring (set)
	local s = "{"
	local sep = ""
	for e in pairs(set) do
        s = s .. sep .. e
        sep = ", "
	end
	return s .. "}"
end

function Set.print (s)
	print(Set.tostring(s))
end

local s1 = Set.new{10, 20, 30, 50, 30}
local s2 = Set.new{1, 20, 3, 5, 3}
Set.print(s1)
Set.print(s2)
Set.print(Set.union(s1, s2))



t = {} -- original table (created somewhere)
-- keep a private access to original table
local _t = t
-- create proxy
t = {}
-- create metatable
local mt = {
    __index = function (t,k)
        print("*access to element " .. tostring(k))
        return _t[k] -- access the original table
    end,
    __newindex = function (t,k,v)
        print("*update of element " .. tostring(k) ..
        " to " .. tostring(v))
        _t[k] = v -- update original table
    end
}
setmetatable(t, mt)




--Please add the following functions for object Set:
--subtraction. Example: 
local a = Set.new{3, 4, 5}
Local b = Set.new{1, 3, 6}
print(a-b) -- output {4, 5}
--Insertion. Example:
local a = Set.new{3, 4, 5}
Print(Set.insert(a, 7)) -- output {3, 4, 5, 7}
--Deletion. Example:
local a = Set.new{3, 4, 5}
Print(Set.remove(a, 4)) -- output {3, 5}


a = 100
print(a)    -- result is 100
magic_start()
a = 100
print(a)    -- please print out twice of the original value, result is 200
magic_end()
a = 100
print(a)    -- print out the original value again, result is 100

--Answer of question 1
Set.subtraction = function(a, b)
    local res = Set.new{}
	for k in pairs(a) do
	    res[k] = not b[k] or nil
	end
	return res
end

Set.insert = function(set, ele)
    local res = Set.new{}
	for i, v in pairs(set) do
	    res[i] = true
	end
	res[ele] = true
	return res
end

Set.remove = function(set, ele)
    local res = Set.new{}
	for i, v in pairs(set) do
	    res[i] = true
	end
	res[ele] = nil
	return res
end

Set.mt__sub = Set.subtraction


--Answer for question 2
real_value = {}
local mtG = {
    __index = function(t, k)
	    return real_value[k] and real_value[k] * 2 or nil
	end,
    __newindex = function(t, k, v)
	    real_value[k] = v
	end,
}
setmetatable(_G, mtG)
a = 100
print(a) -- 200

setmetatable(_G, nil)
a = 100
print(a) -- 100

--Answer for question 3
local data1 = {a = 3, b = 4, c = 5}
local data2 = {}
local mt = {
    _index = function(t, k)
	    if string.sub(k, 1, 6) == "DATA2_" then
		    return nil
		else
		    return data1[k]
		end
	end,
	_newindex = function(t, k, v)
	    if string.sub(k, 1, 6) == "DATA2_" then
		    local tmp_mt = getmetatable(t)
			setmetatable(t, nil)
			t[k] = v
			setmetatable(t, tmp_mt)
		else
		    return data1[k]
		end
	end
}
setmetatable(data2, mt)