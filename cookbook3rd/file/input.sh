read -n 2 var
echo $var

#无回显
read -s passwd
echo $passwd
#回显
read -p "input:" passwd
echo $passwd
#时限
read -t 2 passwd
echo $passwd
#结束符
read -d ":" passwd
echo $passwd

#禁止回显
echo "Enter passwd:"
stty -echo
read passwd
echo "passwd:" $passwd
#允许回显
echo "Enter passwd:"
stty echo
read passwd
echo "passwd:" $passwd

