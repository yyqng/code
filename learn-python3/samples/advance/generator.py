#!/usr/bin/env python3
# -*- coding: utf-8 -*-

g = (x * x for x in range(10))
#print(g)
#print(next(g))
#print(next(g))
#print(next(g))
#print(next(g))
#print(next(g))
#print(next(g))
#print(next(g))
#print(next(g))
#print(next(g))
#print(next(g))
#for x in g:
#    print(x)

def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'

f = fib(6)
print('fib(6):', f)
#for x in f:
#    print(x)
#for n in fib(6):
#    print(n)

def odd():
    print('step 1')
    yield 1
    print('step 2')
    yield (3)
    print('step 3')
    yield (5)

#o = odd()
#print(next(o))
#print(next(o))
#print(next(o))
#print(next(o)) #####wrong

# call generator manually:
g = fib(5)
while 1:
    try:
        x = next(g)
        print('g:', x)
    except StopIteration as e:
        print('Generator return value:', e.value)
        break

