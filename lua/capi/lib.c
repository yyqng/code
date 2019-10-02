#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
 
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
    /* 1st argument must be a table */
    luaL_checktype(L, 1, LUA_TTABLE);
    /* 2nd argument must be a function */
    luaL_checktype(L, 2, LUA_TFUNCTION);
    n = lua_rawlen(L, 1);          // get size of table 
    for (i=1; i<=n; i++) {
        lua_pushvalue(L, 2);       // push function

        lua_rawgeti(L, 1, i);    // push table[i]. equal to call:
        //lua_pushnumber(L, i);
        //lua_rawget(L, 1);

        lua_call(L, 1, 1);         // call function(table[i]) and push result

        lua_rawseti(L, 1, i);    // table[i] = result. equal to call:
        //lua_pushnumber(L, i);
        //lua_insert(L, -2);
        //lua_rawset(L, 1);

    }
    return 0; /* no results */
}

static int split (lua_State *L) {
    const char *s = luaL_checkstring(L, 1);
    const char *sep = luaL_checkstring(L, 2);
    const char *e;
    int i = 1;
    lua_newtable(L); /* result */
    /* repeat for each separator */
    while ((e = strchr(s, *sep)) != NULL) {
        lua_pushlstring(L, s, e-s); /* push substring */
        lua_rawseti(L, -2, i++);
        printf("%s\n",e);
        s = e + 1; /* skip separator */
    }
    /* push last substring */
    lua_pushstring(L, s);
    lua_rawseti(L, -2, i);
    return 1; /* return the table */
}

int ctest(lua_State *L)
{

    static const char kKey = 'K';
    static const char kkkkk[] = "kkkkk";
    /* store a string*/
    lua_pushlightuserdata(L, (void *)&kKey); /* push address */
    lua_pushstring(L, kkkkk);
    /* push value */
    /* registry[&kKey] = myNumber */
    lua_settable(L, LUA_REGISTRYINDEX);

    /* variable with an unique address */
    static const char Key = 'k';
    int myNumber = 1111;
    /* store a number */
    lua_pushlightuserdata(L, (void *)&Key); /* push address */
    lua_pushnumber(L, myNumber);
    /* push value */
    /* registry[&Key] = myNumber */
    lua_settable(L, LUA_REGISTRYINDEX);

    /* retrieve a number */
    lua_pushlightuserdata(L, (void *)&Key);
    /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX); /* retrieve value */
    myNumber = lua_tonumber(L, -1); /* convert to number */
    printf("myNumber = %d\n", myNumber);

    /* retrieve a string*/
    lua_pushlightuserdata(L, (void *)&kKey);
    /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX); /* retrieve value */
    const char *s = lua_tostring(L, -1); /* convert to number */
    printf("s = %s\n", s);

    return 1; /* return the table */
}

typedef struct NumArray {
    int size;
    double values[1]; /* variable part */
} NumArray;

static int newarray (lua_State *L) {
    int n = luaL_checkint(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    a->size = n;
    return 1; /* new userdatum is already on the stack */
}

static int setarray (lua_State *L) {
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);
    double value = luaL_checknumber(L, 3);
    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");
    a->values[index-1] = value;
    //printf("value is set to = %f\n", value);
    return 0;
}

static int getarray (lua_State *L) {
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);
    luaL_argcheck(L, a != NULL, 1, "'array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2,
    "index out of range");
    lua_pushnumber(L, a->values[index-1]);
    return 1;
}

static int getsize (lua_State *L) {
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    lua_pushnumber(L, a->size);
    return 1;
}

int luaopen_array (lua_State *L) {
    luaL_newmetatable(L, "LuaBook.array");
    //luaL_openlibs(L, "array", arraylib, 0);
    luaL_openlibs(L);
    return 1;
}

static int newarrayV2 (lua_State *L) {
    int n = luaL_checkint(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    luaL_getmetatable(L, "LuaBook.array");
    lua_setmetatable(L, -2);
    a->size = n;
    return 1; /* new userdatum is already on the stack */
}

static NumArray *checkarray (lua_State *L) {
    void *ud = luaL_checkudata(L, 1, "LuaBook.array");
    luaL_argcheck(L, ud != NULL, 1, "`array' expected");
    return (NumArray *)ud;
}

static int getsizeV2 (lua_State *L) {
   NumArray *a = checkarray(L);
   lua_pushnumber(L, a->size);
   return 1;
}

static double *getelem (lua_State *L) {
    NumArray *a = checkarray(L);
    int index = luaL_checkint(L, 2);
    luaL_argcheck(L, 1 <= index && index <= a->size, 2,
    "index out of range");
    /* return element address */
    return &a->values[index - 1];
}

static int setarrayV2 (lua_State *L) {
    double newvalue = luaL_checknumber(L, 3);
    *getelem(L) = newvalue;
    return 0;
}

static int getarrayV2 (lua_State *L) {
    lua_pushnumber(L, *getelem(L));
    return 1;
}

//Name of array mylib can be changed.
static const struct luaL_Reg mylib[] = {
    {"lsum" , sum},
    {"lsin" , mysin},
    {"ldir" , dir},
    {"lmap" , map},
    {"lsplit" , split},
    {"lctest" , ctest},

    {"lnewarray" , newarray},
    {"lsetarray" , setarray},
    {"lgetarray" , getarray},
    {"lgetsize" , getsize},

    {"lnewarrayV2" , newarrayV2},
    {"lsetarrayV2" , setarrayV2},
    {"lgetarrayV2" , getarrayV2},
    {"lgetsizeV2" , getsizeV2},

    {NULL, NULL}
};
 
//Function name can not be changed.
int luaopen_lib(lua_State *L){ 
    luaL_newlib(L, mylib); // 5.2
    return 1;
}
