#ln -s creat.sh creat.link
ls -l | grep "^l"
readlink creat.link
#find . -type l -print
find . -type l
