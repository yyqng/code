local function test1()
    for i = 0, 0 do
        print("============")
        local mt = {t1 = {1, 2, 3}, t2 = {4, 5, 6}, t3 = {7, 8, 9}}
        for k, v in pairs(mt) do
            print(k)
        end
        mt.t0 = {}
        mt.t0.v = 1
        print(mt.t0.v)
    end
end

local function test2()
    local t = {
        key1 = "1111",
        key2 = "2222"
    }
    return t
end

local function print_keys(t)
    for k, v in pairs(t) do
        print(k .. "  " .. v)
    end
    for k in pairs(t) do
        print(k)
    end
end

local function print_ele()
    local t = {
        key1 = "11",
        key2 = "22",
        tbl = {k1 = 123, k2 = 456}
    }
    tcopy = t
    t.tbl.k3 = 789
    t[2] = 333
    --t.tbl = nil
    --tcopy.key1 = "1111"
    --tcopy.tbl.k1 = 123456
    --print(tcopy.key1)
    --print(tcopy.tbl.k3)
    print(tcopy[2])
    t.tbl.k1 = t.key1
    print(t.tbl.k1)
end

--test1()
--tt = test2()
--print_keys(tt)
print_ele()
