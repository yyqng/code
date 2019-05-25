ifndef V
	MAKEFLAGS += -s
endif

SUB_DIRS = algorithm  mycomm  curl  data signal  string  time  unix cpp libc proccess

all: debug

.PHONY: $(SUB_DIRS)
$(SUB_DIRS):
	@$(MAKE) -C $@ $(MAKECMDGOALS) V=$V

algorithm: mycomm
curl: mycomm
data: mycomm
signal: mycomm
string: mycomm
time: mycomm
unix: mycomm
cpp: mycomm
libc: mycomm
dyad: mycomm
proccess: mycomm
#fileio: mycomm
#spider: mycomm

.PHONY: debug
debug: $(SUB_DIRS)
	@printf "make $@ is done\n"

.PHONY: release
release: $(SUB_DIRS)
	@printf "make $@ is done\n"

.PHONY: clean
clean: $(SUB_DIRS)

