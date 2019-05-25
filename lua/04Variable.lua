#!/usr/local/bin/lua

x = 11
a, b = 10, 2*x       
print(" a = ", a, "b = ", b)
a=10; b=2*x
print(" a = ", a, "b = ", b)

function f()
    return 5, 10
end

a, b = f()
print(" a = ", a, "b = ", b)
