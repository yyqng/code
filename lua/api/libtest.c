#include "libtest.h"

int wkinit(lua_State *L){
    printf("wkinit\n");
    return 0;
}

int wkmain(lua_State *L){
    printf("wkmain\n");
    return 0;
}

static int sum(lua_State *L){
    double d1 = luaL_checknumber(L, 1);
    double d2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, d1+d2);
    return 1;
}

int mysin (lua_State *L) {
    double d = lua_tonumber(L, 1); /* get argument */
    lua_pushnumber(L, sin(d)); /* push result */
    return 1; /* number of results */
}

int dir (lua_State *L) {
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
    //stackDump(L);
    int i, n;
    /* 1st argument must be a table */
    luaL_checktype(L, 1, LUA_TTABLE);
    /* 2nd argument must be a function */
    luaL_checktype(L, 2, LUA_TFUNCTION);
    //n = lua_rawlen(L, 1);          // get size of table . equal to call:
    n = luaL_len(L, 1);              // get size of table 
    for (i = 1; i <= n; ++i) {
        lua_pushvalue(L, 2);         // push function
        lua_geti(L, 1, i);           // push table[i]. equal to call:
        //lua_rawgeti(L, 1, i);      // push table[i]. equal to call:
        //lua_pushnumber(L, i);
        //lua_rawget(L, 1);

        lua_call(L, 1, 1);           // call and pop function(table[i]), push result
        lua_seti(L, 1, i);           // table[i] = result. equal to call:
        //lua_rawseti(L, 1, i);      // table[i] = result. equal to call:
        //lua_pushnumber(L, i);
        //lua_insert(L, -2);
        //lua_rawset(L, 1);
    }
    return 0; /* no results */
}

int new_NumArray (lua_State *L) {
    //stackDump(L);
    NumArray *retArray =  (NumArray *)lua_newuserdata (L , sizeof(NumArray)) ;
    retArray->size = 314;
    retArray->values[0] = 618;
    lua_pushlightuserdata(L, (void*)retArray);

    //lua_pushlightuserdata(L, (void*)&retArray);
    return 1; /* no results */
}

int NumArray_print (lua_State *L) {
    //stackDump(L);
    /* 1st argument must be a table */
    luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
    NumArray *retArray = (NumArray *)lua_touserdata(L , 1);
    printf("retArray = {%d, %f}\n", retArray->size, retArray->values[0]);
    retArray->size = 311;
    retArray->values[0] = 609;
    //NumArray *retArray = (NumArray *)luaL_checkudata(L, 1, "NumArray");
    return 0; /* no results */
}

int new_Student (lua_State *L) {
    //stackDump(L);
    Student *retArray =  (Student *)lua_newuserdata(L , sizeof(Student));
    char *c =  (char *)lua_newuserdata (L , 6);
    memcpy(c, "hello", 6);
    retArray->age = 16;
    retArray->name = c;
    lua_pushlightuserdata(L, (void*)retArray);

    //lua_pushlightuserdata(L, (void*)&retArray);
    return 1; /* no results */
}

int Student_print (lua_State *L) {
    //stackDump(L);
    /* 1st argument must be a table */
    luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
    Student *pStu = (Student *)lua_touserdata(L , 1);
    printf("Student = {%d, %s}\n", pStu->age, pStu->name);
    pStu->age = 2;
    pStu->name[2] = 'n';
    pStu->name[3] = 'n';
    return 0; /* no results */
}

//LUA_API int luaopen_NumArray(lua_State* L){
//    luaL_newmetatable(L,"NumArray");
//    lua_pushstring (L,"__index");
//    lua_pushvalue(L,-2);
//    lua_rawset(L,-3);
//    luaL_setfuncs(L,mylib,0);
//
//    luaL_newlib(L,mylib);
//    return 1;
//}

//LUA_API int luaopen_Student(lua_State* L){
//    luaL_newmetatable(L,"Student");
//    lua_pushstring (L,"__index");
//    lua_pushvalue(L,-2);
//    lua_rawset(L,-3);
//    luaL_setfuncs(L,mylib,0);
//
//    luaL_newlib(L,mylib);
//    return 1;
//}

int split (lua_State *L) {
    const char *s = luaL_checkstring(L, 1);
    const char *sep = luaL_checkstring(L, 2);
    const char *e;
    int i = 1;
    lua_newtable(L); /* result */
    /* repeat for each separator */
    while ((e = strchr(s, *sep)) != NULL) {
        lua_pushlstring(L, s, e - s); /* push substring */
        lua_rawseti(L, -2, i++);      /* insert to table */
        s = e + 1;                    /* skip separator */
    }
    /* push last substring */
    lua_pushstring(L, s);
    lua_rawseti(L, -2, i);
    return 1; /* return the table */
}

static int tconcat(lua_State *L)
{
    luaL_Buffer b;
    int i, n;
    luaL_checktype(L, 1, LUA_TTABLE);
    n = luaL_len(L, 1);
    luaL_buffinit(L, &b);
    for (i = 1; i <= n; i++) {
        lua_geti(L, 1, i);      /*Get string from table*/
        luaL_addvalue(&b);      /*Put string in buff*/
    }
    luaL_pushresult(&b);
    char* s = lua_tostring(L, -1);
    printf("in c   : s = %s\n", s);
    //lua_remove(L, -1);
    return 1;
}

int regref1(lua_State *L)
{
    /* store a string*/
    //static const char key1 = 'k';
    int key1 = luaL_ref(L, LUA_REGISTRYINDEX);
    //lua_rawgeti(L, LUA_REGISTRYINDEX, key1);
    //printf("key1 = %f\n",lua_tonumber(L, -1));
    char kstring[] = "kstring";
    lua_pushlightuserdata(L, (void *)&key1);  /* push address */
    lua_pushstring(L,  kstring);              /* push value */
    lua_settable(L, LUA_REGISTRYINDEX);       /* registry[&key1] =  kstring*/
    /* retrieve a string*/
    lua_pushlightuserdata(L, (void *)&key1);  /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX);       /* retrieve value */
    const char *s = lua_tostring(L, -1);      /* convert to string*/
    printf("kstring = registry[&%d] = %s\n", key1, s);

    /* store a number */
    //static const char key2 = 'k';
    int key2 = luaL_ref(L, LUA_REGISTRYINDEX);
    int knumber = 1111;
    lua_pushlightuserdata(L, (void *)&key2);  /* push address */
    lua_pushnumber(L, knumber);               /* push value */
    lua_settable(L, LUA_REGISTRYINDEX);       /* registry[&key2] = knumber */
    /* retrieve a number */
    lua_pushlightuserdata(L, (void *)&key2);  /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX);       /* retrieve value */
    knumber = lua_tonumber(L, -1);            /* convert to number */
    printf("knumber = registry[&%d] = %d\n", key2, knumber);

    luaL_unref(L, LUA_REGISTRYINDEX, key1);
    luaL_unref(L, LUA_REGISTRYINDEX, key2);
    return 1; /* return the table */
}

int regref2(lua_State *L)
{
    /* retrieve a string*/
    //static const char key1 = 'k';
    int key1 = -1;
    lua_pushlightuserdata(L, (void *)&key1);  /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX);       /* retrieve value */
    const char *s = lua_tostring(L, -1);      /* convert to string*/
    printf("kstring = registry[&%d] = %s\n", key1, s);

    /* retrieve a number */
    //static const char key2 = 'k';
    int key2 = 4;
    lua_pushlightuserdata(L, (void *)&key2);  /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX);       /* retrieve value */
    int knumber = lua_tonumber(L, -1);            /* convert to number */
    printf("knumber = registry[&%d] = %d\n", key2, knumber);
    return 1; /* return the table */
}

int regref(lua_State *L)
{
    regref1(L);
    //regref2(L);
    regref1(L);
   // regref2(L);
    return 1; /* return the table */
}

static NumArray *checkarray (lua_State *L) {
    void *ud = luaL_checkudata(L, 1, "luaBook.array");
    luaL_argcheck(L, ud != NULL, 1, "`array' expected");
    return (NumArray *)ud;
}

int newarray (lua_State *L) {
    //int n = luaL_checkint(L, 1);
    int n = luaL_checkinteger(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    luaL_getmetatable(L, "LuaBook.array");
    lua_setmetatable(L, -2);
    lua_pushlightuserdata(L, (void*)a);
    a->size = n;
    return 1; /* new userdatum is already on the stack */
}

int setarray (lua_State *L) {
    //NumArray *a = (NumArray *)lua_touserdata(L, 1);
    NumArray *a = checkarray(L);
    //int index = luaL_checkint(L, 2);
    int index = luaL_checkinteger(L, 2);
    double value = luaL_checknumber(L, 3);
    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");
    a->values[index-1] = value;
    //printf("value is set to = %f\n", value);
    return 0;
}

int getarray (lua_State *L) {
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    //int index = luaL_checkint(L, 2);
    int index = luaL_checkinteger(L, 2);
    luaL_argcheck(L, a != NULL, 1, "'array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");
    lua_pushnumber(L, a->values[index-1]);
    return 1;
}

int getsize (lua_State *L) {
    //NumArray *a = (NumArray *)lua_touserdata(L, 1);
    NumArray *a = checkarray(L);
    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    lua_pushnumber(L, a->size);
    return 1;
}

int newarrayV2 (lua_State *L) {
    //int n = luaL_checkint(L, 1);
    int n = luaL_checkinteger(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    luaL_newmetatable(L, "luaBook.array");
    //luaL_getmetatable(L, "luaBook.array");
    lua_setmetatable(L, -2);
    a->size = n;
    return 1; /* new userdatum is already on the stack */
}

int getsizeV2 (lua_State *L) {
   NumArray *a = checkarray(L);
   lua_pushnumber(L, a->size);
   return 1;
}

static double *getelem (lua_State *L) {
    NumArray *a = checkarray(L);
    //int index = luaL_checkint(L, 2);
    int index = luaL_checkinteger(L, 2);
    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");
    return &a->values[index - 1];    // return element address.
}

int setarrayV2 (lua_State *L) {
    double newvalue = luaL_checknumber(L, 3);
    *getelem(L) = newvalue;
    return 0;
}

int getarrayV2 (lua_State *L) {
    lua_pushnumber(L, *getelem(L));
    return 1;
}

int array2string (lua_State *L) {
    NumArray *a = checkarray(L);
    lua_pushfstring(L, "array(%d)", a->size);
    return 1;
}

static const struct luaL_Reg arraylib_m[] =
{
    {"__index",setarray},
    {"__newindex",getarray},
    {"__len",getsize},
    {NULL,NULL}
};

//static const struct luaL_Reg arraylib[] = 
//{
//    {"new", newarray},
//    {"set", setarray},
//    {"get", getarray},
//    {"size", getsize},
//    {NULL, NULL}
//};


//int luaopen_array(lua_State *L){
    //luaL_newmetatable(L,"LuaBook.array");
    //lua_pushvalue(L,-1);
    //lua_setfield(L,-2,"__index");
    //luaL_openlib(L, "array", mylib, 0);
    
    //const struct luaL_Reg *tmp = NULL;
    //lua_register(L, NULL, mylib);
    //lua_register(L, "array", mylib);

    //lua_register(L,NULL,arraylib_m);
    //lua_register(L,"array",arraylib_f);
    //luaL_register(L,NULL,arraylib_m);
    //luaL_register(L,"array",arraylib_f);
    //return 1;
//}

//int luaopen_array (lua_State *L) {
//    luaL_newmetatable(L, "LuaBook.array");
//    lua_pushstring(L, "__index");
//    lua_pushvalue(L, -2); /* pushes the metatable */
//    lua_settable(L, -3);  /* metatable.__index = metatable */
//    //luaL_setfuncs(L, mylib, 0);
//    //luaL_setfuncs(L, NULL, mylib, 0);
//    //luaL_openlib(L, NULL, mylib, 0);
//    //luaL_openlib(L, "array", mylib, 0);
//    luaL_register(L,NULL,arraylib_m);
//    luaL_register(L,"array",arraylib_f);
//    return 1;
//}

//Name of array mylib can be changed.
static const struct luaL_Reg thelib[] = {
    {"lwkinit", wkinit},
    {"lwkmain", wkmain},
    {"lsum", sum},
    {"lsin", mysin},
    {"ldir", dir},
    {"lmap", map},
    {"ltconcat", tconcat},
    {"lnew_NumArray", new_NumArray},
    {"lNumArray_print", NumArray_print},
    {"lnew_Student", new_Student},
    {"lStudent_print", Student_print},
    {"lsplit", split},
    {"lregref",  regref},

    //{"lnewarray", newarray},
    //{"lsetarray", setarray},
    //{"lgetarray", getarray},
    //{"lgetsize", getsize},

    {"new", newarray},
    {"set", setarray},
    {"get", getarray},
    {"size", getsize},

    {"lnewarrayV2", newarrayV2},
    {"lsetarrayV2", setarrayV2},
    {"lgetarrayV2", getarrayV2},
    {"lgetsizeV2", getsizeV2},

    //{"lnew", newarray},
    {"__tostring", array2string},
    {"__index", setarray},
    {"__newindex", getarray},
    {"__len", getsize},
    {NULL, NULL}
};

//Function name can not be changed.
//int luaopen_libtest(lua_State *L){ 
int luaopen_libtest(lua_State *L){ 
    //luaL_newlib(L, mylib); // 5.2
    //luaL_openlib(L, "array", mylib, 0);
//    luaL_newmetatable(L, "LuaBook.array"); // Added to V2
    //luaL_openlibs(L, "array", mylib, 0);
    luaL_newlib(L, thelib);
    return 1;
}
