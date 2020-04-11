P=main.out
OBJECTS=intp2d.o intp3d.o tool.o main.o
CPPFLAGS= -g -Wall -O0 -pg
#CPPFLAGS= -g -Wall -std=gnu11 -O0 -pg
#LDLIBS=`pkg-config --libs gsl`
LDLIBS=-lm
CC=g++

$(P): $(OBJECTS)
	g++ *.o -o main.out

.PHONY: clean
clean:
	-rm $(P) $(OBJECTS)
