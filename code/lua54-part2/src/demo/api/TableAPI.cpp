#include "TableAPI.hpp"

#include <string>
#include <iostream>

extern "C" {

int tables_get(lua_State* state) {
    lua_newtable(state);
    lua_pushstring(state, "I like trains");
    lua_setfield(state, -2, "key");

    // Push the key; the key has to be first thanks to how 
    lua_pushnumber(state, 78.9);
    // Push the value
    lua_pushstring(state, "Foxes are adorable");
    // And add table[78.9] = "Foxes are adorable"; note that the stack is [table, double, string], so the table is -3
    lua_settable(state, -3);
    return 1;
}

int tables_arrget(lua_State* state) {
    lua_newtable(state);
    lua_pushinteger(state, 42069);
    lua_seti(state, -2, 1);
    lua_pushinteger(state, 123456);
    lua_seti(state, -2, 2);

    return 1;
}

int tables_read(lua_State* state) {
    // Ensure the argument passed is a table. Note that this 
    luaL_checktype(state, 1, LUA_TTABLE);

    // Look for the `pirate` key
    lua_getfield(state, -1, "pirate");
    if (!lua_isnil(state, -1)) {
        // If the field isn't nil, the key exists.
        // For the sake of demonstration, we'll just return it.
        // Error checking to make sure the field is in fact a string could be done here.
        return 1;
    }
    // remove the field's value from the stack.
    // Unlike many of the other functions, `lua_pop` uses a count rather than
    // specific indices. Passing 2 instead of 1 removes the top 2 elements.
    // It does not (necessarily) remove the element at position 2, unless there's
    // few enough elements on the stack for the second item to be eaten in by n = 2.
    lua_pop(state, 1);

    // Look for the insert key
    lua_getfield(state, -1, "insert");
    if (!lua_isnil(state, -1)) {
        // For this particular example, we'll check some values:
        std::string field = lua_tostring(state, -1);
        if (field == "ploop") {
            lua_pushstring(state, "You should probably put some oil on that.");
            return 1;
        } else if (field == "I use arch btw") {
            lua_pushstring(state, "Oh no, not one of those");
            return 1;
        }
    }
    lua_pop(state, 1);

    // Push the string to the stack
    lua_pushstring(state, "Yawn. I've seen more exciting tables at my local IKEA");
    // And as usual, the top n elements (n = 1 when we return 1) on the stack become return values.
    return 1;
}

int tables_arrread(lua_State* state) {
    luaL_checktype(state, 1, LUA_TTABLE);

    lua_geti(state, -1, 1);
    if (lua_isnil(state, -1)) {
        return luaL_error(state, "Need at least two elements");
    }
    int sum = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_geti(state, -1, 2);
    if (lua_isnil(state, -1)) {
        return luaL_error(state, "Need at least two elements");
    }
    sum += lua_tointeger(state, -1);
    lua_pop(state, 1);
    
    lua_pushinteger(state, sum);

    return 1;
}

int luaopen_tables(lua_State* state) {
    static const luaL_Reg functions[] = {
        {"get", tables_get},
        {"arrget", tables_arrget},
        {"read", tables_read},
        {"arrread", tables_arrread},
        {nullptr, nullptr}
    };
    luaL_newlib(state, functions);

    lua_pushinteger(state, 42);
    lua_setfield(state, -2, "theAnswer");

    return 1;
}
}
