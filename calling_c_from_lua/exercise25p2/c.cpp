#include <stdio.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

static void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L); /* depth of the stack */
    for (i = 1; i <= top; i++) { /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING: { /* strings */
            printf("'%s'", lua_tostring(L, i));
            break;
        }
        case LUA_TBOOLEAN: { /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
        }
        case LUA_TNUMBER: { /* numbers */
            printf("%g", lua_tonumber(L, i));
            break;
        }
        default: { /* other values */
            printf("%s", lua_typename(L, t));
            break;
        }
        }
        printf(" "); /* put a separator */
    }
    printf("\n"); /* end the listing */
}

int main (void) {
    lua_State *L = luaL_newstate();
    
    lua_pushnumber(L, 3.5);
    lua_pushstring(L, "hello");
    lua_pushnil(L);
    stackDump(L); /* 3.5 'hello' nil */
    
    lua_pushvalue(L, -2); stackDump(L); /* 3.5 'hello' nil 'hello' */
    lua_remove(L, 1); stackDump(L); /* 'hello' nil 'hello' */
    lua_insert(L, -2); stackDump(L); /* 'hello' 'hello' nil */
    
    lua_close(L);
    return 0;
}
