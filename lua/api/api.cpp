//#include "color.h"
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
    stackDump(L);         // dump the stack

    lua_pushvalue(L, -4); // push the value of the index to the stack
    stackDump(L);

    lua_replace(L, 3);    // pop a value and replace the index's
    stackDump(L);

    lua_settop(L, 6);     // set the top index, fill 'nil'
    stackDump(L);

    lua_remove(L, -3);    //
    stackDump(L);

    lua_settop(L, -3);    //Count from top(0) to bottom(negative)
    stackDump(L);

    lua_settop(L, 2);     //Count from bottom(1) to top(positive)
    stackDump(L);

    lua_insert(L, -2);    // move top element to the bottom
    stackDump(L);

    LUA_POP(L, 1);
    stackDump(L);

    lua_close(L);
}
/**/
int exeInputLua(void)
{
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();//lua_open(); // opens Lua 
    luaopen_base(L);   // opens the basic library 
    luaopen_table(L);  // opens the table library 
    luaopen_io(L);     // opens the I/O library 
    luaopen_string(L); // opens the string lib. 
    luaopen_math(L);   // opens the math lib. 
    printf("Please input lua script:\n");
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        //Compile buff and execute chunk
        error = luaL_loadbuffer(L, buff, strlen(buff), "line") || 
                lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);// pop error message from the stack
        }
    }
    lua_close(L);
    return 0;
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

void test2(void)
{
    const char *fmt = "%s %s";
    const char *H = "Hello ";
    const char *h = "hello\n";
    const char *w = "world\n";
    lua_State *L = luaL_newstate();//lua_open();
    error(L, fmt, H, h, w);
    lua_close(L);
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

double callfLuafTest () {
    char filename[] = "pp.lua";
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run configuration file: %s", lua_tostring(L, -1));

    double x = 3.0;
    double y = 2.0;
    double z = 0;
    callLuaf(L, "wk", "dd>d", x, y, &z);//call Luaf(L, x, y);
    lua_close(L);
    printf ("In %s, wk(%f, %f) = %f\n", filename, x, y, z);
    return z;
}

double callfLuafTest2() {
    char filename[] = "pp.lua";
    lua_State *L = luaL_newstate();
    stackDump(L);
    luaopen_base(L);
    //luaopen_io(L);
    //luaopen_string(L);
    //luaopen_math(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run configuration file: %s", lua_tostring(L, -1));

    stackDump(L);
    double x = 3.0;
    double y = 2.0;
    double z = 0;
    callLuaf(L, "wk", "dd>d", x, y, &z);//call func(L, x, y);
    lua_close(L);
    printf ("In %s, Luaf(%f, %f) = %f\n", filename, x, y, z);
    return z;
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

int callLuafun() {
    char filename[] = "test.lua";
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    if (luaL_dofile(L, filename)) {
        error(L, "luaL_dofile : %s", lua_tostring(L, -1));
    }
    for (int i = 0; i < 2; ++i) {
        lua_getglobal(L, "test");
        if (!lua_istable(L, -1)) {
            printf ("test is not exist\n");
            return -1;
        }
        
        lua_getfield(L, -1, "test_lua_func");
        if (!lua_isfunction(L, -1)) {
            printf ("test_lua_func is not exist\n");
            //cout << "GlobalFunction is not exist" << endl;
            return -1;
        }
        
        lua_pushnumber(L, 11);
        lua_pushnumber(L, 22);
        if (lua_pcall(L, 2, 1, 0) != 0) {
            printf ("error %s\n", lua_tostring(L, -1));
            return -1;
        }
    }
    callGlobalLuafun(L);
    lua_close(L);

    return 0;
}

int dofile(const char *filename) {
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
        error(L, "luaL_dofile || lua_pcall: %s", lua_tostring(L, -1));
    }
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

int callwk_bak(const char *filename, const char* func) {
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaopen_table(L);
    luaopen_package(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    luaL_openlibs(L); // open all the libs above
    //if (luaL_loadfile(L, filename))
    //    error(L, "luaL_loadfile(L, %s) failed: ", lua_tostring(L, -1));
    if (luaL_dofile(L, filename))
        error(L, "luaL_dofile: %s\n", lua_tostring(L, -1));
    lua_getglobal(L, func);
    lua_pushnumber(L, 10);   //--x 值入栈
    lua_pushnumber(L, 20);   //--y 值入栈
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        error(L, "error running function %s\n", lua_tostring(L, -1));
    }
    if (!lua_isnumber(L, -1)) {
        error(L, "function must return a number\n");
    }
    double z = lua_tonumber(L, -1);
    lua_pop(L, 1); 
    lua_close(L);
    printf ("In %s, %s(10, 20) = %f\n", filename, func, z);
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

/*
static int dt_get_patchsize(lua_State* L)
{
    int r = ud->getHscanMode() ? ApiContext::CELL : ApiContext::P;
    int n = lua_gettop(L);
    if (n > 0) {
        r = luaL_checkint(L, 1);
    }
    bl_rect_t rect;
    get_patchrect(ud, r, &rect);
    dt_ii_t* a = ud->getII();
    double width = DT_I2U(a, (rect.right - rect.left));
    double height = DT_I2U(a, (rect.top - rect.bottom));
    lua_newtable(L);
    lua_pushstring(L, "width");
    lua_pushnumber(L, width);
    lua_settable(L, -3);
    lua_pushstring(L, "height");
    lua_pushnumber(L, height);
    lua_settable(L, -3);
    return 1;
}
*/

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

int main(void)
{
    //stackDumpTest();
    //exeInputLua();
    //test2();
    //printFloats (3,3.14159,2.71828,1.41421);
    //lualenTest();
    //loadConf();
    //loadTable();
    //callfLuafTest2();
    //callGlobalLuafun();
    //callLuafun();
    //callfLuafTest();
    //luaapitest();
    //definetest();
    //char filename[] = "calllib.lua";
    //dofile(filename);
    //char filename[] = "c_call_lua/color.lua";
    //dofile(filename);
    //char filename[] = "luatest.lua";
    //table_next_test(filename);
    char filename[] = "c_call_lua/wk.lua";
    callwk(filename, "wkmain");
    callwk(filename, "wkinit");
}
#ifdef __cplusplus
}
#endif
