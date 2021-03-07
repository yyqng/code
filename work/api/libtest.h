#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>


void stackDump(lua_State *L);

typedef struct NumArray {
    int size;
    double values[1]; /* variable part */
} NumArray;

typedef struct Student {
    int age;
    char *name;
} Student;

int sum(lua_State *L);
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

//Name of array mylib can be changed.
static const struct luaL_Reg mylib[] = {
    {"lsum", sum},
    {"lsin", mysin},
    {"ldir", dir},
//    {"lmap", map},
    {"lnew_NumArray", new_NumArray},
    {"lNumArray_print", NumArray_print},
    {"lnew_Student", new_Student},
    {"lStudent_print", Student_print},
    {"lsplit", split},
    {"lregref",  regref},

    //{"lnewarray", newarray},
    //{"lsetarray", setarray},
    //{"lgetarray", getarray},
    //{"lgetsize", getsize},

    {"new", newarray},
    {"set", setarray},
    {"get", getarray},
    {"size", getsize},

    {"lnewarrayV2", newarrayV2},
    {"lsetarrayV2", setarrayV2},
    {"lgetarrayV2", getarrayV2},
    {"lgetsizeV2", getsizeV2},

    //{"lnew", newarray},
    {"__tostring", array2string},
    {"__index", setarray},
    {"__newindex", getarray},
    {"__len", getsize},
    {NULL, NULL}
};
