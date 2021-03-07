OBJ1=libtest.o libtool.o
#OBJ1=libtool.o
TARGET1=libtest.so
#TARGET1=libtool.so
OBJ2=api.o color.o
TARGET2=api.out
CFLAG1=-g -Wall -llua -shared -fPIC #-std=c++11
#CFLAG2=-g -Wall -llua -ldl#-std=c++11 
CFLAG2=-g -Wall -llua -lm -ldl -ltest -fPIC #-std=c++11
CC1=gcc
#CC1=g++
CC2=g++
all:$(TARGET1) $(TARGET2)

$(TARGET1):$(OBJ1)
	$(CC1) $(OBJ1)   $(CFLAG1) -o $(TARGET1)
$(TARGET2):$(OBJ2)
	$(CC2) $(OBJ2)   $(CFLAG2) -o $(TARGET2)

%.o:%.c
	$(CC1) $(CFLAG1) -c $< -o $@
%.o:%.cpp
	$(CC2) $(CFLAG2) -c $< -o $@

.PHONY:clean
clean:
	rm $(TARGET1) $(OBJ1) -f
	rm $(TARGET2) $(OBJ2) -f
