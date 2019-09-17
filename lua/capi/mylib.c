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

static int l_sin (lua_State *L) {
    double d = lua_tonumber(L, 1); /* get argument */
    lua_pushnumber(L, sin(d)); /* push result */
    return 1; /* number of results */
}
 
static const struct luaL_Reg mylib[] = {
    {"sum" , sum},
    {"l_sin" , l_sin},
    {NULL, NULL}
};
 
int luaopen_mylib(lua_State *L){
    luaL_newlib(L, mylib); // 5.2
    return 1;
}
