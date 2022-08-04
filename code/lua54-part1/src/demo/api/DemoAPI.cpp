#include "DemoAPI.hpp"

#include <iostream>


int demo_cerr(lua_State* state) {
    std::cerr << "Demo zero-arg function" << std::endl;
    return 0;
}

int demo_cerrarg(lua_State* state) {
    // lua_gettop() returns the stack size. At the start of a function, it's equivalent
    // to a statement for getting the argument count. Arbitrary conditions let us define parameter counts
    //if (lua_gettop(state) != 1) {
        //return luaL_error(state, "One argument expected");
    //}

    // Necessary check only for strings. See https://stackoverflow.com/a/4790999/6296561
    // TL;DR: checkstring allows integers and strings
    //luaL_checktype(state, 1, LUA_TSTRING);

    std::cerr <<
        luaL_checkstring(state, 1) << std::endl;

    return 0;
}

// Exercise in the arguments section
int demo_cerrargs(lua_State* state) {
    if (lua_gettop(state) < 1) {
        return luaL_error(state, "Need at least one argument");
    }
    // For loop based on https://stackoverflow.com/a/59097940/6296561
    for (int i = 1; i <= lua_gettop(state); ++i) {
        switch (lua_type(state, i)) {
            case LUA_TNUMBER:
                std::cerr << lua_tonumber(state, i) << " ";
                break;
            case LUA_TSTRING:
                std::cerr << lua_tostring(state, i) << " ";
                break;
            case LUA_TBOOLEAN:
                std::cerr << (lua_toboolean(state, i) ? "true" : "false") << " ";
                break;
            case LUA_TNIL:
                std::cerr <<  "nil ";
                break;
            // Note; userdata has been dropped, as it isn't necessary
        }
    }
    std::cerr << std::endl;
    return 0;
}

int demo_mathmagic(lua_State* state) {
    
    double rawNumber = lua_tonumber(state, 1) + 42;
    lua_pushnumber(state, rawNumber);

    return 1;
}

int luaopen_demo(lua_State* state) {
    // This array contains all the functions exported by your library.
    // The last element has to be {nullptr, nullptr} (or {NULL, NULL} for
    // the readers using C or an old C++ standard), and prior to that, 
    // the entries are in the form of {"function_name_observed_in_lua", function_reference}
    // Worth noting that the Lua name can have nothing to do with the name
    // if your function what so ever, but it's good practice to align these two.
    // Future you and/or whoever else is stuck maintaining whatever code you
    // write will than kyou.
    static const luaL_Reg functions[] = {
        {"cerr", demo_cerr},
        {"cerrarg", demo_cerrarg},
        {"cerrargs", demo_cerrargs},
        {"mathmagic", demo_mathmagic},
        {nullptr, nullptr}
    };
    luaL_newlib(state, functions);

    return 1;
}

