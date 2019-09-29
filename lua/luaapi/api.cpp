#include "color.h"

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
int test1(void)
{
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();//lua_open(); // opens Lua 
    luaopen_base(L);   // opens the basic library 
    luaopen_table(L);  // opens the table library 
    luaopen_io(L);     // opens the I/O library 
    luaopen_string(L); // opens the string lib. 
    luaopen_math(L);   // opens the math lib. 
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
    size_t l = luaL_len(L, -1); /* its length */
    assert(s[l] == '\0');
    assert(strlen(s) <= l);
    lua_close(L);
}

double callf () {
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
    double z = tool_callf(L, x, y);
    lua_close(L);
    printf ("filename = %s, tool_callf(x, y) = %f\n", filename, z);
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
    call_va(L, "tool_callf", "dd>d", x, y, &z);//tool_callf(L, x, y);
    lua_close(L);
    printf ("filename = %s, tool_callf(x, y) = %f\n", filename, z);
    return z;
}

int main(void)
{
    //stackDumpTest();
    //test1();
    //test2();
    //printFloats (3,3.14159,2.71828,1.41421);
    //lualenTest();
    //loadConf();
    loadTable();
    //callf();
    //callf2();
}
