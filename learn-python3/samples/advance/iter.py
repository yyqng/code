#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import Iterable, Iterator

def g():
    yield 1
    yield 2
    yield 3

#print('Iterable? [1, 2, 3]:', isinstance([1, 2, 3], Iterable))
#print('Iterator? [1, 2, 3]:', isinstance([1, 2, 3], Iterator))
#print('Iterator? iter([1, 2, 3]):', isinstance(iter([1, 2, 3]), Iterator))
#print('Iterable? \'abc\':', isinstance('abc', Iterable))
#print('Iterator? \'abc\':', isinstance('abc', Iterator))
#print('Iterable? 123:', isinstance(123, Iterable))
#print('Iterator? 123:', isinstance(123, Iterator))
#print('Iterable? g():', isinstance(g(), Iterable))
#print('Iterator? g():', isinstance(g(), Iterator))


# iter list:
#print('for x in [6, 7, 8, 9, 10]:')
#for x in [6, 7, 8, 9, 10]:
#    print(x)
#
#print('for x in iter([6, 7, 8, 9, 10]):')
#for x in iter([6, 7, 8, 9, 10]):
#    print(x)

#print('next():')
#it = iter([1, 2, 3, 4, 5])
#print(next(it))
#print(next(it))
#print(next(it))
#print(next(it))
#print(next(it))

#d = {'a': 1, 'b': 2, 'c': 3}
#
## iter each key:
#print('iter key:', d)
#for k in d.keys():
#    print('key:', k)
#
## iter each value:
#print('iter value:', d)
#for v in d.values():
#    print('value:', v)
#
## iter both key and value:
#print('iter item:', d)
#for k, v in d.items():
#    print('item:', k, v)
#
## iter list with index:
#print('iter enumerate([\'A\', \'B\', \'C\']')
#for i, value in enumerate(['A', 'B', 'C']):
#    print(i, value)
#
## iter complex list:
#print('iter [(1, 1), (2, 4), (3, 9)]:')
#for x, y in [(1, 1), (2, 4), (3, 9)]:
#    print(x, y)
