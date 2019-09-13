#include <stdio.h>
#include <cstring>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <lua.hpp>
using namespace std;

static void stackDump(lua_State *L){
    int i;
    int top = lua_gettop(L);
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
        printf("  ");
    }
    printf("\n");
}

void test(void){
    lua_State *L = luaL_newstate();

    lua_pushboolean(L, 1);
    lua_pushnumber(L, 10);
    lua_pushnil(L);
    lua_pushstring(L, "yoyu");
    stackDump(L);    // dump the stack

    lua_pushvalue(L, -4);// push the value of the index to the stack
    stackDump(L);

    lua_replace(L, 3);  // pop a value and replace the index's
    stackDump(L);

    lua_settop(L, 6);  // set the top index, fill 'nil'
    stackDump(L);

    lua_remove(L, -3);  //
    stackDump(L);

    lua_settop(L, -5);
    stackDump(L);

    lua_close(L);
}
/**/
int test1(void)
{
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();//lua_open();
    luaopen_base(L);
    // opens Lua 
    // opens the basic library 
    luaopen_table(L); // opens the table library 
    luaopen_io(L); // opens the I/O library 
    luaopen_string(L); // opens the string lib. 
    luaopen_math(L); // opens the math lib. 
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadbuffer(L, buff, strlen(buff),
        "line") || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));
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

void error (lua_State *L, const char *fmt, ...) {
    va_list vl;
    va_start(vl, fmt);
    vfprintf(stderr, fmt, vl);
    va_end(vl);
    lua_close(L);
    printf ("\n");
    exit(EXIT_FAILURE);
    printf ("\n");
}

void test2(void)
{
    const char *fmt="%s";
    const char *s="hello";
    //int i =5;
    lua_State *L = luaL_newstate();//lua_open();
    error(L,fmt,s);
}

void test3(void)
{
    lua_State *L = luaL_newstate();
    lua_pushstring(L, "yoyu");
    const char *s = lua_tostring(L, -1); /* any Lua string */
    size_t l = luaL_len(L, -1); /* its length */
    assert(s[l-1] == '\0');
    assert(strlen(s) <= l);
}

int main(void)
{
    //test();
    //test1();
    //printFloats (3,3.14159,2.71828,1.41421);
    //test2();
}
