#include <cmath>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

static int l_sin (lua_State *L) {
    double d = luaL_checknumber(L, 1);
    lua_pushnumber(L, sin(d));
    return 1; /* number of results */
}

extern "C" int init(lua_State* L)
{
    luaL_openlibs(L); /* opens the standard libraries */

    lua_pushcfunction(L, l_sin);
    lua_setglobal(L, "mysin");
    
    return 0;
}
