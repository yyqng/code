# variables for Makefile 

# 包含目录
INCDIR =

# 库目录
LIBDIR =

# 库
LIBS =

# 宏定义
DEFS =

# C++标准
CXX_STD = -std=c++0x

# C文件编译选项
CFLAGS = -Wall -Werror

# C++文件编译选项
CXXFLAGS = -Wall #-Werror

# 链接选项
LNKFLAGS = 

# C源文件 
C_FILES = $(wildcard *.c)

# C++源文件
CXX_FILES = $(wildcard *.cpp)

# 依赖文件
DEP_FILES = $(patsubst %.c,%.c.d,$(C_FILES)) $(patsubst %.cpp,%.cpp.d,$(CXX_FILES))

# 目标文件
OBJ_FILES = $(DEP_FILES:.d=.o)

# 将不需要生成依赖的任务添加到NODEPS中
NODEPS = clean
