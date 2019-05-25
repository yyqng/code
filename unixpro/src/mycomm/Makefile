TOP_DIR = ../..
TARGET = $(TOP_DIR)/lib/libmycomm.so

include $(TOP_DIR)/vars.mk
include $(TOP_DIR)/rules.mk

# Don't create dependencies when we're doing no-deps jobs
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEP_FILES)
endif

CFLAGS += -fPIC -Wno-sign-compare -Wno-narrowing -Wno-strict-aliasing -Wno-unused-but-set-variable
CXXFLAGS += -fPIC -Wno-sign-compare -Wno-narrowing -Wno-strict-aliasing -Wno-unused-but-set-variable
LNKFLAGS += -shared
INCDIR += -I$(TOP_DIR)/src/include
LIBDIR += -L$(TOP_DIR)/lib
LIBS += -lpthread -lssl
#LIBS += -lpthread -lrt -lcrypto -lboost_regex -lgumbo
