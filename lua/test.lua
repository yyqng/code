local getbit=function(mask, bit)
    if bit < 1 then
        return false
    end
    bit = bit -1
    tmp = mask / math.ldexp(1, bit)
    mask = math.floor(tmp)
    if math.mod(mask, 2) == 1 then
        return true
    else
        return false
    end
    return false
end

local debugOutputMask=function (maskDesc, debugMask)
    mask = tonumber(debugMask)
    if(mask >= 7 or mask < 0) then
        return true
    end
    if(maskDesc == "MAIN" and getbit(mask, 1)) then
        return true
    end
    if(maskDesc == "SRAF" and getbit(mask, 2)) then
        return true
    end
    if(maskDesc == "SRIF" and getbit(mask, 3)) then
        return true
    end
    return false
end

--debugMask = 2;
--debugOutputMask("SRIF", debugMask)
--debugMask = 3;
--debugOutputMask("SRIF", debugMask)
--debugMask = 4;
--debugOutputMask("SRIF", debugMask)
--debugMask = 5;
--debugOutputMask("SRIF", debugMask)
--debugMask = 6;
--debugOutputMask("SRIF", debugMask)
--debugMask = 7;
--debugOutputMask("SRIF", debugMask)

local bittest=function(mask)
    bit = 0
    print(mask, bit, "result", getbit(mask, bit))
    bit = 1
    print(mask, bit, "result", getbit(mask, bit))
    bit = 2
    print(mask, bit, "result", getbit(mask, bit))
    bit = 3
    print(mask, bit, "result", getbit(mask, bit))
    bit = 4
    print(mask, bit, "result", getbit(mask, bit))
    print("------------")
end

--debugMask = 1;
--debugOutputMask("SRIF", debugMask)

local bittest_main=function(mask)
    bittest(0)
    bittest(1)
    bittest(2)
    bittest(3)
    bittest(4)
    bittest(5)
    bittest(6)
    bittest(7)
    bittest(8)
end

local vv_test = function(mask)
    local vv = {
        {{}, 6, 220},
        5
    }
    local type_error_msg = "[ERROR] DT.correction USER_LAYER is expected to be a table of tables,"..
                       " each table is formatted as {layer_handle, FT, FL}"
    if (type(vv) ~= "table") then
        print(type_error_msg)
        return
    end

    if (vv ~= nil) then
        for k, v in pairs (vv) do
            if (type(v) ~= "table") then
                print(type_error_msg)
                return
            end
            local layer = v[1]
            local ftype = v[2]
            local flevel = v[3]
            print("type(v) = "..type(v)) 
            print("type(layer) = "..type(layer)) 
            print("type(ftype) = "..type(ftype)) 
            print("type(flevel) = "..type(flevel)) 
        end
    end
end
vv_test()
