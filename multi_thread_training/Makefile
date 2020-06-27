TOP_DIR = .
TARGET = $(TOP_DIR)/main.out

include $(TOP_DIR)/vars.mk
include $(TOP_DIR)/rules.mk

# Don't create dependencies when we're doing no-deps jobs
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEP_FILES)
endif
CXXFLAGS += -Wno-sign-compare
LIBS += -pthread -lboost_thread -ljemalloc
