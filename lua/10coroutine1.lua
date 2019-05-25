-- 10coroutine1.lua 文件
co1 = coroutine.create(         --        // 创建 coroutine，返回 coroutine， 参数是一个函数，当和resume配合使用的时候就唤醒函数调用
    function(i)
        print( "create: function, para:", i);
    end
)
 
coroutine.resume(co1, 100)      -- 100    // 重启 coroutine ，和 create 配合使用
print( coroutine.status(co1) )  -- dead   // 查看 coroutine 的状态( dead、 suspend、 running )

print("----------")

co1 = coroutine.wrap(           --        // 创建coroutine，返回一个函数，一旦你调用这个函数，就进入coroutine，和create功能重复
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
                print(coroutine.running())     --thread:XXXXXX  // 返回正在跑的coroutine, 一个coroutine就是一个线程，当使用running的时候，就是返回一个corouting的线程号
            end
            coroutine.yield()   --          // 挂起 coroutine ，将 coroutine 设置为挂起状态，这个和 resume 配合使用能有很多有用的效果
        end
    end
)
 
coroutine.resume(co2)           --1
coroutine.resume(co2)           --2
coroutine.resume(co2)           --3
 
print(coroutine.status(co2))    -- suspended 暂停
print(coroutine.running())
 
print("-----------------------------------------------------------------")


--[[
调用resume，将协同程序唤醒,resume操作成功返回true，否则返回false；
协同程序运行；
运行到yield语句；
yield挂起协同程序，第一次resume返回；（注意：此处yield返回，参数是resume的参数）
第二次resume，再次唤醒协同程序；（注意：此处resume的参数中，除了第一个参数，剩下的参数将作为yield的参数）
yield返回；
协同程序继续运行；
如果使用的协同程序继续运行完成后继续调用 resume方法则输出：cannot resume dead coroutine
resume和yield的配合强大之处在于，resume处于主程中，它将外部状态（数据）传入到协同程序内部；而yield则将内部的状态（数据）返回到主程中。
]]--
function foo (a)
    print("foo output      :", a)
    return coroutine.yield(2 * a)                   -- 返回  2*a 的值
end
 
co = coroutine.create(function (a , b)
    print("1st time output :", a, b)
    local r = foo(a + 1)

    print("2nd time output :", r)
    local r, s = coroutine.yield(a + b, a - b)      -- a，b的值为第一次调用协同程序时传入

    print("3rd time output :", r, s)
    return b, "End coroutine"                       -- b的值为第二次调用协同程序时传入
end)

print("1st main        :", coroutine.resume(co, 1, 10))      -- 1 10       2       true   4  (resume操作成功返回true)
print("----------")
print("2nd main        :", coroutine.resume(co, "r"))        -- r                  true   11 -9
print("----------")
print("3rd main        :", coroutine.resume(co, "x", "y"))   -- x y                true   10 End coroutine
print("----------")
print("4th main        :", coroutine.resume(co, "x", "y"))   --                    false     cannot resume dead coroutine
print("-----------------------------------------------------------------")



-- 生产者-消费者问题
local newProductor

function productor()
     local i = 0
     while true do
          i = i + 1
          send(i)                    -- 将生产的物品发送给消费者
     end
end

function consumer()
     while true do
          local i = receive()        -- 从生产者那里得到物品
          print(i)
     end
end

function receive()
     local status, value = coroutine.resume(newProductor)
     return value
end

function send(x)
     coroutine.yield(x)             -- x表示需要发送的值，值返回以后，就挂起该协同程序
end

-- 启动程序
newProductor = coroutine.create(productor)
consumer()