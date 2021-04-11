#include "libtool.h"

void stackDump(lua_State *L, const char *pre){
    int i;
    int top = lua_gettop(L);      //Return the number of elements.
    printf("%s %d element(s): ", pre, top);
    for(i = 1; i <= top; i++){
        //if (i == 1) {
            printf(" element[%d] ", i);
        //}
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

void callLuaf(lua_State *L, const char *func, const char *sig, ...) {
    lua_getglobal(L, func);
    //if (lua_getglobal(L, func) != 0)
    //    error(L, "error getting function `%s': %s", func, lua_tostring(L, -1));
    int narg = 0;/* number of arguments */
    va_list vl;
    va_start(vl, sig);
    while (*sig) {
        /* push arguments */
        switch (*sig++) {
        case 'd': {/* double argument */
            double d = va_arg(vl, double);
            lua_pushnumber(L, d);
            break;
        }
        case 'i': {/* int argument */
            int i = va_arg(vl, int);
            lua_pushnumber(L, i);
            break;
        }
        case 's': {/* string argument */
            char* c = va_arg(vl, char*);
            lua_pushstring(L, c);
            break;
        }
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
