sort ../data/A.txt -o ../data/A.txt
sort ../data/B.txt -o ../data/B.txt
#echo "comm A.txt B.txt:"
#comm ../data/A.txt ../data/B.txt  
#echo "A-B diffrence set :"
#comm ../data/A.txt ../data/B.txt -2 -3
#echo "B-A diffrence set :"
#comm ../data/A.txt ../data/B.txt -1 -3

echo "sort B.txt C.txt | comm - A.txt:"
sort ../data/C.txt ../data/B.txt | comm - ../data/A.txt 
