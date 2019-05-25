#!/bin/bash
#env
#PWD=/home/clif/ShellCookBook

#HOME=/home/clif

#SHELL=/bin/bash
# -- And many more lines
pid=`pgrep ssh`
echo $pid

prepend() { [ -d "$2" ] && eval $1=\"$2\$\{$1:+':'\$$1\}\" && export $1; }
prepend TESTENV /bin
echo $TESTENV
prepend TESTENV /bin
echo $TESTENV
prepend TESTENV /home
echo $TESTENV
prepend TESTENV 
echo $TESTENV

VAL1=val1
VAL2=val2
eval VAL=\"$VAL1':'$VAL2\"
echo $VAL
