#include <lua.hpp>

#include "api/Helper.hpp"

int main() {
    demo::LuaHelper helper;
    helper.runFile("lua/tabledemo.lua");
}
