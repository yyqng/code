#!/bin/bash

#Filename: printf.sh


printf "%-6s %-10s %-7s\n" No Name Mark
printf "%-6s %-10s %-7.3f\n" 1 Sarath 80.3456
printf "%-6s %-10s %7.3f\n" 2 James 90.9989
printf "%-6s %-10s %7.3f\n" 3 Jeff 77.564

echo -n -e "\thello"

echo "colored txt"
echo "colored txt"
echo "colored txt"
echo -e "\e[1;30m black \e[0m"
#开启颜色
echo -e "\e[1;30m hello "
echo -e " hello"
#关闭颜色
echo -e "\e[0m"
echo -e " hello"
echo -e "\e[1;31m red \e[0m"
echo -e "\e[1;32m green \e[0m"
echo -e "\e[1;33m yellow \e[0m"
echo -e "\e[1;34m blue \e[0m"
echo -e "\e[1;35m red \e[0m"
echo -e "\e[1;36m cyan \e[0m"
echo -e "\e[1;37m white \e[0m"

echo "colored background"
echo "colored background"
echo "colored background"
echo -e "\e[1;40m black \e[0m"
echo -e "\e[1;41m red \e[0m"
echo -e "\e[1;42m green \e[0m"
echo -e "\e[1;43m yellow \e[0m"
echo -e "\e[1;44m blue \e[0m"
echo -e "\e[1;45m red \e[0m"
echo -e "\e[1;46m cyan \e[0m"
echo -e "\e[1;47m white \e[0m"

echo Count:
tput sc
# Loop for 3 seconds
for count in `seq 2 4`
do
 tput rc
 tput ed
 echo -n "hello" $count
 sleep 1
done
