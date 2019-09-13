#include <stdio.h>
#include <cstring>
using namespace std;
extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

static void stackDump(lua_State *L){
    int i;
    int top = lua_gettop(L);
    for(i = 1; i <= top; i++){
        int t = lua_type(L, i);
        switch(t){
            case LUA_TSTRING:
                printf("'%s'", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                printf(lua_toboolean(L, i) ? "true":"false");
                break;
            case LUA_TNUMBER:
                printf("%g", lua_tonumber(L, i));
                break;
            default:
                printf("%s", lua_typename(L, t));
                break;
        }
        printf("  ");
    }
    printf("\n");
}
int test(void){

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
    return 0;
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

int main(void)
{
    test();
    //test1();
}
