# rules for Makefile
all: debug

$(TARGET): $(OBJ_FILES)
	@printf "\e[1;33m %-16s\e[0m%s/$@\n" "linking" "`pwd`"
	g++ $(LNKFLAGS) $(LIBDIR) $^ $(LIBS) -o $@

# make debug version
.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: DEFS += -D_PKTSPY_DEBUG_
debug: $(TARGET)

# make release version
.PHONY: release
release: CFLAGS += -g -O2
release: CXXFLAGS += -g -O2
release: DEFS += -DNDEBUG
release: $(TARGET)

# clean up
.PHONY: clean
clean:
	@printf "\e[1;32m %-16s\e[0m%s\n" "cleaning" "`pwd`"
	rm -f $(TARGET) $(OBJ_FILES) $(DEP_FILES)

# create object files for c files
%.c.o: %.c
	@printf "\e[1;32m %-16s\e[0m%s/$<\n" "compiling" "`pwd`"
	gcc -c $(CFLAGS) $(INCDIR) $(DEFS) $< -o $@

# create object files for cpp files
%.cpp.o: %.cpp
	@printf "\e[1;32m %-16s\e[0m%s/$<\n" "compiling" "`pwd`"
	g++ -c $(CXX_STD) $(CXXFLAGS) $(INCDIR) $(DEFS) $< -o $@

# create dependencies for c files
%.c.d: %.c
	gcc -MM $(CFLAGS) $(INCDIR) $(DEFS) $< | sed 's/\($*\).o/\1.c.o $@/g' > $@

# create dependencies for cpp files
%.cpp.d: %.cpp
	g++ -MM $(CXX_STD) $(CXXFLAGS) $(INCDIR) $(DEFS) $< | sed 's/\($*\).o/\1.cpp.o $@/g' > $@

