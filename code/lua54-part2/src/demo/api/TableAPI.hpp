#pragma once

#include <lua.hpp>

extern "C" {
extern int tables_get(lua_State* state);
extern int tables_arrget(lua_State* state);

extern int tables_read(lua_State* state);
extern int tables_arrread(lua_State* state);

extern int luaopen_tables(lua_State* state);
}
