#!/usr/bin/env python3
# -*- coding: utf-8 -*-

classmates = ('Michael', 'Bob', 'Tracy')
print('classmates =', classmates)
print('len(classmates) =', len(classmates))
print('classmates[0] =', classmates[0])
print('classmates[1] =', classmates[1])
print('classmates[2] =', classmates[2])
print('classmates[-1] =', classmates[-1])

# cannot modify tuple:
# classmates[0] = 'Adam'  ###wrong

c = (1);                  ###是数，而不是tuple
print(c)


c2 = ('Michael', 'Bob', ['Tracy',"Jim"])
print('c2 =', c2)
print('len(c2) =', len(c2))
print('c2[0] =', c2[0])
print('c2[1] =', c2[1])
print('c2[-1][-2] =', c2[-1][1])
print('c2[2][1] =', c2[2][1])
c2[2][1]="Alan"
print('c2[2][1] =', c2[2][1])
