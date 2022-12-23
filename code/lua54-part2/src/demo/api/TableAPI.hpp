#pragma once

#include <lua.hpp>

extern "C" {
extern int tables_get(lua_State* state);

extern int luaopen_tables(lua_State* state);
}
