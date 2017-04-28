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

/* assume that table is at the top */
void setcolorfield (lua_State *L, const char *index, int value) {
    lua_pushstring(L, index); /* key */
    lua_pushnumber(L, (double)value / MAX_COLOR); /* value */
    lua_settable(L, -3);
}

void setcolor (lua_State *L, struct ColorTable *ct) {
    lua_newtable(L); /* creates a table */
    setcolorfield(L, "r", ct->red); /* table.r = ct->r */
    setcolorfield(L, "g", ct->green); /* table.g = ct->g */
    setcolorfield(L, "b", ct->blue); /* table.b = ct->b */
    lua_setglobal(L, ct->name); /* 'name' = table */
}

void load_background_colors(lua_State *L) 
{
    lua_getglobal(L, "background");
    
    if (!lua_istable(L, -1))
        error(L, "'background' is not a table");
    
    int red = getcolorfield(L, "r");
    int green = getcolorfield(L, "g");
    int blue = getcolorfield(L, "b");

    printf("background: red=%d green=%d blue=%d\n", red, green, blue);
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

    int i = 0;
    while (colortable[i].name != NULL)
        setcolor(L, &colortable[i++]);

    char const* fname = "config.lua";
    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run config. file: %s", lua_tostring(L, -1));
    
    load_window_dimensions(L);
    load_background_colors(L);
    
    lua_close(L);
    return 0;
}
