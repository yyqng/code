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
 
static const struct luaL_Reg mylib[] = {
    {"l_sum" , sum},
    {"l_sin" , mysin},
    {"l_dir" , dir},
    {NULL, NULL}
};
 
int luaopen_mylib(lua_State *L){
    luaL_newlib(L, mylib); // 5.2
    return 1;
}
