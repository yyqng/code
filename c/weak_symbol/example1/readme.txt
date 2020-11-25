$ gcc -o weakstrong strong.c symbol_weak.c
$ ./weakstrong
output:  strong

when strong.c is not linked£¬use weak symbol in symbol_weak.c to replace strong symbol in strong.c
$ gcc -o weakstrong symbol_weak.c
$ ./weakstrong
output:  symbol_weak