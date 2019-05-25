#md5 和sha1不再安全
#md5sum args.txt > args.md5
#md5sum sum.txt > sum.md5
#sha1sum args.txt > args.sh1
#sha1sum sum.txt > sum.sh1
#
#md5sum -c args.md5
#md5sum -c sum.md5
#sha1sum -c args.sh1
#sha1sum -c sum.sh1

#md5deep -rl /root/note/shell/cookbook3rd/awk > awk.md5
#md5sum -c awk.md5

#bcrypt和sha512sum
sha512sum args.txt > args.sh512
sha512sum -c args.sh512


#加盐散列
openssl passwd -1 -salt saltstri password_string__

