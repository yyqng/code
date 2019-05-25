#!/bin/bash
exec 3<input.txt
cat <&3

exec 4>output.txt
echo newline>&4
cat output.txt

exec 5>>input.txt
echo append line>&5
cat input.txt
