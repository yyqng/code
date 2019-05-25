ls | cat -n > out.txt

cmd="ls|cat -n"
cmd_output=`ls |cat -n`
echo "ls|cat -n:"$cmd_output

out=`cat in.txt`
echo cat in.txt:$out

out="$(cat in.txt)"
echo cat in.txt:$out
