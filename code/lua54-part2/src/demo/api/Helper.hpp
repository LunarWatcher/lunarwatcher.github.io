#pragma once

// Might only be legal with the conan package, or if you make an include equivalent to this yourself.
#include <lua.hpp>

#include <string>

namespace demo {

class LuaHelper {
private:
    lua_State* state;
public:
    LuaHelper();
    ~LuaHelper();

    void loadLibrary(const char* libName, lua_CFunction f);

    void runFile(const std::string& file);
};

}
