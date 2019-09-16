#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
 
static int sum(lua_State *L){
    double d1 = luaL_checknumber(L, 1);
    double d2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, d1+d2);
    return 1;
}
 
static const struct luaL_Reg lualib[] = {
    {"sum" , sum},
    {NULL, NULL}
};
 
int luaopen_lualib(lua_State *L){
    luaL_newlib(L, lualib); // 5.2
    //luaL_register(L, "lualib",ding); // lua 5.1
    return 1;
}