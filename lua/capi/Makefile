OBJ=ding_lib.o
CSC=sum2.c
TARGET=ding_lib.so
CFLAG=-g -Wall -llua -shared -fPIC
CC=gcc
all:$(TARGET)

#$(TARGET):$(OBJ)
$(TARGET):
	gcc sum2.c -fPIC -shared -o ding_lib.so
#	$(CC) $(OBJ)  $(CFLAG) -o $(TARGET)
#
#%.o:%.c
#	$(CC) $(CFLAG) -c $< -o $@

.PHONY:clean
clean:
	rm $(TARGET) $(OBJ) -f
