P=test
OBJECTS=test.o
CFLAGS= -g -Wall -std=gnu11 `pkg-config --cflags gsl` -O0
LDLIBS=`pkg-config --libs gsl`
#LDLIBS=-lgsl -lgslcblas -lm
CC=cc

$(P): $(OBJECTS)

.PHONY: clean
clean:
	-rm $(P) $(OBJECTS)
