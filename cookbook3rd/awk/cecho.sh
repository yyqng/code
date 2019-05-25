#cat args.txt | xargs -n 2 ./xargs.sh
#cat args.txt | xargs ./xargs.sh
cat args.txt | xargs -I {} -n 1 ./xargs.sh -p {} -l

