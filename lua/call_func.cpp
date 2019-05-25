#include <stdio.h>


//lua头文件
#ifdef __cplusplus
    extern "C" {
#include "lua.h"  
#include <lauxlib.h>   
#include <lualib.h>   
}  
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif


int main(int argc,char ** argv)
{

    lua_State * L=NULL;

    /* 初始化 Lua */  
    L = lua_open();  

    /* 载入Lua基本库 */  
    luaL_openlibs(L);   

    /* 运行脚本 */  
    luaL_dofile(L, "./func.lua");   


    //获取lua中的showinfo函数
    lua_getglobal(L,"showinfo");
    //cpp 调用无参数的lua函数，无返回值
    lua_pcall(L,0,0,0);
    //主动清理堆栈，也可以不调用
    

    
    const char * pstr="世界如此美好";
    lua_getglobal(L,"showstr");
    lua_pushstring(L,pstr);
    //cpp 调用一个参数的的lua函数，无返回值
    lua_pcall(L,1,0,0);
    

    lua_getglobal(L,"add");
    //参数从左到右压栈
    lua_pushinteger(L,2);
    lua_pushinteger(L,3);
    lua_pcall(L,2,1,0);
    printf("lua add function return val is %d \n",lua_tointeger(L,-1));


    /* 清除Lua */  
    lua_close(L);   

    return 1;
}
