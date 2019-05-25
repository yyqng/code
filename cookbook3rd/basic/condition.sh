x=0;
until [ $x -eq 3 ]; # [ $x -eq 3 ] is the condition
do
 let x++; echo $x;
done

x=5
if [ $x -eq 3 ];then
    echo "$x is eq 3";
elif [ $x -eq 4 ];then
    echo "$x is eq 4";
else
    echo "$x is not eq 3 or eq 4";
fi

x=3
if [ $x -lt 3 ];then
    echo "$x is lt 3";
elif [ $x -gt 3 ];then
    echo "$x is gt 3";
else
    echo "$x is eq 3";
fi

x=4
if [ $x -le 3 ];then
    echo "$x is le 3";
elif [ $x -gt 3 ];then
    echo "$x is gt 3";
fi

x=3
if [ $x -le 3 -o $x -ge 5 ];then
    echo "$x is le 3 || ge 5";
elif [ $x -gt 3 ];then
    echo "$x is 4";
fi

x=3
if [ $x -ge 3 -a $x -le 5 ];then
    echo "$x is ge 3 and le 5";
elif [ $x -lt 3 ];then
    echo "$x is lt 4";
elif [ $x -gt 5 ];then
    echo "$x is gt 5";
fi
