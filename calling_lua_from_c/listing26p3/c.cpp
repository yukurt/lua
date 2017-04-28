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

#define MAX_COLOR 255

void error (lua_State *L, const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

struct ColorTable
{
    const char *name;
    unsigned char red, green, blue;
} colortable[] =
{
    {"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
    {"RED", MAX_COLOR, 0, 0},
    {"GREEN", 0, MAX_COLOR, 0},
    {"BLUE", 0, 0, MAX_COLOR},
    {NULL, 0, 0, 0} /* sentinel */
};

/* assume that table is on the stack top */
int getcolorfield (lua_State *L, const char *key)
{
    int result;
    lua_getfield(L, -1, key);
    if (!lua_isnumber(L, -1))
        error(L, "invalid component in background color");
    result = (int)(lua_tonumber(L, -1) * MAX_COLOR);
    lua_pop(L, 1); /* remove number */
    return result;
}

void load_colors(lua_State *L, char const* aspect) 
{
    int red = 0, green = 0, blue = 0;
    
    lua_getglobal(L, aspect);
    if (lua_isstring(L, -1)) /* value is a string? */
    {
        const char *colorname = lua_tostring(L, -1); /* get string */
        int i; /* search the color table */
        for (i = 0; colortable[i].name != NULL; i++)
        {
            if (strcmp(colorname, colortable[i].name) == 0)
                break;
        }
        
        if (colortable[i].name == NULL) /* string not found? */
        {
            error(L, "invalid color name (%s)", colorname);
            return;
        }        
        else /* use colortable[i] */
        {
            red   = colortable[i].red;
            green = colortable[i].green;
            blue  = colortable[i].blue;
        }
    }
    else if (lua_istable(L, -1))
    {
        red   = getcolorfield(L, "r");
        green = getcolorfield(L, "g");
        blue  = getcolorfield(L, "b");
    }
    else
        error(L, "invalid value for '%s'", aspect);

    printf("%s: red=%d green=%d blue=%d\n", aspect, red, green, blue);
}

void load_window_dimensions(lua_State *L)
{
    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    
    if (!lua_isnumber(L, -2))
        error(L, "'width' should be a number\n");
    if (!lua_isnumber(L, -1))
        error(L, "'height' should be a number\n");
    
    int w = lua_tointeger(L, -2);
    int h = lua_tointeger(L, -1);
    
    printf("width=%d height=%d\n", w, h);
}

int main (void) {
    lua_State *L = luaL_newstate();   /* opens Lua */
    luaL_openlibs(L);

    char const* fname = "config.lua";
    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run config. file: %s", lua_tostring(L, -1));
    
    load_window_dimensions(L);
    load_colors(L, "background");
    load_colors(L, "foreground");
        
    lua_close(L);
    return 0;
}
