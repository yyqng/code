#!/bin/bash

#int
n1=1; n2=1;
let sum=$[n1 + n2]    #### no use in float
let sum=$[$n1 + $n2]  #### no use in float
let sum=$((n1 + n2))  #### no use in float
let sum=`expr 1 + 1`  #### no use in float
echo $sum

let n1++;let n2++;    #### no use in float
let ++n1;let ++n2;    #### no use in float
let sum=n1+n2

let n1--;let n2--;    #### no use in float
let --n1;let --n2;    #### no use in float
let sum=n1+n2         #### no use in float
echo $sum

let sum+=4
echo $sum

#float
n1=10; n2=1.5;
echo "scale=3; $n1 * $n2" | bc
echo "obase=2; $n1" | bc
echo "obase=16; ibase=10;  $n1" | bc
echo "scale=10; sqrt($n1)" | bc
echo "$n1^$n1" | bc
