TOP_DIR = ../..
TARGET = $(TOP_DIR)/lib/libdatabase.so

include $(TOP_DIR)/vars.mk
include $(TOP_DIR)/rules.mk

# Don't create dependencies when we're doing no-deps jobs
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEP_FILES)
endif


CXXFLAGS += -fPIC
LNKFLAGS += -shared
INCDIR += -I$(TOP_DIR)/src/include -I$(TOP_DIR)/src/mycomm -I/u01/app/oracle/product/11.2.0/db_1/rdbms/public
LIBDIR += -L$(TOP_DIR)/lib -L/u01/app/oracle/product/11.2.0/db_1/lib -L/usr/local/oracle/instantclient_11_2

# libocci.so与C++11不兼容
DEFS += -D_GLIBCXX_USE_CXX11_ABI=0
