local f

local function g ()
    print("call g")
    f()
end

function f () --不能定义为local，否则将定义一个新的f，从而使前面的f变成为定义的状态
    print("call f")
end

g()