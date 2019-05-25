#!/usr/bin/env python3
# -*- coding: utf-8 -*-

L = ['Michael', 'Sarah', 'Tracy', 'Bob', 'Jack']

print('L =', L[:])
print('L[0:3] =', L[0:3])
print('L[:3] =', L[:3])
print('L[1:3] =', L[1:3])
print('L[-2:] =', L[-2:])

R = list(range(100))
print('R =', R[:])
print('R[:10] =', R[:10])
print('R[-10:] =', R[-10:])
print('R[10:20] =', R[10:20])
print('R[:10:2] =', R[:10:2])
print('R[::5] =', R[::5])

T = ('Michael', 'Sarah', 'Tracy', 'Bob', 'Jack')

print('T =', T[:])
print('T[0:3] =', T[0:3])
print('T[:3] =', T[:3])
print('T[1:3] =', T[1:3])
print('T[-2:] =', T[-2:])

print('S =', ('Michael', 'Sarah', 'Tracy', 'Bob', 'Jack') [:])
print('S[0:3] =', ('Michael', 'Sarah', 'Tracy', 'Bob', 'Jack') [0:3])
print('S[:3] =',  ('Michael', 'Sarah', 'Tracy', 'Bob', 'Jack') [:3])
print('S[1:3] =', ('Michael', 'Sarah', 'Tracy', 'Bob', 'Jack') [1:3])
print('S[-2:] =', ('Michael', 'Sarah', 'Tracy', 'Bob', 'Jack') [-2:])
