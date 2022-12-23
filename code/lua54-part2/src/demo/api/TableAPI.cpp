#include "TableAPI.hpp"

extern "C" {

int tables_get(lua_State* state) {
    lua_newtable(state);
    lua_pushstring(state, "I like trains");
    lua_setfield(state, -2, "key");
    return 1;
}

int luaopen_tables(lua_State* state) {
    static const luaL_Reg functions[] = {
        {"get", tables_get},
        {nullptr, nullptr}
    };
    luaL_newlib(state, functions);

    return 1;
}
}
