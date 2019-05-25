 
-- __index Ԫ������
mytable = { x = 3, y = 4 } 
-- metatable1  ������Ԫ��Ԫ���� __index Ϊ mytable
metatable1  = setmetatable({}, { __index = mytable }) 

--�� metatable1  ���в��� x ���ڱ���δ�ҵ�; ��Ԫ����ʹ��Ԫ���� __index (��mytable) ���ң��ҵ� 3
--�� metatable1  ���в��� z ���ڱ���δ�ҵ�; ��Ԫ����ʹ��Ԫ���� __index (��mytable) ���ң�δ�ҵ�
print (metatable1 .x, metatable1 .z)
 


-- metatable2  ��ֵΪ {key1 = "value1"}
-- metatable2  ������Ԫ��Ԫ���� __index Ϊ function ��
metatable2 = setmetatable({key1 = "value1"}, {
  __index = function( metatable2, key )
    if key == "key2" then
      return "metatablevalue"
    else
      return nil
    end
  end
})

--�� metatable2 ���в��� key1�� �ڱ��в��ң� �ҵ� "value1"
--�� metatable2 ���в��� key2�� �ڱ��в��ң� δ�ҵ�; ��Ԫ����ʹ��Ԫ���� __index (�����Ƿ������) ���ң� �ҵ� "metatablevalue"
--�� metatable2 ���в��� key3�� �ڱ��в��ң� δ�ҵ�; ��Ԫ����ʹ��Ԫ���� __index (�����Ƿ������) ���ң� δ�ҵ�
print( metatable2.key1, metatable2.key2, metatable2.key3 )

metatable2.key1    = "new value1"
metatable2.newkey1 = "new value2"
metatable2.newkey2 = "new value3"
print( "After chage metatable2, metatable2: ", metatable2.key1, metatable2.newkey1, metatable2.newkey2)
print( "After chage metatable2, mytable: ",       mytable.key1,    mytable.newkey1,    mytable.newkey2)



-- __newindex Ԫ������
-- __newindex Ԫ���������Ա���£�__index�������Ա���� ��
-- ��������һ��ȱ�ٵ�������ֵ���������ͻ����__newindex Ԫ��������������������������������и�ֵ������
-- ����ʵ����ʾ�� __newindex Ԫ������Ӧ�ã�

mytable = {}
metatable2 = setmetatable({key1 = "value1"}, { __newindex = mytable })

metatable2.key1    = "new value1"
metatable2.newkey1 = "new value2"
metatable2.newkey2 = "new value3"
print( "After chage metatable2, metatable2: ", metatable2.key1, metatable2.newkey1, metatable2.newkey2)
print( "After chage metatable2, mytable: ",       mytable.key1,    mytable.newkey1,    mytable.newkey2)



-- Ϊ����Ӳ�������
-- ����������ֵ��table.maxn ��Lua5.2���ϰ汾�����޷�ʹ��
-- �Զ�������������ֵ���� table_maxn �� ��������Ԫ�ظ���
function table_maxn(t)
    local mn = 0
    for k, v in pairs(t) do
        if mn < k then
            mn = k
        end
    end
    return mn
end

-- ������Ӳ���
mytable = setmetatable({ 10, 20, 30 }, {
  __add = function(mytable, newtable)
    for i = 1, table_maxn(newtable) do
      table.insert(mytable, table_maxn(mytable)+1,newtable[i])
    end
    return mytable
  end
})

secondtable = {40,50,60}

mytable = mytable + secondtable
    for k,v in ipairs(mytable) do
print(k,v)
end



-- __call Ԫ����:
-- __call Ԫ������ Lua ����һ��ֵʱ���á�����ʵ����ʾ�˼������Ԫ�صĺͣ�

-- ����Ԫ���� __call
mytable = setmetatable({10}, {
  __call = function(mytable, newtable)
    sum = 0
    for i = 1, table_maxn(mytable) do
        sum = sum + mytable[i]
    end
    for i = 1, table_maxn(newtable) do
        sum = sum + newtable[i]
    end
    return sum
  end
})
newtable = {10,20,30}
print(mytable(newtable))
-- print(mytable)

-- __tostring Ԫ����
-- __tostring Ԫ���������޸ı�������Ϊ������ʵ�������Զ����˱��������ݣ�

mytable = setmetatable({ 10, 20, 30 }, {
  __tostring = function(mytable)
    sum = 0
    for k, v in pairs(mytable) do
        sum = sum + v
    end
    return "Sum is : " .. sum
  end
})
print(mytable)