echo "Text through stdin " | cat - list.sh 
  
echo
echo "cat -s list.sh :"
cat -s list.sh 
#show tabs
echo "cat -T list.sh :"
cat -T list.sh 
#show lines
echo "cat -n list.sh :"
cat -n list.sh 
#show lines without blank
echo "cat -b list.sh :"
cat -b list.sh 
