#include <stdio.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

static int stackDump (lua_State *L) {
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

    return 0;
}

extern "C" int init(lua_State* L)
{
    /* register our function */
    lua_register(L, "dump", stackDump);
    
    return 0;
}
