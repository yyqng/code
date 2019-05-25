#ls -lh `find . -name '*.sh'`
#ls *.sh | xargs grep main
#cat example.txt | xargs
#cat example.txt | xargs -n 6
#echo "str1Xstr2Xstr3Xstr4" | xargs -d X 
#echo $*' #'
#find . -type f -name "*.txt" -print0 | xargs -0 ls -al
#find . -type f -name "*.txt" -print0 | xargs -0 wc -l
#cat args.txt | ( while read arg ; do cat $args; done )
#cat args.txt | xargs -I {} echo {}
