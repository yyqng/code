OBJ=api.o
TARGET=api.out
INCLUDE=../lua-5.2.2/src
LIB=../lua-5.2.2/src
CFLAG=-I $(INCLUDE) -L $(LIB) -llua
CC=g++

$(TARGET):$(OBJ)
	$(CC) $(OBJ) $(CFLAG) -o $(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $< -o $@

.PHONY:clean
clean:
	rm $(OBJ) $(TARGET) -f
