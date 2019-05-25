#sort args2.txt args.txt > sorted.txt
#sort args2.txt args.txt -o sorted2.txt
#sort -n args.txt
#sort -r args.txt
#sort -M args.txt
#sort -m sorted2.txt sorted.txt
#sort -m sorted2.txt sorted.txt | uniq

sort -C sorted.txt
if [ $? -eq 0 ]; then
    echo sorted.txt sorted;
else
    echo sorted.txt unsorted;
fi

#sort -nrk 1 data.txt
#sort -nk 1 data.txt
#sort -k 2 data.txt
#sort -bk 2.3,2.4 data2.txt
sort -bk 1.3,1.4 data2.txt
#sort -bk 2.3,2.4 data2.txt
#sort -nk 1,1 data2.txt
