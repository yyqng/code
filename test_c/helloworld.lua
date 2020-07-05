function myprint1(n)
    for i=1,n do
        print(i)
    end
    print(debug.traceback("Stack trace"))
    print(debug.getinfo(1))
    print("Stack trace end")
end

--print("enter a number:")
--a=io.read("*number")

function myprint2()
    n = 2
    for mycount = 1, n do
        print("yyyyyyyyyy in myAppModelApply: enter judge3333.  mycount = " .. mycount.."**"..mycount.."**"..mycount.."**"..mycount.."**"..mycount)
    end
end

function print_table(table)
    for k, v in pairs(table) do
        print("k "..type(k).." "..k.." = "..v)
        print("k "..type(k).." "..k.." = "..table[k])
    end
end

function assignment()
    local a = 1
    local b = a
    b = 2
    print("a = "..a.." b = "..b)
    a = {1}
    b = a
    b[1] = 2
    print("a[1] = "..a[1].." b[1] = "..b[1])
end

-- setting parameters for MRC table
local rule_table = {
      piority = 1,
      TAG=TAGS,
      DEFAULT={
          piority_point_final = 1,
          widthTable = {40, 80, 120},
          spaceTable = {40, 80, 120},
          --lengthTable = {40, 200},
          biasTable=--{ w[40,80) [80,120) [120,inf)
                      {   3,          2,       1,    --s[40,80)
                          6,          5,       4,    --s[80,120)
                          9,          8,       7},   --s[120,inf)
          ruleEndMaxWidth = 40,
      }
  }

local table1 = {
      piority = 1,
      DEFAULT={
          piority_point_final = 1,
          widthTable = {40, 80, 120},
          spaceTable = {40, 80, 120},
          --lengthTable = {40, 200},
          biasTable=--{ w[40,80) [80,120) [120,inf)
                      {   3,          2,       1,    --s[40,80)
                          6,          5,       4,    --s[80,120)
                          9,          8,       7},   --s[120,inf)
          ruleEndMaxWidth = 40,
      }
  }

local table2 = {
      piority = 2,
      DEFAULT={
          piority_point_final = 1,
          widthTable = {40, 80, 120},
          spaceTable = {40, 80, 120},
          --lengthTable = {40, 200},
          biasTable=--{ w[40,80) [80,120) [120,inf)
                      {   3,          2,       1,    --s[40,80)
                          6,          5,       4,    --s[80,120)
                          9,          8,       7},   --s[120,inf)
          ruleEndMaxWidth = 40,
      }
  }


TOP={      
  runRetarget=2,   
  RULE_TABLE=rule_table,
  rule_bias_table = {table1, table2}
}

a = 1
--myprint1(a)
--myprint2()
--local i = (1 and 10) or 0
--print(i)
--local i = (nil and 20) or 0
--print(i)

--local mytable = {test1 = 1}
--mytable["test2"] = 2
--print_table(mytable)
--subtable = {subtest1 = 1, subtest2 = 2}
--mytable["test3"] = {t1 = subtable}
--print_table(mytable["test3"]["t1"])

--TOP["rule_bias_table"] = {rule_bias_table1 = rule_bias_table1}, --, rule_bias_table2 = rule_bias_table2, rule_bias_table3 = rule_bias_table3},
print(table.getn(TOP.rule_bias_table))
print(TOP["rule_bias_table"][1]["piority"])
print(TOP["rule_bias_table"][2]["piority"])
--print(table1["DEFAULT"]["biasTable"][1])
--print(TOP["RULE_TABLE"]["DEFAULT"]["biasTable"][1])

--assignment()
