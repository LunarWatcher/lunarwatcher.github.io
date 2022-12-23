---
title: "Lua 5.4: Tables and C interop"
date: 2022-08-02T22:00:38+02:00
series: ["lua 5.4"]
tags: ["lua5.4"]
toc: yes
---

This is part two in the Lua introduction series. This code relies on the LuaHelper class from the last article. This will not be included verbatim here, but the full code for both parts is in [the repo for this website][full-code]. This article assumes you at least understand the topics discussed in the previous article, and they won't be reintroduced.

---

Tables are an incredibly important topic when it comes to Lua. They're unavoidable.

If you're making an API, you're probably going to run into metatables. I'll cover what these are later:tm:, but all you need to know of relevance is that they're tables. Admittedly, metatables do have a different type of construction in many cases, but if you have some dynamic stuff, you'll suddenly dive back into the deep depths of table construction.

In API access, arrays are a type of table as well. Then there's just regular table use in code.

Tables are just key-value pairs that most people with any history of programming have encountered numerous times. They go by many names depending on what programming language you use; dictionary and map are two other words for more or less the same thing. However, this article isn't dedicated to the concept of a table, nor their many implementations. If you're not sure how tables as a data structure work, I recommend finding a good tutorial dedicated to the data structure instead.

This article addresses the somewhat complex construction of tables, as well as arrays, and to have some fun, we'll take a look at getting the value of variables via the API.

## A note on debugging operations

The deeper you go into Lua, the quicker you're going to run into problems. I've had more time to mess around with it as of late, and I've found stack dumping an invaluable tool. In my project, I actually added a method (well, two, but implementation detail) for dumping the stack. If you're struggling to understand how different calls affect the stack, I highly recommend having a dump function on standby, and plugging it in for debug purposes when necessary.

[This Stack Overflow answer](https://stackoverflow.com/a/59097940/6296561) has a good start implementation. While it does work with both C and C++, you can also rewrite it to use standard C++ features.

## Setting up

As previously mentioned, this code builds on LuaHelper from the previous article. This is largely beceause building around a managed utility is a design choice I'm making. This isn't required in your implementation, but I recommend at least reading the code to understand what's going on with abstracted calls. 

Let's start by getting some boilerplate out of the way.

Just like in the previous article, the library has to be defined. I've called this file `TableApi.hpp` (and an equivalent `.cpp`). We'll start with a basic skeleton:

```cpp
#pragma once

#include <lua.hpp>

extern "C" {
extern int tables_get(lua_State* state);

extern int luaopen_tables(lua_State* state);
}
```
```cpp
#include "TableAPI.hpp"

extern "C" {

int tables_get(lua_State* state) {
    // We'll start from here
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
```

And of course load the library in `LuaHelper`'s constructor:
```cpp
loadLibrary("tables", luaopen_tables);
```

I opted not to name this library `table`, on the paranoid impulse that it might conflict with something else. As usual, though, the exact library names are up to you.

The main method is identical to that of the previous article, with the file call changed to run `tabledemo.lua` (or in addition to the other one, if you're running everything in a single project).

## Creating and populating a table

Creating a table in Lua is trivial; you just `x = {"a": "value", "b": "othervalue", "c": [1, 2, 3, "four"]}`, and you're done. In the API, it isn't that easy. 

Creating an empty table is pretty easy:
```cpp
lua_newtable(state);
return 1;
```

if we now run the C++ code with a simple Lua script (the previously mentioned `tabledemo.lua`):
```lua
local lib = require "tables"

print(lib.get())
```

We'll see:

> table: &lt;number&gt;

The `<number>` bit just means a number. This is just how Lua prints tables by default. Don't worry about it; it has no significance for the vast majority of people. If you want to print their content, [that requires extra code](https://stackoverflow.com/a/47656163/6296561), and is left as an exercise to the reader for later. Not much point in doing that with an empty table now, is there?

Now, empty tables are boring. What if we want to add a value to it?

First of all, we need to push this value to the stack:
```cpp
lua_pushstring(state, "I like trains");
```

This doesn't actually change the table, however. To do that, we'll want to use `lua_setfield`:

```cpp
lua_setfield(state, -2, "key");
```
If we now run:
```lua
print(lib.get()["key"])
```
> I like trains

This may be a bit confusing, but here's what's happening:

First, the table is created, and added to the stack. The stack is now [T], where T is our table.

We then push a string. This, again, doesn't do anything to the table itself, but is just appended to the stack. Lua has no idea what you're planning to use it for. You could just have a table, and add a string you're using as a second return value. Now, the stack is [T, "string"].

Then we run `lua_setfield`, which sets the field of a provided t able. It pops the top element of the stack ("string"), and uses it as the value. The third function parameter is used as the key, as already demonstrated. At the time of the execution of the line, the stack has two elements, and this is what you're working from. T is clearly the second last element, so we use `-2`. `1` would've also worked here, but if you first pushed a string before making the table, or a parameter is passed and this isn't checked, this breaks the code.

Or simply put, the table at -2 in the stack has the provided key added, with the value of the key being whatever is at the top of the stack.

And I do indeed mean "whatever". It takes the top of the stack, uses the string provided to the `lua_setfield` call, and adds the key-value pair to the table at the provided place in the stack. What that thing at the top of the stack is doesn't matter. 

You can push an int, you can push a string, you can push a bool, or a nil. You can even do it with a table. Just make sure you understand how your stack operates at every move, and you can construct quite a lot of stuff.

## Creating and populating arrays

## Reading arrays and tables from C++

## Accessing Lua variables from C++

## Example: converting an nlohmann/json object to its equivalent Lua representation

## Closing notes


[full-code]: https://github.com/LunarWatcher/lunarwatcher.github.io/tree/master/code
