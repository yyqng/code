#!/usr/bin/lua
mytable = {}           -- init table
mytable[1]= "Lua"      --  
mytable = nil          -- remove

fruits = {"banana","orange","apple"}
print( fruits );
print(   '1. table.concat(fruits)                ->',      table.concat(fruits) );                  --> bananaorangeapple
print(   '2. table.concat(fruits, ", ")          ->',      table.concat(fruits, ", ") );            --> banana, orange, apple
print(   '3. table.concat(fruits, ", ", 2, 3)    ->',      table.concat(fruits, ", ", 2, 3) );      --> orange, apple
table.insert(fruits,"mango")
print(   '4. table.concat(fruits, ", ")          ->',      table.concat(fruits, ", ") );            --> banana, orange, apple, mango
table.insert(fruits,2,"grapes")
print(   '5. table.concat(fruits, ", ")          ->',      table.concat(fruits, ", ") );            --> banana, grapes, orange, apple, mango
table.remove(fruits)
print(   '6. table.concat(fruits, ", ")          ->',      table.concat(fruits, ", ") );            --> banana, grapes, orange, apple
table.sort(fruits) 
print(   '7. table.concat(fruits, ", ")          ->',      table.concat(fruits, ", ") );            --> apple, banana, grapes, orange

for k, v in pairs(fruits) do
    print(k, v)    
end


function square(max,i)
   if i<max
   then
      i = i+1 
   return i, i*i 
   end 
end

for i,n in square,3,0
do
   print(i,n)
end


local tab= { [1] = "a", [3] = "b", [4] = "c" } 
for i,v in pairs(tab) do
    print( tab[i] ) 
end 

for i,v in ipairs(tab) do
    print( tab[i] ) 
end
