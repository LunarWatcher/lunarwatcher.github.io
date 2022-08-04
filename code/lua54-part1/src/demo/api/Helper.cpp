#include "Helper.hpp"

#include <iostream>
#include <exception>
#include <string>

#include "DemoAPI.hpp"

namespace demo {

LuaHelper::LuaHelper() : state(luaL_newstate()) {
    // Load the complete lua stdlib
    luaL_openlibs(state);
    loadLibrary("demo", luaopen_demo);
}

LuaHelper::~LuaHelper() {
    lua_close(state);
}

void LuaHelper::loadLibrary(const char* libName, lua_CFunction f) {
    // Equivalent to Lua's `require` keyword, though it also
    // lets us define a loading function, which is necessary
    // when the libraries aren't separate .so files, according to some sources.
    // ... sort of. In the case of our `demo` libary, you can't just `demo.cerr()`
    // even though the docs call this equivalent to the require keyword.
    //
    // That all said, this is one of the few things that keep changing between versions of Lua.
    // There's minimal documentation on it, and much less why it does what it does.
    luaL_requiref(state, libName, f, 1);
    // At least this isn't too bad.
    // requiref leaves the module on the stack, and we don't want it.
    // Yeet it away
    // We'll revisit the stack later; all you need to know is that the previous
    // call adds a thing to the stack, and we don't want it there.
    lua_pop(state, 1);
}

void LuaHelper::runFile(const std::string& file) {
    // Run the file; if the file errors out, the function returns LUA_OK (generally defined as 0)
    if (luaL_dofile(state, file.c_str()) != LUA_OK) {
        // `lua_tostring(state, -1)` returns the top element in the Lua stack. If luaL_dofile errors out, the top of
        // the stack is an error message that you can use to display some more useful information.
        std::cerr << "Failed to load " << file << ": " << lua_tostring(state, -1) << std::endl;

        // The program doesn't _have_ to be terminated if the script fails. This is my lazy way out of
        // any proper error handling when the successful execution of the script is pretty important.
        //
        // Obviously, don't do this if your application has different error handling strategies. The important
        // part is lust `luaL_dofile()` in an if statement, and `lua_tostring(state, -1)` if the value isn't zero.
        throw std::runtime_error("exec failed");
    }
}

}
