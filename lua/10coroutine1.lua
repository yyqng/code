-- 10coroutine1.lua �ļ�
co1 = coroutine.create(         --        // ���� coroutine������ coroutine�� ������һ������������resume���ʹ�õ�ʱ��ͻ��Ѻ�������
    function(i)
        print( "create: function, para:", i);
    end
)
 
coroutine.resume(co1, 100)      -- 100    // ���� coroutine ���� create ���ʹ��
print( coroutine.status(co1) )  -- dead   // �鿴 coroutine ��״̬( dead�� suspend�� running )

print("----------")

co1 = coroutine.wrap(           --        // ����coroutine������һ��������һ�����������������ͽ���coroutine����create�����ظ�
    function(i)
        print( "wrap:   function, para:", i);
        print(i);
    end
)
 
co1(100)                        -- 100 
 
print("----------")
 
co2 = coroutine.create(
    function()
        for i=1,10 do
            print(i)
            if i == 3 then
                print(coroutine.status(co2))   --running
                print(coroutine.running())     --thread:XXXXXX  // ���������ܵ�coroutine, һ��coroutine����һ���̣߳���ʹ��running��ʱ�򣬾��Ƿ���һ��corouting���̺߳�
            end
            coroutine.yield()   --          // ���� coroutine ���� coroutine ����Ϊ����״̬������� resume ���ʹ�����кܶ����õ�Ч��
        end
    end
)
 
coroutine.resume(co2)           --1
coroutine.resume(co2)           --2
coroutine.resume(co2)           --3
 
print(coroutine.status(co2))    -- suspended ��ͣ
print(coroutine.running())
 
print("-----------------------------------------------------------------")


--[[
����resume����Эͬ������,resume�����ɹ�����true�����򷵻�false��
Эͬ�������У�
���е�yield��䣻
yield����Эͬ���򣬵�һ��resume���أ���ע�⣺�˴�yield���أ�������resume�Ĳ�����
�ڶ���resume���ٴλ���Эͬ���򣻣�ע�⣺�˴�resume�Ĳ����У����˵�һ��������ʣ�µĲ�������Ϊyield�Ĳ�����
yield���أ�
Эͬ����������У�
���ʹ�õ�Эͬ�������������ɺ�������� resume�����������cannot resume dead coroutine
resume��yield�����ǿ��֮�����ڣ�resume���������У������ⲿ״̬�����ݣ����뵽Эͬ�����ڲ�����yield���ڲ���״̬�����ݣ����ص������С�
]]--
function foo (a)
    print("foo output      :", a)
    return coroutine.yield(2 * a)                   -- ����  2*a ��ֵ
end
 
co = coroutine.create(function (a , b)
    print("1st time output :", a, b)
    local r = foo(a + 1)

    print("2nd time output :", r)
    local r, s = coroutine.yield(a + b, a - b)      -- a��b��ֵΪ��һ�ε���Эͬ����ʱ����

    print("3rd time output :", r, s)
    return b, "End coroutine"                       -- b��ֵΪ�ڶ��ε���Эͬ����ʱ����
end)

print("1st main        :", coroutine.resume(co, 1, 10))      -- 1 10       2       true   4  (resume�����ɹ�����true)
print("----------")
print("2nd main        :", coroutine.resume(co, "r"))        -- r                  true   11 -9
print("----------")
print("3rd main        :", coroutine.resume(co, "x", "y"))   -- x y                true   10 End coroutine
print("----------")
print("4th main        :", coroutine.resume(co, "x", "y"))   --                    false     cannot resume dead coroutine
print("-----------------------------------------------------------------")



-- ������-����������
local newProductor

function productor()
     local i = 0
     while true do
          i = i + 1
          send(i)                    -- ����������Ʒ���͸�������
     end
end

function consumer()
     while true do
          local i = receive()        -- ������������õ���Ʒ
          print(i)
     end
end

function receive()
     local status, value = coroutine.resume(newProductor)
     return value
end

function send(x)
     coroutine.yield(x)             -- x��ʾ��Ҫ���͵�ֵ��ֵ�����Ժ󣬾͹����Эͬ����
end

-- ��������
newProductor = coroutine.create(productor)
consumer()