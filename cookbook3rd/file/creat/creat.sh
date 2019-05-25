for name in {1..10}.txt
do
    touch -d "Fri Jun 25 20:50:14 IST 1999" $name
    touch -d "Fri Jun 21 1999" $name
#    touch -a $name
#    touch -m $name
done

ls -l
rm -rf *.txt
file creat.sh
file -b creat.sh
