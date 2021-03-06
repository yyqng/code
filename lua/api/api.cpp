#include "color.h"
//#include "libtest.h"
#include "libtool.h"
//#include "lauxlib.h"
#include <stdio.h>

#include <string.h>
#ifdef __cplusplus //告诉编译器，如果定义了__cplusplus(即如果是cpp文件)

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
#endif


#define LUA_POP(L,n) lua_settop(L, -(n)-1)
void stackDumpTest(void){
    lua_State *L = luaL_newstate();

    lua_pushboolean(L, 1);
    lua_pushnumber(L, 10);
    lua_pushnil(L);
    lua_pushstring(L, "yoyu");
    stackDump(L, "1111");         // dump the stack

    lua_pushvalue(L, -4); // push the value of the index to the stack
    stackDump(L, "2222");

    lua_replace(L, 3);    // pop a value and replace the index's
    stackDump(L, "3333");

    lua_settop(L, 6);     // set the top index, fill 'nil'
    stackDump(L, "4444");

    lua_remove(L, -3);    //
    stackDump(L, "5555");

    lua_settop(L, -3);    //Count from top(0) to bottom(negative)
    stackDump(L, "6666");

    lua_settop(L, 2);     //Count from bottom(1) to top(positive)
    stackDump(L, "7777");

    lua_insert(L, -2);    // move top element to the bottom
    stackDump(L, "8888");

    LUA_POP(L, 1);
    stackDump(L, "9999");

    lua_close(L);
}

void printFloats (int n, ...)
{
  int i;
  double val;
  printf ("Printing floats:");
  va_list vl;
  va_start(vl,n);
  for (i = 0; i < n; i++)
  {
    val = va_arg(vl,double);
    printf (" [%.2f]",val);
  }
  va_end(vl);
  printf ("\n");
}

void lualenTest()
{
    lua_State *L = luaL_newstate();
    lua_pushstring(L, "yoyu");
    const char *s = lua_tostring(L, -1); /* any Lua string */
    printf ("s is %s\n", s);
//    size_t l = luaL_len(L, -1); /* its length */
//    assert(s[l] == '\0');
//    assert(strlen(s) <= l);
    lua_close(L);
}

int callGlobalLuafunc(lua_State *L, const char* func) {
    lua_getglobal(L, func);
    if (!lua_isfunction(L, -1)) {
        printf ("%s is not exist\n", func);
        return -1;
    }
    if (lua_pcall(L, 0, 0, 0) != 0) {
        printf ("lua_pcall: %s\n", lua_tostring(L, -1));
        return -1;
    }
    return 0;
}

int callGlobalLuafun(lua_State *L = NULL) {
    char filename[] = "test.lua";
    if (!L) {
        L = luaL_newstate();
        luaopen_base(L);
        if (luaL_dofile(L, filename)) {
            error(L, "luaL_dofile: %s", lua_tostring(L, -1));
        }
    }
    for (int i = 0; i < 2; ++i) {
        lua_getglobal(L, "GlobalFunction");
        if (!lua_isfunction(L, -1)) {
            printf ("GlobalFunction is not exist\n");
            return -1;
        }
        if (lua_pcall(L, 0, 0, 0) != 0) {
            printf ("lua_pcall: %s\n", lua_tostring(L, -1));
            return -1;
        }
    }
    return 0;
}

int callLuafun2(char* const filename, const char** func) {
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaL_openlibs(L); // open all the libs
    if (luaL_dofile(L, filename)) {
        error(L, "luaL_dofile : %s", lua_tostring(L, -1));
    }
    for (int i = 0; i < 1; ++i) {
        lua_getglobal(L, func[i]);
        int ret = lua_pcall(L, 0, 1, 0);
        if (ret != 0) {
            printf ("error %s\n", lua_tostring(L, -1));
            return -1;
        }
    }
    lua_close(L);
    return 0;
}

int dofile(const char *filename) {
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaopen_table(L);
    luaopen_package(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    luaL_openlibs(L); // open all the libs above
    if (luaL_loadfile(L, filename)) {
        error(L, "luaL_loadfile %s", lua_tostring(L, -1));
    }
    if (lua_pcall(L, 0, 0, 0)) {
        error(L, "lua_pcall: %s", lua_tostring(L, -1));
    }
    /*
    const char *cmd = "    local key1, key2 = lib.lset_regref()\
    print(string.format(\"%x\", key1))\
    print(string.format(\"%x\", key2))\
    lib.lget_regref(key1, key2)";*/
    const char *cmd = "test_reg()";
    if (luaL_dostring(L, cmd)) {
        error(L, "luaL_loadstring: %s", lua_tostring(L, -1));
    }
    //callGlobalLuafunc(L, "ctest_reg");
    /*
    if (lua_pcall(L, 0, 0, 0)) {
        error(L, "lua_pcall: %s", lua_tostring(L, -1));
    }*/
    lua_close(L);

    return 0;
}

int callwk(const char *filename, const char* func) {
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaopen_table(L);
    luaopen_package(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    luaL_openlibs(L); // open all the libs above
    if (luaL_dofile(L, filename))
        error(L, "luaL_dofile: %s\n", lua_tostring(L, -1));
    callLuaf(L, func, "");
    lua_close(L);

    //double x = 3.0;
    //double y = 2.0;
    //double z = 0;
    //callLuaf(L, func, "dd>d", x, y, &z);//call func(L, x, y);
    //printf ("In %s, %s(%f, %f) = %f\n", filename, func, x, y, z);
    return 0;
}

void luaapitest() {
    lua_State *L = luaL_newstate();
//    printf ("lua_version(NULL) = %f\n", *(double*)lua_version(NULL));
//    printf ("lua_version(L) = %f\n", *(double*)lua_version(L));
//    ((void)L);
//    luaL_checkversion(L);
    lua_close(L);
}

void definetest()
{
#define LUA_TNIL		0
    printf ("LUA_TNIL = %d\n", LUA_TNIL);
//#define NILCONSTANT	{NULL}, LUA_TNIL
//#define NILCONSTANT	NULL
//    printf ("NILCONSTANT = %s\n", NILCONSTANT);
#ifdef __STRICT_ANSI__
    printf ("__STRICT_ANSI__ defined\n");
#endif

#ifdef __x86_64
        printf ("__x86_64 defined\n");
#endif

#if (0)
    #error if error
#endif
}

int table_next(lua_State *L, int i,char **k, char **v)
{
    if (lua_next(L, i) != 0) {
        *k = (char *)lua_tostring(L, -2);
        *v = (char *)lua_tostring(L, -1);
        lua_pop(L, 1);
        printf("lua_next != 0 i = %d: k = %s  v = %s\n", i, *k, *v);
        return 1;
    } else {
        printf("lua_next == 0 i = %d: k = %s  v = %s\n", i, *k, *v);
        return 0;
    }
}

int table_next_test(const char*filename)
{
    lua_State *L;
    //int t_idx;
    char *k= NULL;
    char *v= NULL;

//    L = lua_open();
    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_loadfile(L, filename);
    lua_pcall(L, 0, 0, 0);

    lua_getglobal(L, "testtab");
    lua_gettop(L);
    //t_idx = lua_gettop(L);
    lua_pushnil(L);
    while (table_next(L, 1, &k, &v) != 0) {
    }

    lua_close(L);
    return 1;
}

int test_lua_cmd(void) {
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

int main(void)
{
    //stackDumpTest();
    //loadTable();
    //printFloats (3,3.14159,2.71828,1.41421);
    //lualenTest();
    //callGlobalLuafun();
    //char filename[] = "testlua/test.lua";
    //const char* funcname[] = {"myprint"}; //, "myprint"};
    //callLuafun2(filename, funcname);
    //char filename[] = "lua_call_c/calllib.lua";
    //const char* funcname[] = {"test_reg"}; //, "myprint"};
    //callLuafun2(filename, funcname);
    //luaapitest();
    //definetest();
    //char filename[] = "c_call_lua/color.lua";
    //dofile(filename);
    //char filename[] = "luatest.lua";
    //table_next_test(filename);
    //test_lua_cmd();
    //char filename[] = "c_call_lua/wk.lua";
    //callwk(filename, "wkmain");
    //callwk(filename, "wkinit");
    char filename[] = "lua_call_c/calllib.lua";
    dofile(filename);
}
#ifdef __cplusplus
}
#endif
