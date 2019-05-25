#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from def_func import my_abs
from def_func import move
import math

x = abs(100)
y = abs(-20)
print(x, y)
print('max(1, 2, 3) =', max(1, 2, 3))
print('min(1, 2, 3) =', min(1, 2, 3))
print('sum([1, 2, 3]) =', sum([1, 2, 3]))


n = my_abs(-20)
print(n)

x, y = move(100, 100, 60, math.pi / 6)
print(x, y)

# TypeError: bad operand type:
# my_abs('123')

a = my_abs
n = a(-20)
print(n)
