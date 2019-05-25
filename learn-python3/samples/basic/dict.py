#!/usr/bin/env python3
# -*- coding: utf-8 -*-

d = {
    'Michael': 95,
    'Bob': 75,
    'Tracy': 85
}
print('d =', d)
print('d[\'Michael\'] =', d['Michael'])
print('d[\'Bob\'] =', d['Bob'])
print('d[\'Tracy\'] =', d['Tracy'])
print('d.get(\'Bob\', -2) =', d.get('Bob', -2))
print('d.get(\'Thomas\', -2) =', d.get('Thomas', -2))
d["Tracy"]=5
print('d[\'Tracy\'] =', d['Tracy'])
d["Jim"]=5
print('d[\'Jim\'] =', d['Jim'])
print('tom' in d)
print('Jim' in d)
print('d.pop("Michael") = ', d.pop('Michael'))
print('d =', d)
