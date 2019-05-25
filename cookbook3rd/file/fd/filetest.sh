filetest()
    if [ $1 $2 ]; then
        echo $2 $1
    else
        echo $2 does not $1
    fi

####正常文件名或路径
pa="-f"              
fpath="/etc/pass"
filetest $pa $fpath
fpath="/etc/passwd"
filetest $pa $fpath

####可执行
pa="-x"
fpath="/etc/pass"
filetest $pa $fpath
fpath="/etc/passwd"
filetest $pa $fpath

####目录
pa="-d"
fpath="/etc"
filetest $pa $fpath
fpath="/etc/passwd"
filetest $pa $fpath

####正常文件名或路径
pa="-e"
fpath="/etc/pass"
filetest $pa $fpath
fpath="/etc/passwd"
filetest $pa $fpath

####字符设备
pa="-c"
fpath="/dev/dsk"
filetest $pa $fpath
fpath="/dev/rdsk"
filetest $pa $fpath

####块设备
pa="-b"
fpath="/dev/dsk"
filetest $pa $fpath
fpath="/etc/ds"
filetest $pa $fpath

####可写
pa="-w"
fpath="/etc/pass"
filetest $pa $fpath
fpath="/etc/passwd"
filetest $pa $fpath

####可读
pa="-r"
fpath="/etc/pass"
filetest $pa $fpath
fpath="/etc/passwd"
filetest $pa $fpath

####符号链接
pa="-L"
fpath="/etc/pass"
filetest $pa $fpath
fpath="/etc/passwd"
filetest $pa $fpath
