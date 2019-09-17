OBJ=mylib.o
CSC=sum2.c
TARGET=mylib.so
CFLAG=-g -Wall -llua -shared -fPIC
CC=gcc
all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ)   $(CFLAG) -o $(TARGET)
#	$(CC) $(OBJ)   -shared -fPIC -o $(TARGET)
#	gcc mylib.c -fPIC -shared -o mylib.so

%.o:%.c
	$(CC) $(CFLAG) -c $< -o $@

.PHONY:clean
clean:
	rm $(TARGET) $(OBJ) -f
