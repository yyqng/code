OBJ=api.o
TARGET=api.out
#INCLUDE=../lua-5.2.2/src
#LIB=../lua-5.2.2/src
CFLAG=-g -Wall -llua
CC=g++
all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ)  $(CFLAG) -o $(TARGET)

%.o:%.cpp
	$(CC) $(CFLAG) -c $< -o $@

.PHONY:clean
clean:
	rm $(TARGET) $(OBJ) -f
