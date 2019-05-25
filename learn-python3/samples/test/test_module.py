#!/usr/bin/env python3
# -*- coding: utf-8 -*-

' test '

#export PYTHONPATH=/root/note/pro/learn-python3/samples/module
import sys
sys.path.append("../module")
import hello

if __name__=='__main__':
    print("Begin test")
    hello.test()
    print("End test")

