主动侦察

目录
  	1. 目录结构
	2. 第三方库
	3. 编译
  





1. 目录结构
.
├── external		# 使用的第三方开源项目目录
│   ├── include		# 头文件
│   └── lib			# 库
├── script			# 脚本
└── src				# 源代码
    ├── comm		# 公共功能代码
    ├── merge		# 合成模块
    ├── parser		# 分配模块
    ├── spider		# 爬虫模块
    └── test		# 测试代码

2. 第三方库
libcurl
HTTP/HTTPS库，Redhat通常都会带rpm包

openssl
SSL、加密库，Redhat通常都会带rpm包

gumbo
Google的HTML解析库，源代码库地址：https://github.com/google/gumbo-parser.git。在158上编译需要先编译一个2.65版本以上的autoconf工具，然后将autoconf工具的路径加到PATH环境变量的开头。

boost
主要为了能在158上编译通过，部分STL容器与std::regex正则库改用了boost版本

3. 编译
make [goal] [V=1]
goal可以是debug，release，help，clean。选项V=1是在编译过程中打印出详细命令，默认是输出简洁的编译信息。