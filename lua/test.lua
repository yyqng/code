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
bittest(0)
bittest(1)
bittest(2)
bittest(3)
bittest(4)
bittest(5)
bittest(6)
bittest(7)
bittest(8)
