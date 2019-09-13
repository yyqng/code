OBJ=api.o
TARGET=api.out
CFLAG=-llua
CC=gcc

$(TARGET):$(OBJ)
	$(CC) $(OBJ) $(CFLAG) -o $(TARGET)

%.o:%.c
	$(CC) -c $< -o $@

.PHONY:clean
clean:
	rm $(OBJ) $(TARGET) -f
