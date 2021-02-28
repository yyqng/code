OBJ=test.o
TARGET=a.out
#CFLAG=-g -Wall -llua -shared -fPIC #-std=c++11
CFLAG=-g -Wall -llua -lm -ldl#-std=c++11 # -L /home/yoyu/hub/testcode/lua/capi -ltest
CC=gcc
#CC=g++
CC2=g++
all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ)   $(CFLAG) -o $(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $< -o $@

.PHONY:clean
clean:
	rm $(TARGET) $(OBJ) -f
