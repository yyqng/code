#!/bin/bash -xv
#Filename: debug.sh

for i in {1..2};
do
 set -x
 echo $i
 set +x
done
echo "Script executed"

_DEBUG=on
function DEBUG()
{
 [ "$_DEBUG" == "on" ] && $@ || :
}

for i in {1..2}
do
 DEBUG echo "I is $i"
done
