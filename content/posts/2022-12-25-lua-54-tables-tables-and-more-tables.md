---
title: "Lua 5.4: Tables and arrays in  the C API"
date: 2022-12-25T23:30:59+01:00
series: ["lua 5.4"]
tags: ["lua5.4"]
summary: "Tables lay the foundation for the more powerful aspects of the Lua language. This article covers the basics of tables, and by extension arrays, as well as some real-world use."
toc: yes
---

This is part two in the Lua introduction series. This code relies on the LuaHelper class from the last article. This will not be included verbatim here, but the full code for both parts is in [the repo for this website][full-code]. This article assumes you at least understand the topics discussed in the previous article, as they won't be fully reintroduced.

---

Tables are an incredibly important topic when it comes to Lua. They're unavoidable for any larger APIs.

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

## Creating tables and arrays

### Creating and populating a table

Creating a table in Lua is trivial; you just `x = {a = "value", b = "othervalue", c = {1, 2, 3, "four"}}`, and you're done. In the API, it isn't that easy. 

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

**TL;DR:** `lua_newtable(state)` makes a new table. When you have a value you want to add to the stack, use `lua_setfield()` to set the field. This also pops the value off the stack

### Creating and populating arrays

Arrays in Lua have a dirty little secret; they're not a separate data object. Arrays are syntactic sugar around tables with numeric IDs. You can verify this on your own:
```lua
print(type({1, 2, 3}))
```
> table

That means to make an array, do the exact same thing as with a table. 

Let's make a new function (`tables_arrget`):

```cpp
int tables_arrget(lua_State* state) {
    lua_newtable(state);
    lua_pushinteger(state, 42069);
    // Now what?
    return 1;
}
```

If you take a [gander at the documentation](https://www.lua.org/manual/5.4/manual.html#lua_setfield), you'll notice that `lua_setfield` takes a C string. `arr["1"]` doesn't exactly have the same feel to it as a proper array. Instead, we have to use `lua_seti` (or `lua_rawseti`). The major difference is that `lua_seti` can call the `__newindex` meta method. 

In many cases, `seti` and `rawseti` are functionally identical, but if lua finds something it interprets as a metatable, `seti` may behave differently than expected. However, in most cases, you're probably fine doing `seti`.

This means the code is:
```cpp
lua_pushinteger(state, 42069);
lua_seti(state, -2, 1);
```

... with 1 symbolising the index. Remember that Lua is 1-indexed rather than 0-indexed, so this being the first element does mean it gets an index of 1. If we want to add another item to the list, same system:
```cpp
lua_pushinteger(state, 123456);
lua_seti(state, -2, 2);
```

Just like `setfield`, `seti` pops the integer off the stack, so `-2` can be used all around, as long as you don't add more than you remove. Adding `tables_arrget` to `luaopen_tables` is left as an exercise to the reader, but after that, you can write some Lua code:

```lua
local arr = lib.arrget();
print(arr);
print(arr[1])
print(arr[2])
```
> table
>
> 69420
>
> 123456

That said, due to arrays secretly being tables, it's perfectly possible to create zero-indexed arrays if you'd prefer. I don't recommend it for consistency, but it's possible. You can even create arrays with negative indices by just changing the indices you pass to `seti`. However, at that point, you no longer have an array. You can also have non-continuous indices if you'd prefer.

I highly recommend reading the [Lua documentation on arrays](https://www.lua.org/pil/11.1.html), and taking a moment to play around with both table and array creation before continuing.

**TL;DR:** arrays are secretly tables. They're made with `lua_newtable`, and construction is almost identical to arrays, but using `seti` instead. `seti` replaces `lua_setfield` from table construction. Arrays being tables also means you can have negative and/or non-continuous indices.

### `lua_settable`

`lua_setfield` and `lua_seti` are both effectively utilities; they let you inline the operations you can do with `lua_settable`. 

Both `setfield` and `seti` are restricted to strings and integers respectively. For normal arrays, you don't need anything fancy; both `seti` and `pushinteger` followed by `lua_setttable` work. 

But what if you want a double key, for instance?


Going back to `tables_get` for a moment, you can:
```cpp
// Push the key; the key has to be first thanks to how 
lua_pushnumber(state, 78.9);
// Push the value
lua_pushstring(state, "Foxes are adorable");
// And add table[78.9] = "Foxes are adorable"; note that the stack is [table, double, string], so the table is -3
lua_settable(state, -3);
```

And the accompanying Lua:
```lua
print(lib.get()[78.9]);
```
> Foxes are adorable

### Summary

I'm aware introducing two methods and then introducing a third method isn't the best way to go about this, but it's the short and sweet approach.

In many table contexts, I personally find myself using only string keys, except when going into non-continuous numbers or effectively arrays with negative indices, so I personally find these methods extremely helpful in cutting down code.

Lua's C API does have a bit of a problem with function sprawl and awkward function names, so here's a TL;DR:

* If you're making an array, you can use `seti`
* If you're making a table with string keys, you can use `lua_setfield`
* If you're making a table with keys of any other type, you can use `lua_settable`, though this function can also be used as an (admittedly boilerplate) alternative to `lua_setfield`/`lua_seti`
* You can mix and match functions however you see fit. If you have a hydra table consisting of integer, double, and string keys, there's nothing preventing you from using `seti` and `lua_setfield` where you use int and string keys respectively, and using `lua_settable` everywhere else. 

I also highly recommend you take a minute to explore these functions to get comfortable with them. Because tables are such a big deal in Lua, it's a very good idea to understand and explore these now.

## Reading arrays and tables from C++

Producing tables is one thing, but you may want to consume them as well. Let's start with tables. As usual, connecting the method to `luaopen_tables` is left as an exercise to the reader.

For this example, we'll look for specific indices of importance, and return an explanatory string. Let's start with the basic framework
```cpp
int tables_read(lua_State* state) {
    // Ensure the argument passed is a table.
    luaL_checktype(state, 1, LUA_TTABLE);

    // check code goes here

    // Push the string to the stack
    lua_pushstring(state, "Yawn. I've seen more exciting tables at my local IKEA");
    // And as usual, the top n elements (n = 1 when we return 1) on the stack become return values.
    return 1;
}
```

When it comes to tables, there are a few key methods:
* `lua_gettable` ([docs][lua-gettable]; tables and arrays) - takes the top element on the stack as the key, pops the key, and pushes the value of table[key] to the stack. This is, by a solid margin, one of the more powerful access functions
* `lua_getfield` ([docs][lua-getfield]; tables): Three-argument constructor that can relatively easily be used as an alternatiev to `lua_gettable` for string access. Similarly to `lua_setfield`, this only works on string keys. For many applications, this is the more extensively and easily used 
* `lua_geti` ([docs][lua-geti]; arrays): equivalent to `lua_getfield`, but with an integer parameter instead of a string parameter.
* `lua_next` ([docs][lua-next]; tables and arrays) - iterates the table.

With the three former, the same discussion from the summary on table creation applies; the `get` variants here are exact counterparts of the `set` functions

In this particular example, we'll be using `lua_getfield`, as the idea is string keys. As an exercise to the reader, you can rewrite the function using `lua_gettable` or `lua_next` (or both, separately of course) if you'd like to get used to these.

Back to the example:

```cpp
// Look for the `pirate` key
lua_getfield(state, -1, "pirate");
if (!lua_isnil(-1)) {
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
// This isn't strictly speaking required, it just ensures `-1` stays the table. If not, the table access
// index has to be incremented by 1 every time a value is checked.
lua_pop(state, 1);
```

In this case, we just return the element at the position. You don't even need to check its value. You may want to check the type, as it could return a non-string, but that's left as an exercise to the reader.

There's lots of options, though. You could push a new string and return it instead:
```cpp
lua_getfield(state, -1, "insert");
if (!lua_isnil(state, -1)) {
    // For this particular example, we'll check some values:
    std::string field = lua_tostring(state, -1);
    if (field == "ploop") {
        lua_pushstring(state, "You should probably put some oil on that.");
        return 1;
    } else if (field == "I use arch btw") {{
        lua_pushstring(state, "Oh no, not one of those");
        return 1;
    }
}
lua_pop(state, 1);
```
Here's two examples of Lua code:
```lua
print(lib.read({
    insert = "ploop",
    explode = "boom",
    pirate = "Enceladus corp would like to know your location"
}))
```
> Enceladus corp would like to know your location

<sub><sub>Yes, that is a [deltaV: Rings of Saturn](https://store.steampowered.com/app/846030/V_Rings_of_Saturn/) reference. No affiliation, it's just a really good game</sub></sub>

```lua
print(lib.read({
    insert = "I use arch btw",
    explode = "boom",
}))
```
> Oh no, not one of those


Equivalently with arrays and a dumb addition system because I'm running out of ideas:

```cpp
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
```

Example Lua:
```lua
print(lib.arrread({1, 4, 3, 4}))
print(lib.arrread({7}))
```
> 5
> 
> Failed to load lua/tabledemo.lua: lua/tabledemo.lua:36: Need at least two elements

## Example: converting an nlohmann/json object to its equivalent Lua representation

This is a real-world example based on [upm][upm], where I needed to add a JSON parsing API. There's two ways to go about this:

1. Userdata
2. Just converting it to a lua representation

I chose the latter in my implementation, because userdata in a data structure with a theoretical max depth of effectively infinity presented several problems with data management.

Note that to run this, you need nlohmann/json set up in your repo. The code is fairly straight-forward, however, and you might be able to figure out what it does just by reading the code:

```cpp
// This function is a recursive helper function. It was not registered in the `luaopen` function for this module.
void upmjson_parseInternal(lua_State* state, const nlohmann::json& json) {
    // first, there's a set of primitives. All these are pushed in their raw form.
    // This also ensures JSON just consisting of one of these primitives is allowed, as it is valid JSON.
    if (json.is_null()) {
        lua_pushnil(state);
    } else if (json.is_number_integer()) {
        lua_pushinteger(state, json.get<long long>());
    } else if (json.is_number_float()) {
        lua_pushnumber(state, json.get<double>());
    } else if (json.is_string()) {
        lua_pushstring(state, json.get<std::string>().c_str());
    } else if (json.is_array()) {
        // Arrays is where stuff gets interesting
        lua_newtable(state);
        // This keeps track of the index used
        int index = 0;
        for (auto& value : json) {
            // The recursive call takes care of the values. If it's a primitive, the stack just contains that primitive.
            // Complex objects, such as tables, also become the last element on the array after
            // all the interation is done.
            upmjson_parseInternal(state, value);
            // And as previously demonstrated, the table at -2 is assigned the value at -1 in the stack,
            // associated with the key at the current index. Since Lua is 1-indexed, index being
            // set to 0 inlines the addition operation, as we can let the result of adding 1 be the index.
            lua_rawseti(state, -2, ++index);
        }
    } else if (json.is_object()) {
        lua_newtable(state);
        // The idea is identical for maps, but this time...
        for (auto& [k, v] : json.items()) {
            upmjson_parseInternal(state, v);
            // k.c_str() is used because json keys are always strings: https://stackoverflow.com/q/8758715/6296561
            lua_setfield(state, -2, k.c_str()); // step[k] = v
        }
    } else {
        // catch-all for uncaught primitives, because I might've missed stuff.
        throw std::runtime_error("bad JSON parsing");
    }
}

// This is the function that gets exposed via the module's luaopen.
int upmjson_parse(lua_State* state) {
    // First, convert the string to an nlohmann::json object
    auto json = nlohmann::json::parse(luaL_checkstring(state, 1));
    // Then recurse
    upmjson_parseInternal(state, json);

    return 1;
}
```

## Example: pushing module globals

Guess what `luaL_newlib` does under the hood?

If you guessed it makes a table, you're absolutely correct.

This allows you to define module-level variables<sup>\*</sup>:
```cpp
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
```
```lua
local lib = require "tables"
print(lib.theAnswer)
```
> 42

You can also add functions after the fact with this approach, or anything else Lua has push functions for (tables, primitives, userdata, ...).

<sup>\*: Constants can be supported as well, but due to complications of Lua, this requires metatables, which I have not covered yet. There doesn't appear to be any API functions to declare constants at this time, even though Lua 5.4 [does support constants][lua-const]. Tables may be exempt from the attribute system anyway</sup>

## Summary

Tables in the Lua API aren't fundamentally hard to understand, but there's a lot of functions and mechanics that "feel" unintuitive compared to many programming languages, where adding to tables or arrays is abstracted in functions or syntactic sugar. The many function calls add up, making table definitions look far scarier than they actually are.

The Lua API doesn't have any of those features, so it has to split into different functions to represent the same operations we often can do in far fewer lines. 

The important functions for creating tables are:
* `lua_settable`
* `lua_setfield`
* `lua_seti`

And for reading tables:
* `lua_gettable`
* `lua_getfield`
* `lua_geti`
* `lua_next`

There's tables in many places you might not expect, and these usually operate as normal tables. Module definitions, introduced here as `luaopen_<module name (without brackets)>`, are also tables, allowing all the standard table-related operations, such as adding variables.

Along with the very basics (for obvious reasons), everything related to tables (notably creation and modification, reading, and the still unintroduced metatables) are the most important topics in Lua by a wide margin. Learn your tables, and Lua becomes a lot more manageable.

Despite Lua's developers introducing breaking changes in every minor version (against all versioning practices, but that's an aside), the API changes are far easier to learn when you understand how Lua operates, and understand the single most powerful construct in the language, and the topic of a future article on Lua: metatables.

[full-code]: https://github.com/LunarWatcher/lunarwatcher.github.io/tree/master/code
[lua-next]: https://www.lua.org/manual/5.4/manual.html#lua_next
[lua-gettable]: https://www.lua.org/manual/5.4/manual.html#lua_gettable
[lua-rawget]: https://www.lua.org/manual/5.4/manual.html#lua_rawget
[lua-getfield]: https://www.lua.org/manual/5.4/manual.html#lua_getfield
[lua-geti]: https://www.lua.org/manual/5.4/manual.html#lua_geti
[upm]: https://github.com/LunarWatcher/upm
[lua-const]: https://stackoverflow.com/a/58224960/6296561
