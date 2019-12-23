file = io.open("/nfs/DEV/OPC/feibin/test.log", "r")
--file = io.open("test.log", "r")
io.input(file)

local words = {}
local function printtable(t)
    if (t == nil) then
        return
    end
    for k, v in pairs(t) do
        print(v)
    end
end

local function useSpace2split(s, p)
    if (s == nil) then
        return
    end
    string.gsub(s,'[^'..p..']+',
    function (w)
        table.insert(words, w)
    end)
end

local function replacePunctuationWithSpace(s)
    if (s == nil) then
        return
    end
    s = string.gsub(s, "%p", " ")
    local p = ' '
    useSpace2split(s, p)
end

local function getWords()
    while(true)
    do
        local s = io.read()
        if(s == nil) then
            break;
        end
        replacePunctuationWithSpace(s)
    end
end

getWords()
printtable(words)
print(collectgarbage("count"))
words = nil;
collectgarbage("collect")
print(collectgarbage("count"))
io.close(file)
