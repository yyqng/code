P=main.out
OBJECTS=intp2d.o intp3d.o tool.o main.o
CFLAGS= -g -Wall -std=gnu11 -O0 -pg
#LDLIBS=`pkg-config --libs gsl`
LDLIBS=-lm
CC=cc

$(P): $(OBJECTS)

.PHONY: clean
clean:
	-rm $(P) $(OBJECTS)
