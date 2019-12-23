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
    size_t l = luaL_len(L, -1); /* its length */
    assert(s[l] == '\0');
    assert(strlen(s) <= l);
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
    double zV2 = 0;
    callLuafV2(L, "Luaf", "dd>d", x, y, &zV2);//call Luaf(L, x, y);
    double z =  callLuaf(L, x, y);
    lua_close(L);
    printf ("In %s, Luaf(%f, %f) = %f\n", filename, x, y, z);
    printf ("In %s, Luaf(%f, %f) = %f\n", filename, x, y, zV2);
    return z;
}

void luaapitest() {
    lua_State *L = luaL_newstate();
    printf ("lua_version(NULL) = %f\n", *(double*)lua_version(NULL));
    printf ("lua_version(L) = %f\n", *(double*)lua_version(L));
    ((void)L);
    luaL_checkversion(L);
    lua_close(L);
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
    callfLuafTest();
    //luaapitest();
}
