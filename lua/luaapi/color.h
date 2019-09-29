#include "tool.h"

#ifndef _COLOR_H
#define

#define MAX_COLOR 255

struct ColorTable {
    const char *name;
    unsigned char red, green, blue;
} colortable[] = {
    {"WHITE",  MAX_COLOR, MAX_COLOR, MAX_COLOR},
    {"RED",    MAX_COLOR, 0,         0},
    {"GREEN",  0,         MAX_COLOR, 0},
    {"BLUE",   0,         0,         MAX_COLOR},
    {"BLACK",  0,         0,         0},
    {NULL,     0,         0,         0} /* sentinel */
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
