#find . -print
#find . -print0
#find . -name  '*q.sh' -print
#find . -iname '*Q.sh' -print
#find . -iname 'egrep*' -print
#find . \( -iname 'egrep*' -o -iname '*q.sh' \) -print
#find . \( -iname 'egrep*' -and -iname '*.sh' \) -print
#find /root/note/shell \( -path '*cookbook3rd*' -and -path '*awk*' \) \( -iname 'egrep*' -and -iname '*.sh' \) -print
#find . -iregex '.*\(\.py\|\.sh\)$' 
#find . ! -iname '*.sh' -print
#find /root/note/ -maxdepth 2 -name '*.sh' -print
#find -L /root/note/ -name '*.sh' -print 2> /dev/null
#find /root/note/ -mindepth 4 -name '*.sh' -print
#find /root/note/ -mindepth 4 -type d -print
#find /root/note/ -mindepth 4 -type f -print
#find /root/note/ -mindepth 4 -type l -print
#find /root/note/ -mindepth 4 -type f -atime -7 -print
#find /root/note/ -mindepth 4 -type f -atime 7 -print
#find /root/note/ -mindepth 4 -type f -atime +7 -print
#find /root/note/ -mindepth 4 -type f -mtime -1 -print
#find /root/note/ -mindepth 4 -type f -amin -600 -print
#find /root/note/ -mindepth 4 -type f -amin -17 -print
#find /root/note/ -mindepth 4 -type f -size +300k
#find /root/note/ -mindepth 4 -type f -size +1M
#find /root/note/ -mindepth 4 -type f -size 3k
#find /root/note/ -mindepth 4 -type f -size +1G
#find /root/note/shell/cookbook3rd/awk -type f -perm 555
#find . -type f -user yuyq
#find . -type f -user 1000
#find . -type f -name "*.tmp" -delete
#find . -type f -name "*.c" -exec cat {} \;> all_c_cfiles.txt
#find . -type f -name "*.c" -exec cat {} \;> all_c_cfiles.txt
#find . -type f -name "*.c" -exec cat {} > all_c_cfiles.txt \;
#find . -type f -name "*.c" -exec cat {} >> all_c_cfiles.txt +
#find . -type f -mmin -10 -name "*.sh" -exec printf "Text file: %s\n" {} \; 
#find /root/note/shell/cookbook3rd/ -name 'README*' -type f -prune -o -print
