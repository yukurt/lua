#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C"
{
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}

void error (lua_State *L, const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

/* call a function 'f' defined in Lua */
double f(lua_State *L, double x, double y) {
    int isnum;
    double z;
    
    /* push functions and arguments */
    lua_getglobal(L, "f"); /* function to be called */
    lua_pushnumber(L, x);  /* push 1st argument */
    lua_pushnumber(L, y);  /* push 2nd argument */

    /* do the call (2 arguments, 1 result) */
    if (lua_pcall(L, 2, 1, 0) != LUA_OK)
        error(L, "error running function 'f': %s",
              lua_tostring(L, -1));
    
    /* retrieve result */
    z = lua_tonumberx(L, -1, &isnum);
    if (!isnum)
        error(L, "function 'f' must return a number");
    lua_pop(L, 1); /* pop returned value */
    
    return z;
}

int main (void) {
    lua_State *L = luaL_newstate();   /* opens Lua */
    luaL_openlibs(L);

    char const* fname = "function.lua";
    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run lua file: %s", lua_tostring(L, -1));

    double z = f(L, 100.0, 1.0);
    printf("z = %f\n", z);
        
    lua_close(L);
    return 0;
}
