#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

#include "libtool.h"


typedef struct NumArray {
    int size;
    double values[1]; /* variable part */
} NumArray;

typedef struct Student {
    int age;
    char *name;
} Student;

int wkmain(lua_State *L);
int wkinit(lua_State *L);
//int sum(lua_State *L);
int mysin (lua_State *L);
int dir (lua_State *L);
//int map (lua_State *L);
int new_NumArray (lua_State *L);
int NumArray_print (lua_State *L);
int new_Student (lua_State *L);
int Student_print (lua_State *L);

int split (lua_State *L);
int regref(lua_State *L);

int newarray (lua_State *L);
int setarray (lua_State *L);
int getarray (lua_State *L);
int getsize (lua_State *L);

int newarrayV2 (lua_State *L);
int getsizeV2 (lua_State *L);
int setarrayV2 (lua_State *L);
int getarrayV2 (lua_State *L);

int array2string (lua_State *L);
