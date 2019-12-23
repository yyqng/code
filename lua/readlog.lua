file = io.open("/nfs/DEV/OPC/feibin/test.log", "r")
--file = io.open("test.log", "r")
io.input(file)

local words = {}
function printtable(t)
    if (t == nil) then
        return
    end
    for k, v in pairs(t) do
        print(v)
    end
end

function useSpace2split(s, p)
    if (s == nil) then
        return
    end
    string.gsub(s,'[^'..p..']+',
    function (w)
        table.insert(words, w)
    end)
end

function replacePunctuationWithSpace(s)
    if (s == nil) then
        return
    end
    s = string.gsub(s, "%p", " ")
    local p = ' '
    useSpace2split(s, p)
end

function getWords()
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
words = nil;
collectgarbage()
io.close(file)
