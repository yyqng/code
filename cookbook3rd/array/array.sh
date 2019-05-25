#!/bin/bash
#普通数组：整数作为字符索引
#关联数组：字符串作为字符索引(bash 4.0及以上)

array_var=(test0 test1 test2 test3)
echo ${array_var[0]}
index=2
echo ${array_var[$index]}
echo ${array_var[*]}
echo ${array_var[@]}
echo ${#array_var[*]}
echo ${#array_var[@]}

declare -A ass_array
ass_array=([index1]=val1 [index2]=val2)
ass_array[index3]=val3
ass_array[index4]=val4
echo "${ass_array[index1]}"
echo "${ass_array[*]}"
echo "${ass_array[@]}"
echo "${!ass_array[*]}"
echo "${!ass_array[@]}"
echo "${#ass_array[*]}"
echo "${#ass_array[@]}"
