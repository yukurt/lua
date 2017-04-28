
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

void call_va (lua_State *L, const char *func, const char *sig, ...)
{
    va_list vl;
    int narg, nres; /* number of arguments and results */
    va_start(vl, sig);
    
    lua_getglobal(L, func); /* push function */

// <push arguments (Listing 26.6)>
    for (narg = 0; *sig; narg++) /* repeat for each argument */
    {
        /* check stack space */
        luaL_checkstack(L, 1, "too many arguments");
        
        switch (*sig++)
        {
        case 'd': /* double argument */
            lua_pushnumber(L, va_arg(vl, double));
            break;
        case 'i': /* int argument */
            lua_pushinteger(L, va_arg(vl, int));
            break;
        case 's': /* string argument */
            lua_pushstring(L, va_arg(vl, char *));
            break;
        case '>': /* end of arguments */
            goto endargs;
        default:
            error(L, "invalid option (%c)", *(sig - 1));
        }
    }
endargs:
// end of Listing 26.6
    
    nres = strlen(sig); /* number of expected results */

    if (lua_pcall(L, narg, nres, 0) != 0) /* do the call */
        error(L, "error calling '%s': %s", func, lua_tostring(L, -1));

// <retrieve results (Listing 26.7)>
    nres = -nres; /* stack index of first result */

    while (*sig) /* repeat for each result */
    {
        switch (*sig++)
        {
        case 'd': { /* double result */
            int isnum;
            double n = lua_tonumberx(L, nres, &isnum);
            if (!isnum)
                error(L, "wrong result type");
            *va_arg(vl, double *) = n;
            break;
        }
        case 'i': { /* int result */
            int isnum;
            int n = lua_tointegerx(L, nres, &isnum);
            if (!isnum)
                error(L, "wrong result type");
            *va_arg(vl, int *) = n;
            break;
        }
        case 's': { /* string result */
            const char *s = lua_tostring(L, nres);
            if (s == NULL)
                error(L, "wrong result type");
            *va_arg(vl, const char **) = s;
            break;
        }
        default:
            error(L, "invalid option (%c)", *(sig - 1));
        }
        
        nres++;
    }
// end of Listing 26.7

    va_end(vl);
}

int main (void) {
    lua_State *L = luaL_newstate();   /* opens Lua */
    luaL_openlibs(L);

    char const* fname = "function.lua";
    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run lua file: %s", lua_tostring(L, -1));

    double z;
    call_va(L, "f", "dd>d", 100.0, 1.0, &z);
    printf("z = %f\n", z);

    int greeting_length, name_length;
    call_va(L, "greet", "ss>ii", "welcome", "james", &greeting_length, &name_length);
    printf("greeting_length=%d name_length=%d\n", greeting_length, name_length);
                
    lua_close(L);
    return 0;
}
