#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
 
static int sum(lua_State *L){
    double d1 = luaL_checknumber(L, 1);
    double d2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, d1+d2);
    return 1;
}

static int mysin (lua_State *L) {
    double d = lua_tonumber(L, 1); /* get argument */
    lua_pushnumber(L, sin(d)); /* push result */
    return 1; /* number of results */
}

#include <dirent.h>
#include <errno.h>
static int dir (lua_State *L) {
    DIR *dir;
    struct dirent *entry;
    int i;
    const char *path = luaL_checkstring(L, 1);
    /* open directory */
    dir = opendir(path);
    if (dir == NULL) {
        lua_pushnil(L);
        /* error opening the directory? */
        /* return nil and ... */
        lua_pushstring(L, strerror(errno)); /* error message */
        return 2; /* number of results */
    }
    /* create result table */
    lua_newtable(L);
    i = 1;
    while ((entry = readdir(dir)) != NULL) {
        lua_pushnumber(L, i++); /* push key */
        lua_pushstring(L, entry->d_name); /* push value */
	//printf("entry->d_name : %s\n", entry->d_name);
        lua_settable(L, -3);
    }
    closedir(dir);
    return 1;
    /* table is already on top */
}
 
int map (lua_State *L) {
    int i, n;
    /* 1st argument must be a table (t) */
    luaL_checktype(L, 1, LUA_TTABLE);
    /* 2nd argument must be a function (f) */
    luaL_checktype(L, 2, LUA_TFUNCTION);
    n = lua_rawlen(L, 1); /* get size of table */
    for (i=1; i<=n; i++) {
        lua_pushvalue(L, 2); /* push f */
        lua_rawgeti(L, 1, i); /* push t[i] */
        lua_call(L, 1, 1); /* call f(t[i]) */
        lua_rawseti(L, 1, i); /* t[i] = result */
    }
    return 0; /* no results */
}
static const struct luaL_Reg mylib[] = {
    {"l_sum" , sum},
    {"l_sin" , mysin},
    {"l_dir" , dir},
    {"l_map" , map},
    {NULL, NULL}
};
 
int luaopen_mylib(lua_State *L){
    luaL_newlib(L, mylib); // 5.2
    return 1;
}
