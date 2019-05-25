file_sh="creatfd.sh"
name=${file_sh%.*}  #非贪婪的:更适合
echo File name is: $name
name=${file_sh%%.*} #贪婪的，从右向左匹配尽可能多
echo File name is: $name

file_ext="cd.sh"
name=${file_sh#*.}
echo File ext is: $name
file_ext="cd.sh"
name=${file_sh##*.}  #贪婪的:更适合
echo File ext is: $name
