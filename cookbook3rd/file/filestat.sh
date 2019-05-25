#!/bin/bash
# Filename: filestat.sh

if [ $# -ne 1 ];then
    echo "Usage is $0 basepath";
    exit
fi

path=$1
declare -A statarray;

while read line; do
#    echo $line
    ftype=`file -b "$line" | cut -d, -f1`
    let statarray["$ftype"]++;
done < <(find $path -type f -print)
#done <<< "`find $path -type f -print`"

echo ============ File types and counts =============
for ftype in "${!statarray[@]}"; do
    echo $ftype : ${statarray["$ftype"]}
done

