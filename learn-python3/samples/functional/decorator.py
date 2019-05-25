#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

def log(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        print('begin call %s():' % func.__name__)
        func(*args, **kw)
        print('after call %s():' % func.__name__)
    return wrapper

@log
def now():
    print('2015-3-25')

now()
#print(log(now))
#print(now.__name__)

def logger(text=""):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kw):
            print('%s %s():' % (text, func.__name__))
            return func(*args, **kw)
        return wrapper
    return decorator

@logger()
#@logger('DEBUG')
def today():
    print('2015-3-25')

today()
#print(today.__name__)
