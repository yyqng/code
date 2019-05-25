#!/usr/bin/env python3
# -*- coding: utf-8 -*-

print([x * x for x in range(1, 11)])
print([x * x for x in range(1, 11) if x % 2 == 0])
print([m + n for m in 'ABC' for n in 'XYZ'])

d = {'x': 'A', 'y': 'B', 'z': 'C' }
print([key + '=' + value for key, value in d.items()])

L = ['Hello', 'World18', 18, 'IBM', 'Apple']
print([s.lower() for s in L if isinstance(s, str)])
