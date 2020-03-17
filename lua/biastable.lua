-- setting parameters for MRC table
local rule_table = {
      piority = 0,
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

local rule_bias_table1 = {
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

local rule_bias_table2 = {
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
}

tt = {
    rule_bias_table = {rule_bias_table1, rule_bias_table2},
    param_table_name="TOP",
    key=1,
    debug_output=out_debug,
    MASK1={
        MAIN = graphics, --target,
        debug_type = debugOut,
    }
}

function update_rule_bias_table(RULE_TABLE, rule_bias_tablei)
        RULE_TABLE.piority = rule_bias_tablei.piority
end

function other_flow()
    print("other flow")
end

multiRuleBias = function(in_tt)
    topTable=_G[in_tt.param_table_name]

    print(topTable.RULE_TABLE.piority)
    for k, v in pairs(tt.rule_bias_table) do
        update_rule_bias_table(topTable.RULE_TABLE, v)
        if (type(v) ~= "table") then
            print("Error: v is not a table")
        end
        if (type(v) == "table") then
            print("YES: v is a table")
        end
        print(topTable.RULE_TABLE.piority)
    end
    other_flow()
end

multiRuleBias = function(intt)
    print(topTable.RULE_TABLE.piority)
    for k, v in pairs(tt.rule_bias_table) do
        update_rule_bias_table(topTable.RULE_TABLE, v)
        if (type(v) ~= "table") then
            print("Error: v is not a table")
        end
        if (type(v) == "table") then
            print("YES: v is a table")
        end
        print(topTable.RULE_TABLE.piority)
    end
end

test = function(in_tt)
    print("In DT.test")
end

--print("size of tt[\"rule_bias_table\"] = "..table.getn(tt["rule_bias_table"]))
--print(tt["rule_bias_table"][1]["piority"])
--print(tt["rule_bias_table"][2]["piority"])
--multiRuleBias(tt)
test(tt)
