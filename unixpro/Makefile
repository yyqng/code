ifndef V
	MAKEFLAGS += -s
endif

SUB_DIRS = algorithm

all: debug

.PHONY: $(SUB_DIRS)
$(SUB_DIRS): output_dirs
	@$(MAKE) -C $@ $(MAKECMDGOALS) V=$V

.PHONY: debug
debug: $(SUB_DIRS)

.PHONY: release
release: $(SUB_DIRS)

.PHONY: clean
clean: $(SUB_DIRS)

.PHONY: help
help:
	@echo "    make          - make debug version"
	@echo "    make help     - display this help information"
	@echo "    make debug    - make debug version"
	@echo "    make release  - make release version"
	@echo "    make clean    - clean object files, dpendencies and targets"

.PHONY: output_dirs
output_dirs:
	@mkdir -p bin
	@mkdir -p lib
