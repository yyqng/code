#!/usr/bin/env python3
# -*- coding: utf-8 -*-

print('The quick brown fox', '\"jumps \t over\"', 'the lazy dog')
print(300)
print(100 + 200)
print('100 + 200 =', 100 + 200)
print('''line001
line002
line003''')
print(ord('A'))
print(ord('中'))
print(chr(66))
print(chr(25991))
print('\u4e2d\u6587')

#bytes : utf-8 ascii 
#str   : 内存中Unicode -> 磁盘上或网络上：bytes
s = 'AB'.encode('ascii')                        #str(Unicode) -> bytes(ascii)
print(s)
s = 'ABC'.encode('utf-8')                       #str(Unicode) -> bytes(ascii)
print(s)
s = '中文'.encode('utf-8')                      #str(Unicode) -> bytes(utf-8)
print(s)
#s = '中文'.encode('ascii') ---wrong
#print(s)
s = b'ABCD'.decode('ascii')                     #(bytes)ascii -> str(Unicode)
print(s)
s = b'\xe4\xb8\xad\xe6\x96\x87'.decode('utf-8') #(bytes)ascii -> str(utf-8)
print(s)

print("format %% %s %2d %02d %.2f" %("word", 1, 3, 13.1415))
