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

void stackDumpTest(void){
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
    lua_close(L);
}

void luaL_len_Test(void)
{
    lua_State *L = luaL_newstate();
    lua_pushstring(L, "yoyu");
    const char *s = lua_tostring(L, -1); /* any Lua string */
    size_t l = luaL_len(L, -1); /* its length */
    printf ("%c\n", s[l]);
    assert(s[l] == '\0');
    assert(strlen(s) <= l);
    lua_close(L);
}

#define MAX_COLOR 255
/* assume that table is on the stack top */
int getfield (lua_State *L, const char *key) {
    int result;
    lua_pushstring(L, key);
    lua_gettable(L, -2); /* get background[key] */
    if (!lua_isnumber(L, -1))
        error(L, "invalid component in background color");
    result = lua_tonumber(L, -1) * MAX_COLOR;
    lua_pop(L, 1); /* remove number */
    return result;
}

void loadConf () {
    char filename[] = "pp.conf";
    int width = 0;
    int height = 0;
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run configuration file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    if (!lua_isnumber(L, -2))
        error(L, "`width' should be a number\n");
    if (!lua_isnumber(L, -1))
        error(L, "`height' should be a number\n");
    width = (int)lua_tonumber(L, -2);
    height = (int)lua_tonumber(L, -1);
    lua_close(L);
    printf ("filename = %s, width = %d, height = %d\n", filename, width, height);
}

void loadTable () {
    char filename[] = "pp.conf";
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run configuration file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "background");
    if (!lua_istable(L, -1))
        error(L, "`background' is not a valid color table");
    int red = getfield(L, "r");
    int green = getfield(L, "g");
    int blue = getfield(L, "b");

//    lua_pushstring(L, "r");
//    lua_gettable(L, -2);
//    lua_pushstring(L, "g");
//    lua_gettable(L, -3);
//    lua_pushstring(L, "b");
//    lua_gettable(L, -4);
//    if (!lua_isnumber(L, -1) || !lua_isnumber(L, -2) || !lua_isnumber(L, -3))
//    {
//        error(L, "color field should be a number");
//    }
//    int red = lua_tonumber(L, -3);
//    int green = lua_tonumber(L, -2);
//    int blue = lua_tonumber(L, -1);
    printf ("r = %d, g = %d, b = %d\n", red, green, blue);
    lua_close(L);
}

/* call a function `f' defined in Lua */
double f (lua_State *L, double x, double y) {
    /* push functions and arguments */
    lua_getglobal(L, "f"); /* function to be called */
    lua_pushnumber(L, x); /* push 1st argument */
    lua_pushnumber(L, y); /* push 2nd argument */
    /* do the call (2 arguments, 1 result) */
    if (lua_pcall(L, 2, 1, 0) != 0)
        error(L, "error running function `f': %s",
    lua_tostring(L, -1));
    /* retrieve result */
    if (!lua_isnumber(L, -1))
        error(L, "function `f' must return a number");
    double z = lua_tonumber(L, -1);
    lua_pop(L, 1); /* pop returned value */
    return z;
}

double callf () {
    char filename[] = "pp.conf";
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run configuration file: %s", lua_tostring(L, -1));

    double x = 3.0;
    double y = 2.0;
    double z = f(L, x, y);
    lua_close(L);
    printf ("filename = %s, f(x, y) = %f\n", filename, z);
    return z;
}

void call_va (lua_State *L, const char *func, const char *sig, ...) {
    va_list vl;
    int narg, nres;
    /* number of arguments and results */
    va_start(vl, sig);
    lua_getglobal(L, func); /* get function */
    /* push arguments */
    narg = 0;
    while (*sig) {
        /* push arguments */
        switch (*sig++) {
        case 'd': /* double argument */
            lua_pushnumber(L, va_arg(vl, double));
            break;
        case 'i': /* int argument */
            lua_pushnumber(L, va_arg(vl, int));
            break;
        case 's': /* string argument */
            lua_pushstring(L, va_arg(vl, char *));
            break;
        case '>':
            goto endwhile;
        default:
            error(L, "invalid option (%c)", *(sig - 1));
        }
        narg++;
        luaL_checkstack(L, 1, "too many arguments");
    } endwhile:
    /* do the call */
    nres = strlen(sig);
    /* number of expected results */
    if (lua_pcall(L, narg, nres, 0) != 0) /* do the call */
        error(L, "error running function `%s': %s", func, lua_tostring(L, -1));
    /* retrieve results */
    nres = -nres; /* stack index of first result */
    while (*sig) { /* get results */
        switch (*sig++) {
        case 'd': /* double result */
            if (!lua_isnumber(L, nres)) error(L, "wrong result type");
            *va_arg(vl, double *) = lua_tonumber(L, nres);
            break;
        case 'i': /* int result */
            if (!lua_isnumber(L, nres)) error(L, "wrong result type");
            *va_arg(vl, int *) = (int)lua_tonumber(L, nres);
            break;
        case 's': /* string result */
            if (!lua_isstring(L, nres)) error(L, "wrong result type");
            *va_arg(vl, const char **) = lua_tostring(L, nres);
            break;
        default:
            error(L, "invalid option (%c)", *(sig - 1));
        }
        nres++;
    }
    va_end(vl);
}

double callf2 () {
    char filename[] = "pp.conf";
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
    call_va(L, "f", "dd>d", x, y, &z);//f(L, x, y);
    lua_close(L);
    printf ("filename = %s, f(x, y) = %f\n", filename, z);
    return z;
}

int main(void)
{
    //stackDumpTest();
    //test1();
    //printFloats (3,3.14159,2.71828,1.41421);
    //luaL_len_Test();
    //loadConf();
    //loadTable();
    //callf();
    callf2();
}
