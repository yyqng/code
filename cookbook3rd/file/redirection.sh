#!/bin/bash
echo "test 1" >    temp.txt
echo "test 2" >>   temp.txt
ls +          2>>  temp.txt
ls .          2>>  temp.txt 1>> temp.txt
ls .          &>>  temp.txt

echo "" > out.txt
#tee: 一份副本写入文件，一份副本作为后续命令的输入: -a 追加
cat a* | tee -a temp.txt out.txt | cat -n
ls < in.txt
