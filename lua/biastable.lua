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

rule_bias_table_a = {
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

local function update_rule_bias_table(RULE_TABLE, rule_bias_tablei)
    for k, v in pairs(rule_bias_tablei) do
        if(type(v) ~= "table") then
            print("update " .. k)
            RULE_TABLE[k] = v
        else
            print("update table    " .. k)
            RULE_TABLE[k] = mydeepcopy(v)
        end
    end
end

local DT = {}
DT.execute_function = function (a)
    print(a)
end

local function check_table()
    print("check_table")
end

local function check_rule_bias_tablei(rule_bias_tablei)
    local rule_bias_table_all = {
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
        endSizeTable = {},
        endDistanceTable = {},
        endBiasTable = {},
        endSpaceTable = {},
        endSideSpaceTable = {},
        endWidthTable = {},
            
        widthTable = {},
        spaceTable = {},
        lengthTable = {},
        biasTable = {},
        endRetargetOption = 2,
        ruleSmallSegment = 30,
    
        spendBiasTable = {},
        spendDistanceTable = {},
        spendSizeTable = {},
        spendWidthTable = {},
        spendSdieWidthTable = {},
        spendSpaceTable = {},
    
        freezeSegments = {},
        spendRetargetOption = 2,
        endBiasWeightingOption = 2,
        spendBiasWeightingOption = 2,
        endSideSpaceWeight = 0.2,
        spendSideWidthWeight = 0.2,
        ruleQueryOption = 3,
    }

    print("check each table ============")
    for k, v in pairs(rule_bias_tablei) do
        if(type(rule_bias_table_all[k]) ~= type(v)) then
            error(k .. " is illegal parameter.")
        end
    end
end

local function multiRuleBias(tt)
    for k, v in pairs(tt.rule_bias_table) do
        if(type(v) ~= "table") then
            error("All elements of rule_bias_table must be table")
        end
        check_rule_bias_tablei(v)
    end

    local topTable = _G[tt.param_table_name]
    local backup_table = mydeepcopy(topTable.RULE_TABLE)
    --printtable(topTable.RULE_TABLE)
    --printtable(backup_table)
    DT.execute_function("AppMainRuleRedissection")
    for k, v in pairs(tt.rule_bias_table) do
        if(type(v) ~= "table") then
            error("rule_bias_table must be a table")
        end
        topTable.RULE_TABLE = mydeepcopy(backup_table)
        update_rule_bias_table(topTable.RULE_TABLE, v)
        DT.execute_function("ruleAppReinit")
        DT.execute_function("AppMainRuleBias")
    end
    topTable.RULE_TABLE = mydeepcopy(backup_table)
end

DT.rule = function (tt)
    local topTable = _G[tt.param_table_name]
    --if(table.getn(tt.rule_bias_table) > 0) then
    if(tt.rule_bias_table ~= nil) then
        multiRuleBias(tt)
    else
        DT.execute_function("ruleAppMain")
    end
end


local function AppInit()
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
        MASK1 = {
            MAIN = graphics, --target,
            debug_type = debugOut,
        }
    }
end

local function AppMain()
    DT.rule(tt)
end

AppInit()
AppMain()
