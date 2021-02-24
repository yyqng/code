
--make copy of a table
function deepcopy(object)
    local lookup_table = {}
    local function _copy(object)
      if type(object) ~= "table" then
        return object
      elseif lookup_table[object] then
        return lookup_table[object]
      end
      local new_table = {}
      lookup_table[object] = new_table
      for index, value in pairs(object) do
        new_table[_copy(index)] = _copy(value)
      end
      return setmetatable(new_table, getmetatable(object))
    end
    return _copy(object)
end


function printAll(var, name, table_depth, suf)
    if ("string"~=type(name) and "number"~=type(name)) then name="UNKNOWN" end
    if ("string"~=type(suf)) then suf="  " end
    local ending = ""
    --if ("userdata"==type(var) and not is_model) then ending=DT.get(var) end
    print (suf .. name .. " = ", var, ending)
    if ("table"==type(var)) then
        print(suf .. name .. " = {")
        if ("number"==type(table_depth)) then
            table_depth = table_depth-1
        else
            table_depth = 5
        end
        if ("number"~=type(table_depth) or table_depth>=0) then
            local subsuf = suf.."  "
            for subname,subvar in pairs(var) do
                if ("sgm_pw_model"~=name) then
                    printAll(subvar, subname, table_depth, subsuf)
                else
                    printAll(subvar, subname, table_depth, subsuf)
                end
            end
        end
        print(suf .. "}")
    end
end