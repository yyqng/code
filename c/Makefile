#gcc erf.c -o erf -lm -g -Wall -O3 -std=gnu11
P=main.out
OBJECTS=test.o
#CFLAGS = -g -Wall -O3
CFLAGS= -g -Wall -std=gnu11 `pkg-config --cflags gsl`
LDLIBS=`pkg-config --libs gsl`
#LDLIBS=-lgsl -lgslcblas -lm
CC=cc

$(P): $(OBJECTS)

.PHONY: clean
clean:
	-rm $(P) $(OBJECTS)
