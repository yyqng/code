#!/usr/bin/env python3
#test
def test_001():
    print (100+200+300)

test_001()

#for
def for_001():
    for i in range(0,1):
        print (i)

#for_001()

#set
def set_002():
    aset=set();
    print (type(aset));
    b=15;
    print (type(b));
    aset.add(b);
    print (aset);

#set_002()

#str
def str_003():
    astring="        hello,nihao,see you   ";
    print (astring);
    print ("strip string:" , astring.strip());
    print ('split string:' , astring.strip().split(","))
    print ("length of string:" , len(astring.strip().split(",")))

#str_003()

#list
def list_004():
    alist=[1,2,"nihao","see you"];
    print ((alist[0:3]))
    alist[0]=5
    alist.insert(4,"end")
    print ((alist[0:6:2]))
    del(alist[4])
    print ((alist[0:100]))

#list_004();

#tuple
def tuple_005():
    atuple=(1,2,"nihao","see you");
    print (type(atuple))
    #atuple[0]=5 ------------------wrong
    #atuple.insert(4,"end")--------wrong
    print ((atuple[0:6:2]))
    #del(atuple[3])----------------wrong
    print ((atuple[0:100]))

#tuple_005();

#dict
def dict_006():
    dic = {"name":"zhangsan", "age":18, "height":172}
    print (type(dic));
    print (dic);
    del(dic["name"])
    print ((dic));
    dic["class"]=4
    print ((dic));

#dict_006();
