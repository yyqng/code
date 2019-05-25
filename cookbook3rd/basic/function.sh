#!/bin/bash

fname()
{
 echo $1, $2; #Accessing arg1 and arg2
# echo "$1" "$2" "$3"
 echo "$@"; # Printing all arguments as list at once
# echo "$1c$2c$3" #c是IFS的第一个字符
 echo "$*"; # Similar to $@, but arguments taken as single entity
 echo "$#";
 return -1; # Return value
}

fname arg1 arg2 arg3

showArgs()
{
    for i in `seq 1 $#`
    do 
    echo $i is $1
    shift
    done
    return 0; # Return value
}

showArgs arg1 arg2 arg3

