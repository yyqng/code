$ gcc -o weakstrong weak.c
$ ./weakstrong
output: weak.c.symbol1

when link strong.c£¬use strong symbol in strong.c to replace weak symbol in weak.c
$ gcc -o weakstrong weak.c strong.c
$ ./weakstrong
output: strong.c.symbol1