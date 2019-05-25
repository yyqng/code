#all:main

#conf.o:conf.h conf.c 
#	gcc -c conf.c -O2 -Wall

#stack.o:stack.h stack.c 
#	gcc -c stack.c -O2 -Wall

#hash.o:hash.h hash.c 
#	gcc -c hash.c -O2 -Wall

#read.o:read.c
#	gcc -c read.c -02 -Wall

#create.o:create.c
#	gcc -c create.c -02 -Wall

#main:main.c create.c hash.c stack.c conf.c
#	gcc -o main main.c

#clean:
#	rm -f main *.o *.a

CC = gcc
CFLAGS=-Wall -O2
TARGET = main
SRCS := $(wildcard *.c) 
OBJS := $(patsubst %c, %o, $(SRCS)) 
all: $(TARGET) 
$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f *.o $(TARGET)
