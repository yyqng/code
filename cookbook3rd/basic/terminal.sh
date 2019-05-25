#!/bin/bash
#终端行
tput lines
#终端列
tput cols
#终端名
tput longname
echo 
#移动光标到（100，100）
tput cup 100 100
#设置终端背景色 0-7
tput setb 7
echo "hello"
tput setb 0
echo "hello"
#设置下划线起止
tput smul
tput rmul
echo "hello"
#设置文本样式为粗体
tput bold
echo "hello"
#删除从当前光标位置到行尾的所有内容
tput ed
echo "hello"
