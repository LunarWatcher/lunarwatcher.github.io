#pragma once

#include <lua.hpp>


extern int demo_cerr(lua_State* state);
extern int demo_cerrarg(lua_State* state);
extern int demo_cerrargs(lua_State* state);

extern int demo_mathmagic(lua_State* state);

extern int luaopen_demo(lua_State* state);

