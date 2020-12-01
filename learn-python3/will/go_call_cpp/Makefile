.PHONY: clean

TARGET=go_cpp_test

$(TARGET): libfoo.a
	go build -o $(TARGET) .

libfoo.a: interface.o imp.o
	ar r $@ $^

%.o: %.cpp
	g++ -O2 -o $@ -c $^

clean:
	rm -f *.o *.so *.a $(TARGET)
