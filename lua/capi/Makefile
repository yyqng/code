OBJ=lualib.o
CSC=sum2.c
TARGET=lualib.so
CFLAG=-g -Wall -llua -shared -fPIC
CC=gcc
all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ)   $(CFLAG) -o $(TARGET)
#	$(CC) $(OBJ)   -shared -fPIC -o $(TARGET)
#	gcc lualib.c -fPIC -shared -o lualib.so

%.o:%.c
	$(CC) $(CFLAG) -c $< -o $@

.PHONY:clean
clean:
	rm $(TARGET) $(OBJ) -f
