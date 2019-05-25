#split -b 10 cd.sh -d -a 5
#split -b 10 cd.sh
#split -b 10 cd.sh -d -a 4 /tmp/split_file_10char
#split -l 2 cd.sh -a 4 /tmp/split_file_2line
csplit cd.sh /pwd/ -n 2 -s {*} -f /tmp/split_cd -b "%02d.log"
