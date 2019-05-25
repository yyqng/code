-- 13Debug.lua �ļ�

function myfunction ()
    print(debug.traceback("Stack trace begin:"))
    print(debug.getinfo(1))
    print("Stack trace end!")
    return 10
end

print("-----------------------")
myfunction ()
print("***********************")
print(debug.traceback("Stack trace begin:"))
print(debug.getinfo(1))
print("Stack trace end!")
print("-----------------------")


function newCounter ()
  local n = 0
  local k = 0
  return function ()
    k = n
    n = n + 1
    return n
    end
end


counter = newCounter ()
print(counter())
print(counter())

local i = 1

repeat
  name, val = debug.getupvalue(counter, i)    -- getupvalue �����鿴�ֲ������ĵ�ǰ״̬
  if name then
    print ("index", i, name, "=", val)
    if(name == "n") then
        debug.setupvalue (counter,2,10)
    end
    i = i + 1
  end -- if
until not name
--������ʵ���У���������ÿ�ε���ʱ��������1��ʵ��������ʹ���� �����ǿ������þֲ�����Ϊ��ֵ��ʵ���У�������ǰ n ��ֵΪ 2,ʹ�� setupvalue ������������Ϊ 
--10���������ǵ��ú�����ִ�к����Ϊ 11 ������ 3��

print(counter())
print("***********************")
