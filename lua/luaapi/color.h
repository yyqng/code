#pragma once
#ifndef _COLOR_H
#define _COLOR_H

#include "tool.h"

#define MAX_COLOR 255

struct ColorTable {
    const char *name;
    unsigned char red, green, blue;
};

void loadConf ();

/* assume that table is at the top */
void setfield (lua_State *L, const char *index, int value);

void setcolor (lua_State *L, struct ColorTable *ct);

void register_color();

/* assume that table is on the stack top */
int getfield (lua_State *L, const char *key);

void loadTable ();

#endif
