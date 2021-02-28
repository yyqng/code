#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
int main (void) {
    lua_State *L = luaL_newstate();   //打开 Lua
    luaL_openlibs(L);                 //打开标准库
    char buff[256];
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        int error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }
    lua_close(L);
    return 0;
}
