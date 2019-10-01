#include "tool.h"

void stackDump(lua_State *L){
    int i;
    int top = lua_gettop(L);      //Return the number of elements.
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
        printf(" ");
    }
    printf("\n");
}

void error (lua_State *L, const char *fmt, ...) {
    va_list vl;
    va_start(vl, fmt);
    vfprintf(stderr, fmt, vl);
    va_end(vl);
    lua_close(L);
    exit(EXIT_FAILURE);
    printf ("won't print\n");
}

/* call a function `Luaf' defined in Lua */
double callLuaf(lua_State *L, double x, double y) {
    /* push functions and arguments */
    lua_getglobal(L, "Luaf"); /* function to be called */
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

void callLuafV2(lua_State *L, const char *func, const char *sig, ...) {
    va_list vl;
    va_start(vl, sig);
    lua_getglobal(L, func); /* get function */

    /* push arguments */
    int narg = 0;/* number of arguments */
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
    }

endwhile:
    /* do the call */
    int nres = strlen(sig); /* number of results */
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
