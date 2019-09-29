#pragma once
#ifndef _TOOL_H
#define _TOOL_H

#include <stdio.h>
#include <cstring>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <lua.hpp>
using namespace std;

void stackDump(lua_State *L);

void error (lua_State *L, const char *fmt, ...);

/* call a function `f' defined in Lua */
double tool_callf (lua_State *L, double x, double y);

#endif
