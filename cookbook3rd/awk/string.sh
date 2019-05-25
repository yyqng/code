stringtest()
    if [ $1 $2 $3 ]; then
        echo $1 $2 $3
    else
        echo $1 does not $2 $3
    fi

str1="string1"
str2="string2"
op="!="              
stringtest $str1 $op $str2
op=">"              
stringtest $str1 $op $str2

str1="string"
str2="string"
op="=="              
stringtest $str1 $op $str2
#等号前后要有空格
op="="              
stringtest $str1 $op $str2

stringtest2()
    if [ $1 $2 ]; then
        echo $2 $1
    else
        echo $2 does not $1
    fi

str=""
op="-z"              
stringtest2 $op $str
str="string"
stringtest2 $op $str

str=""
op="-n"              
stringtest2 $op $str
str="string"
stringtest2 $op $str
