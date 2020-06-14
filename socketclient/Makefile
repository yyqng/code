P=main
OBJECTS=test.o otst.o main.o 
#CFLAGS= -g -Wall -std=gnu11 -O0 -pg
#CPPFLAGS= -g -Wall -std=gnu++0x -O0 -pg
CPPFLAGS= -g -Wall -std=c++11 -O0 -pg -pthread
CC=g++

$(P): $(OBJECTS)
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm $(P) $(OBJECTS)
