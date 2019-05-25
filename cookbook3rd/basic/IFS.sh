#!/bin/bash
#Desc: Illustration of IFS

line="root:x:0:0:root:/root:/bin/bash"
oldIFS=$IFS;
IFS=":"
count=0

for item in $line;
do
 [ $count -eq 0 ] && user=$item;
 [ $count -eq 6 ] && shell=$item;
 let count++
done;
IFS=$oldIFS
echo $user\'s shell is $shell;


data="name,gender
,rollno,location"

# To read each of the item in a variable, we can use IFS.
oldIFS=$IFS
IFS=, # IFS is now a ,
#echo $oldIFS
#echo $IFS

for item in $data;
do
 echo Item: $item
done
IFS=$oldIFS

#默认的界定符
data="name  gender   rollno 
location"
for item in $data;
do
 echo Item: $item
done
