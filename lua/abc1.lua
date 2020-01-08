local Set = {}
function Set.new(t)
    local set = {}
    for _, l in ipairs(t) do
        set[l] = true
    end
    return set
end

function table_len(t)
  local len = 0
  for k, v in pairs(t) do
    len = len + 1
  end
  return len;
end

local mt = {
    __sub = function(a, b)
    	for i, v in pairs(b) do
    	    a[i] = not v or nil
    	end
        return a
	end,
    __tostring = function(a)
        local s = "{"
        local len = table_len(a)
        local count = 1
    	for i, v in pairs(a) do
    	    s = s..i
            if count < len then
                s = s..", "
            end
            count = count + 1
    	end
    	s = s.."}"
        return s
	end
}

Set.insert = function(set, ele)
	set[ele] = true
	return set
end

Set.remove = function(set, ele)
	set[ele] = nil
	return set
end

--Please add the following functions for object Set:
--subtraction. Example: 
local a = Set.new{3, 4, 5}
setmetatable(a, mt)
local b = Set.new{1, 3, 6}
print(a - b) -- output {4, 5}

--Insertion. Example:
local a = Set.new{3, 4, 5}
setmetatable(a, mt)
print(Set.insert(a, 7)) -- output {4, 5, 3, 7}

----Deletion. Example:
local a = Set.new{3, 4, 5}
setmetatable(a, mt)
print(Set.remove(a, 4)) -- output {5, 3}
