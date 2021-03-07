#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
int dofile(const char *filename) {
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
//        error(L, "luaL_dofile || lua_pcall: %s", lua_tostring(L, -1));
    }
    lua_close(L);

    return 0;
}

int testdofile(void)
{
    char filename[] = "b.lua";
    dofile(filename);
    exit(0);
}
int main (void) {
    testdofile();
    lua_State *L = luaL_newstate();   //打开 Lua
    luaL_openlibs(L);                 //打开所有的标准库
    char buff[256];
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        //1. 编译用户输入的每一行内容，并向栈中压入编译得到的函数
        //2. 从栈中弹出编译后得到的函数，并以保护模式运行
        int error = luaL_loadstring(L, buff) ||
                    lua_pcall(L, 0, 0, 0);
        //3. 错误信息处理：获取栈中的错误信息并打印，随后删除栈中的错误信息
        if (error) { 
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }
    lua_close(L);
    return 0;
}
