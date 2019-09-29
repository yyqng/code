#include "tool.h"

void stackDump(lua_State *L){
    int i;
    int top = lua_gettop(L);      //Return the number of elements.
    for(i = 1; i <= top; i++){
        int t = lua_type(L, i);
        switch(t){
            case LUA_TBOOLEAN:
                printf(lua_toboolean(L, i) ? "true":"false");
                break;
            case LUA_TNUMBER:
                printf("%g", lua_tonumber(L, i));
                break;
            case LUA_TSTRING:
                printf("'%s'", lua_tostring(L, i));
                break;
            default:
                printf("%s", lua_typename(L, t));
                break;
        }
        printf(" ");
    }
    printf("\n");
}

void error (lua_State *L, const char *fmt, ...) {
    va_list vl;
    va_start(vl, fmt);
    vfprintf(stderr, fmt, vl);
    va_end(vl);
    lua_close(L);
    exit(EXIT_FAILURE);
    printf ("won't print\n");
}

/* call a function `f' defined in Lua */
double tool_callf (lua_State *L, double x, double y) {
    /* push functions and arguments */
    lua_getglobal(L, "f"); /* function to be called */
    lua_pushnumber(L, x); /* push 1st argument */
    lua_pushnumber(L, y); /* push 2nd argument */
    /* do the call (2 arguments, 1 result) */
    if (lua_pcall(L, 2, 1, 0) != 0)
        error(L, "error running function `f': %s",
    lua_tostring(L, -1));
    /* retrieve result */
    if (!lua_isnumber(L, -1))
        error(L, "function `f' must return a number");
    double z = lua_tonumber(L, -1);
    lua_pop(L, 1); /* pop returned value */
    return z;
}
