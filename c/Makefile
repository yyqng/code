TARGET = test.out

CXXFLAGS= -g -Wall -std=gnu11 `pkg-config --cflags gsl` -O0 -pg #-quiet#-Werror
LDLIBS=`pkg-config --libs gsl`

CXX_STD = -std=c++11
CFLAGS = -Wall -Werror #-quiet
CXXFLAGS += -Wno-sign-compare
LNKFLAGS = 
C_FILES = $(wildcard *.c)
CXX_FILES = $(wildcard *.cpp)
DEP_FILES = $(patsubst %.c,%.c.d,$(C_FILES)) $(patsubst %.cpp,%.cpp.d,$(CXX_FILES))
OBJ_FILES = $(DEP_FILES:.d=.o)
NODEPS = clean

#all: release
all: debug

$(TARGET): $(OBJ_FILES)
	@printf "\e[1;33m %-16s\e[0m%s/$@\n" "linking" "`pwd`"
	g++ $(LNKFLAGS) $(LIBDIR) $^ $(LIBS) -o $@

.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: DEFS += -D_PKTSPY_DEBUG_
debug: $(TARGET)

.PHONY: release
release: CFLAGS += -o3
release: CXXFLAGS += -o3
release: DEFS += -DNDEBUG
release: $(TARGET)

.PHONY: clean
clean:
	@printf "\e[1;32m %-16s\e[0m%s\n" "cleaning" "`pwd`"
	rm -f $(TARGET) $(OBJ_FILES) $(DEP_FILES)

%.c.o: %.c
	@printf "\e[1;32m %-16s\e[0m%s/$<\n" "compiling" "`pwd`"
	gcc -c $(CFLAGS) $(INCDIR) $(DEFS) $< -o $@

%.cpp.o: %.cpp
	@printf "\e[1;32m %-16s\e[0m%s/$<\n" "compiling" "`pwd`"
	g++ -c $(CXX_STD) $(CXXFLAGS) $(INCDIR) $(DEFS) $< -o $@

%.c.d: %.c
	gcc -MM $(CFLAGS) $(INCDIR) $(DEFS) $< | sed 's/\($*\).o/\1.c.o $@/g' > $@

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEP_FILES)
endif

LIBS += -pthread -lboost_thread -lboost_system -ljemalloc -lboost_regex -lm
#LIBS += -lm -lboost_regex lib1.so lib2.so
