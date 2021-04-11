#include "libtest.h"

int wkinit(lua_State *L){
    printf("wkinit\n");
    return 0;
}

int wkmain(lua_State *L){
    printf("wkmain\n");
    return 0;
}

int mysin (lua_State *L) {
    double d = lua_tonumber(L, 1); /* get argument */
    lua_pushnumber(L, sin(d)); /* push result */
    return 1; /* number of results */
}

static int push_test(lua_State *L){
    lua_pushnumber(L, 1111);
    stackDump(L, "1111");
    //lua_remove(L, -1);
    stackDump(L, "2222");
    return 0;      //自动销毁C栈,需使用lua注册表持久保存数据
}

static int pop_test(lua_State *L){
    stackDump(L, "3333");  //C栈为空,需使用lua注册表持久保存数据
    return 0;
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

static int dir_iter(lua_State *L);

static int dir_gc(lua_State *L)
{
    DIR *dir = *(DIR**)lua_touserdata(L, 1);
    if (dir) {
        closedir(dir);
    }
    return 0;
}

int dirV2 (lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    DIR **dir = (DIR**)lua_newuserdata(L, sizeof(DIR*));
    *dir = NULL; // 预先初始化
    luaL_getmetatable(L, "LuaBook.dir");
    lua_setmetatable(L, -2);
    *dir = opendir(path);
    //创建并返回迭代函数；该函数唯一的upvalue，即代表目录的用户数据位于栈顶
    lua_pushcclosure(L, dir_iter, 1);
    return 1;
}

static int dir_iter(lua_State *L)
{
    DIR *dir = *(DIR**)lua_touserdata(L, lua_upvalueindex(1));
    struct dirent *entry = readdir(dir);
    if (entry) {
        lua_pushstring(L, entry->d_name);
        return 1;
    } else {
        return 0; //遍历完成
    }
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

static int tconcat(lua_State *L)
{
    luaL_Buffer b;
    int i, n;
    luaL_checktype(L, 1, LUA_TTABLE);
    n = luaL_len(L, 1);
    luaL_buffinit(L, &b);
    for (i = 1; i <= n; i++) {
        lua_geti(L, 1, i);      // Get string from table
        luaL_addvalue(&b);      // Put string in buff
    }
    luaL_pushresult(&b);
    char* s = lua_tostring(L, -1);
    printf("in c   : s = %s\n", s);
    //lua_remove(L, -1);
    return 1;
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

static int str_upper(lua_State *L)
{
    luaL_Buffer b;
    size_t i, l;
    const char *s = luaL_checklstring(L, 1, &l);
    char *p = luaL_buffinitsize(L, &b, l);
    for (i = 0; i < l; i++) {
        p[i] = toupper((unsigned char)s[i]);
    }
    luaL_pushresultsize(&b, l);
    return 1;
}

static int sum(lua_State *L){
    //double d1 = luaL_checknumber(L, 1);
    //double d2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, 1);//d1 + d2);
    lua_pushnumber(L, 2);//d1 - d2);
    return 2;
}

static int set_regref(lua_State *L)
{
    int key1 = luaL_ref(L, LUA_REGISTRYINDEX);
    char data_of_key1[] = "char data of key1";
    lua_pushlightuserdata(L, (void *)&key1);  /* push address */
    lua_pushstring(L,  data_of_key1);         /* push value */
    lua_settable(L, LUA_REGISTRYINDEX);       /* registry[&key1] =  data_of_key1*/
    printf("key1 = %d set registry[&%p] = %s\n", key1, &key1, data_of_key1);

    int key2 = luaL_ref(L, LUA_REGISTRYINDEX);
    int number_of_key2 = key2 * 1000;
    lua_pushlightuserdata(L, (void *)&key2);  /* push address */
    lua_pushnumber(L, number_of_key2);        /* push value */
    lua_settable(L, LUA_REGISTRYINDEX);       /* registry[&key2] = number_of_key2 */
    printf("key2 = %d set registry[&%p] = %d\n", key2, &key2, number_of_key2);

    lua_rawgeti(L, LUA_REGISTRYINDEX, key1);  /* why needed? */
    lua_rawgeti(L, LUA_REGISTRYINDEX, key2);  /* why needed? */
    lua_pushnumber(L, (long)(&key1));        /* push address */
    lua_pushnumber(L, (long)(&key2));        /* push address */
    printf("key1 = %p\n", (void *)lua_tointeger(L, -2));
    printf("key2 = %p\n", (void *)lua_tointeger(L, -1));

    return 2; /* return the keys */
}

int get_regref(lua_State *L)
{
    long key1_addr = luaL_checknumber(L, 1);
    long key2_addr = luaL_checknumber(L, 2);
    /* retrieve a string*/
    lua_pushlightuserdata(L, (void*)key1_addr); /* push address. */
    lua_gettable(L, LUA_REGISTRYINDEX);        /* retrieve value */
    const char *key1_data = lua_tostring(L, -1); /* convert to string*/
    printf("get registry[&%p] = %s\n", (void*)key1_addr, key1_data);
    /* retrieve a number */
    lua_pushlightuserdata(L, (void*)key2_addr); /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX);       /* retrieve value */
    int key2_data = lua_tonumber(L, -1);        /* convert to number */
    printf("get registry[&%p] = %d\n", (void*)key2_addr, key2_data);

    luaL_unref(L, LUA_REGISTRYINDEX, (int)key1_addr);
    luaL_unref(L, LUA_REGISTRYINDEX, (int)key2_addr);
    printf("return\n");
    return 0; /* return the table */
}

int regref_test2(lua_State *L)
{
    /* retrieve a string*/
    static const char key1 = 'k';
    //int key1 = -1;
    lua_pushlightuserdata(L, (void *)&key1);  /* push address */
    lua_pushstring(L, "myStr1");
    lua_settable(L, LUA_REGISTRYINDEX);

    lua_pushlightuserdata(L, (void *)&key1);  /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX);       /* retrieve value */
    const char *s = lua_tostring(L, -1);      /* convert to string*/
    printf("kstring = registry[&%c] = %s\n", key1, s);

    /* retrieve a number */
    //static const char key2 = 'k';
    int key2 = 4;
    lua_pushlightuserdata(L, (void *)&key2);  /* push address */
    lua_pushnumber(L, 8888);
    lua_settable(L, LUA_REGISTRYINDEX);

    lua_pushlightuserdata(L, (void *)&key2);  /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX);       /* retrieve value */
    int knumber = lua_tonumber(L, -1);            /* convert to number */
    printf("knumber = registry[&%d] = %d\n", key2, knumber);
    return 1; /* return the table */
}

static int counter(lua_State *L)
{
    int val = lua_tointeger(L, lua_upvalueindex(1));
    lua_pushinteger(L, ++val); //新值
    lua_copy(L, -1, lua_upvalueindex(1)); //用新值更新upvalue
    return 1; //返回新值
}

int newCounter(lua_State *L)
{
    lua_pushinteger(L, 1); //压入upvalue，初始值为1
    lua_pushcclosure(L, &counter, 1); //创建闭包
    return 1; //返回闭包
}

int t_tupple(lua_State *L)
{
    lua_Integer op = luaL_optinteger(L, 1, 0); //获取1个参数值，默认0
    if (op == 0) { //没有参数
        int i;
         /*将每一个有效的upvalue压栈*/
        for (i = 1; !lua_isnone(L, lua_upvalueindex(i)); ++i) {
            lua_pushvalue(L, lua_upvalueindex(i));
        }
        return i - 1; //值的个数
    } else {
        luaL_argcheck(L, 0 < op && op <= 256, 1, "index out of range");
        if (lua_isnone(L, lua_upvalueindex(op))) {
            return 0; //字段不存在
        }
        lua_pushvalue(L, lua_upvalueindex(op));
        return 1;
    }
}

int t_new(lua_State *L)
{
    int top = lua_gettop(L);
    luaL_argcheck(L, top < 256, top, "too many fields");
    lua_pushcclosure(L, t_tupple, top);
    return 1;
}

int newarray (lua_State *L) {
    int n = luaL_checkinteger(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    //把这块分配的内存压入栈，并把地址存入 a。
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    a->size = n;
    luaL_getmetatable(L, "LuaBook.array");
    lua_setmetatable(L, -2);
    return 1; // new userdatum is already on the stack
}

//判断第一个参数的元表是否为 registry["LuaBook.array"]
#define checkarray(L) (NumArray *)luaL_checkudata(L, 1, "LuaBook.array")

static int getindex (lua_State *L) {
    NumArray *a = checkarray(L);
    int index = luaL_checkinteger(L, 2) - 1;
    luaL_argcheck(L, 0 <= index && index < a->size, 2,"index out of range");
    return index; /* return element address */
}

int getsize (lua_State *L) {
   NumArray *a = checkarray(L);
   lua_pushnumber(L, a->size);
   return 1;
}

static double *getelem (lua_State *L) {
    NumArray *a = checkarray(L);
    int index = getindex(L);
    return &a->values[index];    // return element address.
}

int setarray (lua_State *L) {
    double newvalue = luaL_checknumber(L, 3);
    *getelem(L) = newvalue;
    return 0;
}

int getarray (lua_State *L) {
    double ret = *getelem(L);
    lua_pushnumber(L, ret);
    return 1;
}

int array2string (lua_State *L) {
    NumArray *a = checkarray(L);
    lua_pushfstring(L, "array(%d)", a->size);
    return 1;
}

//Name of array mylib can be changed.
static const struct luaL_Reg thelib[] = {
    {"lwkinit", wkinit},
    {"lwkmain", wkmain},
    {"lsum", sum},
    {"lpush_test", push_test},
    {"lpop_test", pop_test},
    {"lsin", mysin},
    {"ldir", dirV2},//dir},
    {"lmap", map},
    {"ltconcat", tconcat},
    {"lstr_upper", str_upper},
    {"lnew_NumArray", new_NumArray},
    {"lNumArray_print", NumArray_print},
    {"lnew_Student", new_Student},
    {"lStudent_print", Student_print},
    {"lsplit", split},
    {"lset_regref",  set_regref},
    {"lget_regref",  get_regref},
    {"lregref_test2",  regref_test2},
    {"lnewCounter",  newCounter},
    {"lnew",  t_new},

    {"new", newarray},
    {"set", setarray},
    {"get", getarray},
    {"size", getsize},
    {NULL, NULL}
};

static const struct luaL_Reg arraylib_f [] = {
    {"new", newarray},
    {NULL, NULL}
};

static const struct luaL_Reg arraylib_m[] =
{
    {"__newindex", setarray},
    {"__index", getarray},
    {"__len", getsize},
    {"__tostring", array2string},
    {NULL,NULL}
};

//Function name can not be changed.
int luaopen_libtest(lua_State *L){ 
    //luaL_newlib(L, mylib); // 5.2
    //luaL_openlib(L, "array", mylib, 0);
    //luaL_openlibs(L, "array", mylib, 0);
    luaL_newmetatable(L, "LuaBook.array"); // 创建元表 mt
    //lua_pushvalue(L, -1); // 复制元表
    //把栈顶的元表弹出并设置 mt.__index = mt
    //lua_setfield(L, -2, "__index");
    //把 set,get,size 3个方法注册到 mt 元表
    //luaL_register(L, NULL, arraylib_m);
    luaL_setfuncs(L, arraylib_m, 0);
    //把 new函数 注册到 package.loaded['array'] 对应的表格
    //luaL_register(L, "array", arraylib_f);
    //luaL_newlib(L, arraylib_f);
    luaL_newmetatable(L, "LuaBook.dir");
    lua_pushcfunction(L, dir_gc);
    lua_setfield(L, -2, "__gc");
    luaL_newlib(L, thelib);
    return 1;
}
