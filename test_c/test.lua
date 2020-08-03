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

local function print_type()
    local vv = {
        {nil, 6, 230},
        key1 = "11",
        key2 = "22",
        tbl = {k1 = 123, k2 = 456},
        xxxx
    }
    for k, v in pairs (vv) do
        local layer = v[1]
        local ftype = v[2]
        local flevel = v[3]
        print("yyy:".."  "..type(layer).."  "..type(ftype).."  "..type(flevel))
    end
end

local function print_tt()
    local tt = {
        lib = mylib,
        param_table_name="TOP",
        key=1,
        debug_output=out_gds,
        MASK1 = {
            MAIN = target31,
            model_list={
                ID1={model=model1},
            },
            debug_type = DEBUG1,
            -- USER_LAYER is a new parameter for OPC-26338.
            USER_LAYER = {
                {target30, 6, 100}, -- ftype is 6 and flelve is 100.
                {target17, 6, 101}, -- ftype is 6 and flelve is 101.
            }
        }
    }
    old_output_table = tt
    old_output_table[1] = {}
    old_output_table[1].DIS = 5
    print("yyy:".."  "..old_output_table[1].DIS)
end

--test1()
--tt = test2()
--print_keys(tt)
--print_ele()
--print_type()
--print_tt()
print(type(print_tt))
if (print_t) then
    print("print_t is not nil")
else
    print("print_t is nil")
end
