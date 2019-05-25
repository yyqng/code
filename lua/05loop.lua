#!/usr/local/bin/lua

i = 0
print("Before whlie: i = ", i)
while( i < 3 )
do
   print(" i = ", i)
   i = i + 1
end

print("Before for: i = ", i)
for i = 0, 6, 2 do
   print(" i = ", i)
   i = i + 1
end

print("Before repeat: i = ", i)
repeat
   print(" i = ", i)
   i = i - 1
until( i == 0 )

print("Before if: i = ", i)
if( i > 0 )
then
   print(" i > 0 ")
elseif( i < 0 )
then
   print(" i < 0 ")
else
   print(" i == 0 ")
end

