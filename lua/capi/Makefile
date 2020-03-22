OBJ1=libtest.o
TARGET1=libtest.so
OBJ2=api.o tool.o color.o
TARGET2=api.out
CFLAG1=-g -Wall -llua -shared -fPIC
CFLAG2=-g -Wall -llua# -L /home/yoyu/hub/testcode/lua/capi -ltest
CC1=gcc
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
