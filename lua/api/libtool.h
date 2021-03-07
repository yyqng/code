#pragma once
#ifndef _TOOL_H
#define _TOOL_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus //告诉编译器，如果定义了__cplusplus(即如果是cpp文件)
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    #include <lua.hpp>
    using namespace std;
#endif

void stackDump(lua_State *L);

void error (lua_State *L, const char *fmt, ...);

/* call a function `f' defined in Lua */
void callLuaf(lua_State *L, const char *func, const char *sig, ...);

#ifdef __cplusplus
}
#endif
#endif
