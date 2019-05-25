#!/usr/bin/env python3
# -*- coding: utf-8 -*-

' a test module '

__author__ = 'Michael Liao'

import sys

def test():
    args = sys.argv
    print("Sys.path", sys.path)
    print('__name__: %s' % __name__)
    print('__author__: %s' % __author__)
    print('atgs[0]: %s!' % args[0])
    if len(args)==1:
            print('Hello, world!')
    elif len(args)==2:
        print('Hello, %s!' % args[1])
    else:
        print('Too many arguments!')

if __name__=='__main__':
    test()

