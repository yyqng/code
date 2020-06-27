TOP_DIR = ..
TARGET = $(TOP_DIR)/bin/client

include $(TOP_DIR)/vars.mk
include $(TOP_DIR)/rules.mk

# Don't create dependencies when we're doing no-deps jobs
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEP_FILES)
endif

# 变量说明
# CXX_STD	C++标准，默认为-std=c++0x
# CFLAGS	C文件编译选项，debug版本默认为-Wall -g3 -O0，release版本默认为-Wall -g -O2
# CXXFLAGS	C++文件编译选项，debug版本默认为-Wall -g3 -O0，release版本默认为-Wall -g -O2
# LNKFLAGS	链接选项
# INCDIR	包含路径，-I<path>
# LIBDIR	库路径，-L<path>
# LIBS		库，-l<library>
# DEFS		宏定义，-D<macro>，debug版本默认为空，release版本默认为-DNDEBUG

# 修改编译选项示例（同时影响debug与release版本）
#CXX_STD = -std=c++11
# CFLAGS += -fPIC -other_options
CXXFLAGS += -Wno-sign-compare
# LNKFLAGS += -shared -other_options
# INCDIR += -Imy/include/dir
# LIBDIR += -Lmy/library/dir
# LIBS += -lmylib
INCDIR += -I$(TOP_DIR)/src/mycomm -I$(TOP_DIR)/src/include -I$(TOP_DIR)/src/database -I$(C_INCLUDE_PATH)
LIBDIR += -L$(TOP_DIR)/lib
LIBS += -pthread -lboost_regex -lboost_thread -lboost_system -ljemalloc# -lboost_circular_buffer
#LIBS += -lcomm -lgumbo -lboost_regex -ldatabase -locci -lclntsh -lnnz11 -lsqlite3
# DEFS += -DMY_MACRO

# debug版本添加自定义编译选项示例
# debug: CXX_STD = -std=c++11
# debug: CFLAGS += -fPIC -other_options
# debug: CXXFLAGS += -fPIC -other_options
# debug: LNKFLAGS += -shared -other_options
# debug: INCDIR += -Imy/include/dir
# debug: LIBDIR += -Lmy/library/dir
# debug: LIBS += -lmylib
# debug: DEFS += -DMY_DEBUG_MACRO

# release版本添加自定义编译选项示例
# release: CXX_STD = -std=c++11
# release: CFLAGS += -fPIC -other_options
# release: CXXFLAGS += -fPIC -other_options
# release: LNKFLAGS += -shared -other_options
# release: INCDIR += -Imy/include/dir
# release: LIBDIR += -Lmy/library/dir
# release: LIBS += -lmylib
# release: DEFS += -DMY_RELEASE_MACRO
