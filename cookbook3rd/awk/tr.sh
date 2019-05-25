#echo "Hello Who Is This 1234" | tr 'A-Z1-9' 'a-z987'
#echo "Hello Who Is This 1234" | tr 'A-Z1-9' 'a-z987654321'
#echo "Hello Who Is This 1234" | tr -d '0-9'
#echo "Hello Who Is This 1234 step" | tr -d -c '0-9\n'
#echo "Hello Who Is This 1234 step" | tr -c '0-9\n' ' '
#echo "Hello Who    Is This 1234 step .       !!" | tr -s ' '
#cat args.txt | tr -s '\n'
#cat sum.txt | echo $[ $(tr '\n' '+' ) 0 ]
#cat sum.txt | echo $[ 1+2+3+0 ]
#cat args.txt | tr -s '\n' | tr -d [a-z] | echo "total : $[$( tr '\n' '+' ) 0 ]"
#cat args.txt | tr '[:lower:]' '[:upper:]'
#cat args.txt | tr '[:alnum:]' ' '
#cat args.txt | tr '[:digit:]' ' '
#cat args.txt | tr '[:print:]' ' '
#cat args.txt | tr '[:graph:]' ' '
cat args.txt | tr '[:space:]' ' '
