#include "tool.h"
#include "color.h"

void loadConf () {
    lua_State *L = luaL_newstate();
    //Optionnal, but good practice?
    luaL_openlibs(L);      // This is necessary for os.genenv(DISPALY)
    //luaopen_base(L);
    //luaopen_io(L);
    //luaopen_string(L);
    //luaopen_math(L);
    char filename[] = "pp.lua";
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
        error(L, "cannot run configuration file: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    if (!lua_isnumber(L, -2))
        error(L, "`width' should be a number\n");
    if (!lua_isnumber(L, -1))
        error(L, "`height' should be a number\n");
    int width = (int)lua_tonumber(L, -2);
    int height = (int)lua_tonumber(L, -1);
    lua_close(L);
    printf ("filename = %s, width = %d, height = %d\n", filename, width, height);
}

/* assume that table is at the top */
void setfield (lua_State *L, const char *index, int value) {
    lua_pushstring(L, index);
    lua_pushnumber(L, (double)value/MAX_COLOR);
    lua_settable(L, -3); // set table[index] = value, then pop index and value
}

void setcolor (lua_State *L, struct ColorTable *ct) {
    lua_newtable(L);              /* creates a table */
    setfield(L, "r", ct->red);    /* table.r = ct->r */
    setfield(L, "g", ct->green);  /* table.g = ct->g */
    setfield(L, "b", ct->blue);   /* table.b = ct->b */
    lua_setglobal(L, ct->name);   /* 'name' = table */
}

void register_color()
{
    lua_State *L = luaL_newstate();
    int i = 0;
    while (colortable[i].name != NULL)
        setcolor(L, &colortable[i++]);
    lua_close(L);
}

/* assume that table is on the stack top */
int getfield (lua_State *L, const char *key) {
    int result;
    lua_pushstring(L, key);
    lua_gettable(L, -2); /* push background[key] and remove key*/

    if (!lua_isnumber(L, -1))
        error(L, "invalid component in background color");
    result = lua_tonumber(L, -1) * MAX_COLOR;
    lua_pop(L, 1); /* remove number */
    return result;
}

void loadTable () {
    char filename[] = "pp.lua";
    lua_State *L = luaL_newstate();
    //Optionnal, but good practice?
    luaL_openlibs(L);      // This is necessary for os.genenv(DISPALY)
    //luaopen_base(L);
    //luaopen_io(L);
    //luaopen_string(L);
    //luaopen_math(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
        error(L, "cannot run configuration file: %s", lua_tostring(L, -1));
    }

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
