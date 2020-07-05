-- setting parameters for MRC table
local rule_table = {
      piority = 0,
      TAG=TAGS,
      DEFAULT={
          piority_point_final = 1,
          widthTable = {40, 80, 120},
          spaceTable = {40, 80, 120},
          lengthTable = {40, 200},
          biasTable=--{ w[40,80) [80,120) [120,inf)
                      {   3,          2,       1,    --s[40,80)
                          6,          5,       4,    --s[80,120)
                          9,          8,       7},   --s[120,inf)
          ruleEndMaxWidth = 40,
      }
  }

local rule_bias_table1 = {
    endSpMeasureExtension = 5,
    inSpMeasureExtension = 5,
    inSpMeasureExtensionV = -5,
    inSpMeasureRange = -60,
    inWdMeasureExtension = -5,
    inWdMeasureExtensionV = 5,
    inWdMeasureRange = -60,
    outSpMeasureExtension = -5,
    outSpMeasureExtensionV = 5,
    outSpMeasureRange = -60,
    outWdMeasureExtension = 5,
    outWdMeasureExtensionV = -5,
    outWdMeasureRange = -60,
    runSpMeasureExtension = -5,
    runWdMeasureExtension = 5,
    spendWdMeasureExtension = 5,
    
    doLengthInterpolation = 1,
    doSpaceInterpolation= 0,
    endSizeTable = {30, 40, 50},
    endDistanceTable = {30, 45, 55, 100, 110, 120},
    endBiasTable = {-- w[30,40) [40,50) [50,inf)
                        8,      8,      8,    --s[30,45)  
                        15,     15,     15,   --s[45,55)
                        18,     18,     18,   --s[55,100)
                        20,     20,     20,   --s[100,110)
                        22,     22,     22,   --s[110,120)
                        25,     25,     25,   --s[120,inf)
        },
        
    widthTable = {40, 80, 120},
    spaceTable = {40, 80, 120},
    lengthTable = {40, 200},
    biasTable=--{ w[40,80) [80,120) [120,inf)
                  {3,          2,          1,    --s[40,80)
                   6,          5,          4,    --s[80,120)
                   10,          8,          7},   --s[120,inf)
    --[[
                  {35,          25,          15,    --s[40,80)
                   65,          55,          45,    --s[80,120)
                   95,          85,          75},   --s[120,inf)
                }, ]]
    endRetargetOption = 2,
    ruleSmallSegment = 30,

    endSpaceTable = {},
    spendBiasTable = {},
    spendDistanceTable = {},
    spendRetargetOption = 2,
    spendSizeTable = {},
    spendWidthTable = {},
    freezeSegments = {},
    endSideSpaceTable = {},
    endWidthTable = {},
    spendSdieWidthTable = {},
    spendSpaceTable = {},
    endBiasWeightingOption = 2,
    spendBiasWeightingOption = 2,
    endSideSpaceWeight = 0.2,
    spendSideWidthWeight = 0.2,
    ruleQueryOption = 3,
}

local rule_bias_table2 = {
    endSpMeasureExtension = 5,
    inSpMeasureExtension = 5,
    inSpMeasureExtensionV = -5,
    inSpMeasureRange = -60,
    inWdMeasureExtension = -5,
    inWdMeasureExtensionV = 5,
    inWdMeasureRange = -60,
    outSpMeasureExtension = -5,
    outSpMeasureExtensionV = 5,
    outSpMeasureRange = -60,
    outWdMeasureExtension = 5,
    outWdMeasureExtensionV = -5,
    outWdMeasureRange = -60,
    runSpMeasureExtension = -5,
    runWdMeasureExtension = 5,
    spendWdMeasureExtension = 5,
    
    doLengthInterpolation = 1,
    doSpaceInterpolation= 0,
    endSizeTable = {30, 40, 50},
    endDistanceTable = {30, 45, 55, 100, 110, 120},
    endBiasTable = {-- w[30,40) [40,50) [50,inf)
                        8,      8,      8,    --s[30,45)  
                        15,     15,     15,   --s[45,55)
                        18,     18,     18,   --s[55,100)
                        20,     20,     20,   --s[100,110)
                        22,     22,     22,   --s[110,120)
                        25,     25,     25,   --s[120,inf)
        },
        
    widthTable = {40, 80, 120},
    spaceTable = {40, 80, 120},
    lengthTable = {40, 200},
    biasTable=--{ w[40,80) [80,120) [120,inf)
                  {3,          2,          1,    --s[40,80)
                   6,          5,          4,    --s[80,120)
                   11,          8,          7},   --s[120,inf)
    --[[
                  {35,          25,          15,    --s[40,80)
                   65,          55,          45,    --s[80,120)
                   95,          85,          75},   --s[120,inf)
                }, ]]
    endRetargetOption = 2,
    ruleSmallSegment = 30,

    endSpaceTable = {},
    spendBiasTable = {},
    spendDistanceTable = {},
    spendRetargetOption = 2,
    spendSizeTable = {},
    spendWidthTable = {},
    freezeSegments = {},
    endSideSpaceTable = {},
    endWidthTable = {},
    spendSdieWidthTable = {},
    spendSpaceTable = {},
    endBiasWeightingOption = 2,
    spendBiasWeightingOption = 2,
    endSideSpaceWeight = 0.2,
    spendSideWidthWeight = 0.2,
    ruleQueryOption = 3,

}

rule_bias_table_all = {
    endSpMeasureExtension = 5,
    inSpMeasureExtension = 5,
    inSpMeasureExtensionV = -5,
    inSpMeasureRange = -60,
    inWdMeasureExtension = -5,
    inWdMeasureExtensionV = 5,
    inWdMeasureRange = -60,
    outSpMeasureExtension = -5,
    outSpMeasureExtensionV = 5,
    outSpMeasureRange = -60,
    outWdMeasureExtension = 5,
    outWdMeasureExtensionV = -5,
    outWdMeasureRange = -60,
    runSpMeasureExtension = -5,
    runWdMeasureExtension = 5,
    spendWdMeasureExtension = 5,
    
    doLengthInterpolation = 1,
    doSpaceInterpolation= 0,
    endSizeTable = {30, 40, 50},
    endDistanceTable = {30, 45, 55, 100, 110, 120},
    endBiasTable = {-- w[30,40) [40,50) [50,inf)
                        8,      8,      8,    --s[30,45)  
                        15,     15,     15,   --s[45,55)
                        18,     18,     18,   --s[55,100)
                        20,     20,     20,   --s[100,110)
                        22,     22,     22,   --s[110,120)
                        25,     25,     25,   --s[120,inf)
        },
        
    widthTable = {40, 80, 120},
    spaceTable = {40, 80, 120},
    lengthTable = {40, 200},
    biasTable=--{ w[40,80) [80,120) [120,inf)
                  {3,          2,          1,    --s[40,80)
                   6,          5,          4,    --s[80,120)
                   20,          8,          7},   --s[120,inf)
    --[[
                  {35,          25,          15,    --s[40,80)
                   65,          55,          45,    --s[80,120)
                   95,          85,          75},   --s[120,inf)
                }, ]]
    endRetargetOption = 2,
    ruleSmallSegment = 30,

    endSpaceTable = {},
    spendBiasTable = {},
    spendDistanceTable = {},
    spendRetargetOption = 2,
    spendSizeTable = {},
    spendWidthTable = {},
    freezeSegments = {},
    endSideSpaceTable = {},
    endWidthTable = {},
    spendSdieWidthTable = {},
    spendSpaceTable = {},
    endBiasWeightingOption = 2,
    spendBiasWeightingOption = 2,
    endSideSpaceWeight = 0.2,
    spendSideWidthWeight = 0.2,
    ruleQueryOption = 3,
}

local function rule_bias_tablei_check(rule_bias_tablei)
    for k, v in pairs(rule_bias_tablei) do
        if(type(v) ~= "table") then
            error("rule_bias_tablei must be a table")
        end
        update_rule_bias_table(rule_table, v)
        new_flow(rule_table.endSpMeasureExtension)
    end
end

local function rule_bias_table_check(rule_bias_table)
    for k, v in pairs(rule_bias_table) do
        if(type(v) ~= "table") then
            error("must be a table")
        end
    end
end

local function printtable(table)
    print("")
    print("printtable <<<<<<<<<<<<< ")
    for k, v in pairs(table) do
        if(type(v) ~= "table") then
            print("table[ "..k.." ] = "..v)
        end
    end
    print("printtable >>>>>>>>>>>>")
    print("")
end


--make a copy of a table (object). function will return a copied table
local function mydeepcopy(object)   -- replaced by drcplusfunc.lua
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


local function backup_rule_bias_table(RULE_TABLE, backup_table)
    for k, v in pairs(RULE_TABLE) do
        if(type(v) ~= "table") then
            backup_table[k] = v
            backup_table[k] = 11111
        else
            backup_table[k] = mydeepcopy(v)
        end
    end

    printtable(RULE_TABLE)
    printtable(RULE_TABLE.DEFAULT.widthTable)
    backup_table.DEFAULT.widthTable[1] = 1000
    backup_table.DEFAULT.widthTable[2] = 2000
    backup_table.DEFAULT.widthTable[3] = 3000
    printtable(backup_table)
    printtable(backup_table.DEFAULT.widthTable)
end

local function update_rule_bias_table(RULE_TABLE, rule_bias_tablei)
        --print(" RULE_TABLE.DEFAULT.biasTable[7] = ".. RULE_TABLE.DEFAULT.biasTable[7])
        --print(" rule_bias_tablei.biasTable[7] = "..rule_bias_tablei.biasTable[7])
        RULE_TABLE.DEFAULT.biasTable[7] = rule_bias_tablei.biasTable[7]
        --print(" RULE_TABLE.DEFAULT.biasTable[7] = ".. RULE_TABLE.DEFAULT.biasTable[7])
        --print(" rule_bias_tablei.biasTable[7] = "..rule_bias_tablei.biasTable[7])
--    for k, v in pairs(rule_bias_tablei) do
--        repeat
--            if(type(v) == "table") then
--               break 
--            end
--            if(rule_bias_table_all[k] == nil) then
--            --    print("--------"..k.." is not exsit ")
--            end
--            RULE_TABLE[k] = v
----            print(k.." "..v)
--        until true
--    end
end

local function multi_rule_bias_param_check()
    print("multi_rule_bias_param_check")
end

local function new_flow(value)
    print("new flow: value = "..value)
end

local function old_flow()
    print("old flow")
end

local DT = {}
local function myexecute_function(a, b, c, d, e)
    print("myexecute_function "..a)
end

DT.execute_function = myexecute_function

local function check_table()
    print("check_table")
end

local function check_rule_bias_table(rule_bias_table)
    for k, v in pairs(rule_bias_table) do
        if(type(v) ~= "table") then
            error("must be a table")
        end
    end

    for k, v in pairs(rule_bias_table) do
        print("check each table ============")
        for k2, v2 in pairs(v) do
            print("k2 = " .. k2 .. ",type(k2) = " .. type(k2))
            if(rule_bias_table_all[k2] == nil) then
                error(k2 .. " is illegal parameter.")
            end
            if(type(v2) == "table") then
                check_table()
            end
        end
    end
end

local function multiRuleBias(tt)
    check_rule_bias_table(tt.rule_bias_table)

    local topTable = _G[tt.param_table_name]
    local backup_table = mydeepcopy(topTable.RULE_TABLE)
    --printtable(topTable.RULE_TABLE)
    --printtable(backup_table)
    DT.execute_function("AppMainRuleRedissection", "DT[tableName].tt.lib", 1, "DT[tableName].tt.param_table_name", "{key=DT[tableName].tt.key}")
    for k, v in pairs(tt.rule_bias_table) do
        if(type(v) ~= "table") then
            error("must be a table")
        end
        update_rule_bias_table(topTable.RULE_TABLE, v)
        DT.execute_function("ruleAppReinit", "DT[tableName].tt.lib", 1, "DT[tableName].tt.param_table_name", "{key=DT[tableName].tt.key}")
        DT.execute_function("ruleAppMain", "DT[tableName].tt.lib", 1, "DT[tableName].tt.param_table_name", "{key=DT[tableName].tt.key}")
    end
    topTable.RULE_TABLE = mydeepcopy(backup_table)
end

local function myrule(tt)
    local topTable = _G[tt.param_table_name]
    --if(table.getn(tt.rule_bias_table) > 0) then
    if(tt.rule_bias_table ~= nil) then
        multiRuleBias(tt)
    else
        DT.execute_function("ruleAppMain", "DT[tableName].tt.lib", 1, "DT[tableName].tt.param_table_name", "{key=DT[tableName].tt.key}")
    end
end


TOP={      
  runRetarget=2,   
  RULE_TABLE=rule_table,
}

tt = {
    test1 = 0,
    rule_bias_table = {rule_bias_table1, rule_bias_table2},
    param_table_name="TOP",
    key=1,
    debug_output=out_debug,
    MASK1={
        MAIN = graphics, --target,
        debug_type = debugOut,
    }
}
DT.rule = myrule
DT.rule(tt)
