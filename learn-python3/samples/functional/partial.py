#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

int2 = functools.partial(int, base=2)
int3 = functools.partial(int, base=3)

print('100=', int2('100'))
print('101=', int2('101'))

print('100=', int2('100', base=8))
print('101=', int2('101', base=8))

print('100=', int( '100', 3))
print('100=', int3('100'))
