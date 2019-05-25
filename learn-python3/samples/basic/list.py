#!/usr/bin/env python3
# -*- coding: utf-8 -*-

classmates = ['Michael', 'Bob', 'Tracy']
print('classmates =', classmates)
print('len(classmates) =', len(classmates))
print('classmates[0] =', classmates[0])
print('classmates[1] =', classmates[1])
print('classmates[2] =', classmates[2])
print('classmates[-1] =', classmates[-1])
print('classmates[-2] =', classmates[-2])
print('classmates[-3] =', classmates[-3])
classmates.pop()
print('classmates =', classmates)
classmates.append("testappend")
print('classmates =', classmates)
classmates.insert(1,"testinsert")
print('classmates =', classmates)
classmates.pop(1)
print('classmates =', classmates)

c = ['Michael', 123, True, ["asp", "php"]]
print('c =', c)
print('c =', c[3][0])

classmates.sort()
print('classmates =', classmates)
