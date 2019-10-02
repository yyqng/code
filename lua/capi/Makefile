OBJ=lib.o
CSC=sum2.c
TARGET=lib.so
CFLAG=-g -Wall -llua -shared -fPIC
CC=gcc
all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ)   $(CFLAG) -o $(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $< -o $@

.PHONY:clean
clean:
	rm $(TARGET) $(OBJ) -f
