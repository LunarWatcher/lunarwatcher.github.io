---
title: "Lua 5.4: introduction to the C API"
date: 2022-08-02T22:00:38+02:00
series: ["lua 5.4"]
tags: ["lua5.4"]
summary: "Lua constantly makes breaking changes to its own API, rapidly making most of the available Lua documentation obsolete. This is an update for Lua 5.4 aimed at beginners to the Lua API."
toc: yes
---

## Preface

This is the first post in a series aimed at using the Lua 5.4 C API, because no other equivalent resources seem to exist at the time of writing, and the official documentation is exhausting to read without previous understanding of how the C API works.

Lua's continued breaking changes doesn't make documenting it easy, for anyone. Including the Lua project itself. Lua's official book (Programming In Lua) is already a version out of date, and has been out of date for a couple years. Odds are also solid that if you search for anything related to the C API, you either find plain Lua questions, or questions with answers that no longer work because of breaking API changes. This also means I'm making a best effort at documenting what I've observed, which may or may not be questionable. However, I still hope anyone not already deep in the Lua C API finds this series to be a time-saver. A lot of time has gone into trial and error to make this series, and the project that sparked it possible.

Unfortunately, if you're reading this in time for 5.5 (or 6.0 if that's how they roll in the future, whenever the next major version is coming), some or all the function calls in this article may be obsolete. If you're not sure whether or not to go with Lua, this is a thing to keep in mind; staying up-to-date with Lua versions requires refactoring on every single minor or major version, to some other another extent. There's nothing preventing you from sticking with 5.4 once implemented of course, but it's worth keeping in mind. I'll likely update this series when the next breaking version is released, under a new series (which I'll link in a more visible place than right here).

---

Back to the C API itself, this series cannot cover everything. It is expected you're familiar with:
* C++17; while this isn't a requirement for the C API itself, it's what I'll be using to make my life easier. The calls to the Lua API remain identical.
* ... and familiarity with a build system, or other compiling methods that you feel work. The demo code uses CMake, but this isn't a requirement for Lua itself
* The general concept of a stack; being familiar with Lua's stack is a bonus, but will be indirectly covered
* The Lua language itself; this is, however, mostly trivial if you're deep enough in programming
* Installation of Lua; if you don't know how to do that, may I recommend [a good package manager](//conan.io)? There's an [excellent CMake plugin](https://github.com/conan-io/cmake-conan) as well.

And it will not cover:
* General API design; though [Factorio](https://lua-api.factorio.com/latest/) is a solid case for demonstrating good API design (and on the other side, neovim shows how _not_ to do a Lua API, but that's a story for another time)
* Programming basics or the basics of Lua; consider taking a dedicated programming course first, or reading a C or C++ book.

The plan for the series, at the time of writing, is:

1. Introduction; Creating a state, intro to the Lua stack, creating libraries, and creating C functions
2. Globals in and out of C(++), and extended C++/Lua interop
3. Tables and metatables
4. Proxy classes and userdata
5. Further entries to be determined at a later time; this list is out of date the second it's posted and won't be updated to reflect further articles. Check the series list for the complete list of posted articles.

As a disclaimer, it's worth noting that I have minimal background in Lua myself, and this series is written alongside an enormous puzzle of trying to figure out what sources still work, what code snippets are up-to-date, and what standards have changed. Consequently, I may and likely have made mistakes, particularly in the redundant code department, or by using practices that no longer apply in later versions. I'll write an errata if/when these show up for bookkeeping.

And finally, I am going to use some design patterns in this series that feel natural to me. However, the critical takeaways should be general execution flow, as well as the methods themselves. How you one day structure your program is fully up to you; I do not make any claims that my system is _the_ system to follow.

With that out of the way, let's get started.

## Demo code

All the code for this article can be found [in the repo for this website](https://github.com/LunarWatcher/lunarwatcher.github.io/tree/master/code/lua54-part1), along with the build system config used. Feel free to rip out the CMake files if you need a place to start, and don't want to set up all the files yourself from scratch.

While the entire source code for the article is available, I highly recommend following along the article first and looking at the code later, or looking at it if you get stuck for any reason, and can't figure it out on your own.

## Lua's state

Lua's C API is centered around `lua_State*`, which you'll both get as an argument from C functions, and that you're going to pass on to all Lua API calls related to the state.

I'm not qualified to talk about the contents of `lua_State` itself, but it doesn't particularly matter unless you're diving into the internals. All you need to know is that it's a pointer that lets lua manage its state, memory, etc., and that you need to pass it to quite a few functions.

### Naming conventions

A convention is to call it `L`, though I don't particularly understand why, and I personally find that to be somewhat awful naming. Consequently, I'll be naming all my state variables `state`, because I've yet to find a better name. However, the convention of calling it `L` is important to remember; If you look for snippets of code on your own, you'll often find some with no context and a "mysterious" `L` parameter. Knowing that `L` is almost always `lua_State` matters.

Naming it `lua` is also pretty common.

However, obligatory note that this is fully irrelevant. The name of the parameter affects absolutely nothing but what you have to write, so do pick whatever name you feel makes sense.

## Defining a C API

In this part, we're going to define a basic C API, as well as play around with basic operations; function arguments and return values, file parsing, and calling C functions from Lua, and vice versa. 

Before continuing, ensure that you have a fully functional "hello world" program; i.e. a `main()` file with Lua properly linked, and a build system set up, if you've opted to use one.

### Creating a `lua_State*`

Before we can do anything, we need to manage our state.

Depending on your application, there are many ways to do this. Personally, I prefer making a helper class for my actual applications, though the actual structure around it isn't particularly important.

Let's make a basic class to manage the state:

```cpp
#pragma once

// Might only be legal with the conan package, or if you make an include equivalent to this yourself.
#include <lua.hpp>

namespace demo {

class LuaHelper {
private:
    lua_State* state;
public:
    LuaHelper();
    ~LuaHelper();
};

}
```

From here, there's a single call required to create the Lua state itself.
```cpp
LuaHelper::LuaHelper() : state(luaL_newstate()) {}
```

As the name of the Lua C API indicates, the API for Lua is written in C. Consequently, there is a cleanup step. All you need to do is `lua_close(state);` when you're ready to throw a state out the window, or under a bus, or whereever it is you feel like throwing your used state today.<sub>Strictly speaking, this isn't required if the lifetime of the helper class is equivalent to that of your program, but it's a good practice anyway, and especially useful if you close and  reopen states regularly for whatever reason.</sub>

```cpp
LuaHelper::~LuaHelper() {
    lua_close(state);
}
```

Now we have a fully functional Lua environment that we can use to run stuff. Sort of.

While lua does have an stdlib, a lot or all of them aren't included by default, and have to be manually enabled. Fortunately, Lua provides a convenient function to load all of them for us to add to the constructor, or a manual init method. For this demo, I'm throwing it in the constructor.

```cpp
// Load the complete lua stdlib
luaL_openlibs(state);
```

You can also load the stdlib libraries individually, but we'll cover that in a bit. Unless you need fine-grained control over which functions are included, you typically want `luaL_openlibs()`

### Running scripts

By now, you have a state, and Lua's stdlib has been loaded into memory. We can now play around with Lua. There are ways to run individual lines, which I'll be disregarding because I don't see any practical use for it. What you're most likely going to use, at least if you have support for external script sources, is files.

There are many ways to structure your files. In my current project, for instance, I use a custom CMake target to copy over a directory (`lua/`) into the build directory, which is where it's easily accessible to me as a command line user.

Regardless, for the sake of the demo, I'm assuming that there's a `lua` directory in the working directory at runtime. Make sure you configure your environment to have this be the case, if applicable.

In case you didn't see where this is going, let's define a new function in our helper class:
```cpp
void runFile(const std::string& file);
```

Strictly speaking, the parameter _could_ be a `const char*`, but I find it substantially easier to take a string and rather convert it for no overhead, compared to you later using a string and converting it to pass to the function you made.

Anyway, to run a file, use `luaL_dofile()`:

```cpp
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
```

At this point, you can play around with Lua. Using:
```cpp
#include <lua.hpp>

#include "api/Helper.hpp"

int main() {
    LuaHelper helper;
    helper.runFile("lua/demo.lua");
}
```

... anything you put in `lua/demo.lua` will be executed. You can also use this system to play with the entirety of plain Lua, should you desire to take the opportunity to play with the language.

If not, or when you're done, it's time to move on to one of the main reasons to embed Lua; customizable APIs.

You're also not limited to just one file. You can run several, or mix it in with line execution (which I won't be covering).

### An initial library

Libraries are just a fancy way of saying a thing you `require`, though I've also seen them called modules. The exact name isn't particularly important. What is, is how they're defined.

First of all, we need a way to load our libraries. This is done with `luaL_requiref()`, and a `lua_pop()` to get rid of an unwanted return value. This is incidentally how the `luaL_openlibs()` method functions internally.

```cpp
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
```

And of course add the declaration in the class, as usual.

This is also the method you'll want to use if you want to load single components of the stdlib, and not the whole thing, though I'll leave that as an exercise to the reader who wants to do that.

#### Name conventions

Before we continue to actually defining libraries, we once again need to cover naming conventions of the C API functions.

Simply put, every library has an `int luaopen_name_of_the_library_in_any_naming_convention(lua_state*)`. It's common practice to prefix all your own methods with the name of the declared library.

Take the `demo` module I'll introduce in a bit; it requires a `luaopen_demo`, and the functions used as a part of the library are typically called `demo_functionname`.

Personally, I stick to this, and use camelCase for the actual module and function names. However, as far as I'm aware, as long as it's valid C/C++, the actual name conventions you apply to the module names are wholly irrelevant.

`luaopen_<blank>` itself is only critical if shared libraries are used to load the library. As demonstrated by the `loadLibrary` function, it takes a `lua_CFunction`, and doesn't care what you name it in your source code.

Worth noting that the names of the functions are partly detached from the name of the perceived module. Lua's convention generally states to use underscores as a period, however, so `demo_abcd_func` is `demo.abcd.func`, but you're free to decide how you name your functions. Adhering to the naming conventions for the "scopes", however, is something I strongly recommend, just in case someone else some day reads your code.

See also the section for package.searchers in [the Lua manual](https://www.lua.org/manual/5.4/manual.html) (which doesn't have anchors; search for `package.searchers`) for details on the automatic shared object loading system.

Obligatory note that I'll have to revisit C API submodules at a later time, because I have no idea how they work at the time of writing.

#### Defining the library

Now, back to the fun part, defining the library.

Now, an `extern "C"` block appears to only be necessary if you're roaming a round shared object space. Otherwise, it isn't necessary. Another thing to note is the return type and values; the return type is always `int` for these functions. The return value represents the number of values returned from the function. Returning values from the function is done implicitly. If you `return 1`, it takes the first element available on the stack as the return value.

**Bonus:** when you've completed `demo_cerr`, what happens if you `print(demo.cerr("any parameter is fine"))`, and change the `return` statement to match the number of arguments you added? Answer later in the post.

We'll need two new files; `DemoAPI.hpp` and `DemoAPI.cpp`. The header is rather short and sweet:
```cpp
#pragma once

#include <lua.hpp>

extern int demo_cerr(lua_State* state);

extern int luaopen_demo(lua_State* state);
```

The names are aligned with the previous section. All the functions take a `lua_State*` argument.

`demo_cerr` is our example function in our example module. This is just an example function that takes zero arguments, does a thing, and returns zero arguments. Let's start with the library loader itself:

```cpp
#include "DemoAPI.hpp"
#include <iostream>

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
        {nullptr, nullptr}
    };
    luaL_newlib(state, functions);

    return 1;
}
```

Revisiting the return types of the function, you'll see this function returns 1 -- why?

`luaL_newlib` has a return value; or rather, it leaves a table at the top of the stack. Modules are just fancy tables as well. Hell, `luaL_newlib` calls `luaL_newlibtable` under the hood. If you make more libraries in the same function, provided they aren't submodules, you can technically return all of them. 

Anyhow, moving on to `demo_cerr`, we've already said no return values. Consequently, it  returns zero. You can do whatever you want with this function; but the demo has a single `std::cerr` in it:
```cpp
int demo_cerr(lua_State* state) {
    std::cerr << "Demo zero-arg function" << std::endl;
    return 0;
}
```

Finally, whereever you decided to load the stdlib (in the demo here, that's in LuaHelper's constructor), add the line `loadLibrary("demo", luaopen_demo)`(don't forget the imports!). What this now means is that our demo Lua script from earlier can import `demo`:

```lua
local demo = require 'demo';
demo.cerr();

print("Hello, World!");
```

### General usage of C functions from Lua

Using C functions in Lua isn't actually as hard as it seems. The Lua end is just like importing another lua file, or an stdlib component. You `require` the applicable library, throw it in a variable, and access its members, and call it like you would any function.

The same cannot be said the other  way around. Calling a Lua function from C requires a bit of code. Consequently, calling Lua functions from C(++) will not be covered in this part of the series.

### The Lua stack

One of the prerequisites for this article was understanding the concept of a stack, because I will not be explaining it in depth.

Lua is centered around a stack for managing memory, and it's where arguments and return values get thrown in, as well as other working memory variables. Numbers returned from functions define how many of the top items in the stack to use as return variables. 

Previously in this article, there was a bonus assignment surrounding modifying the return value of `demo_cerr` and giving it some arguments. The answer is that the input arguments and return values share the same stack, alongside any other parameters created for any reason. Since the function doesn't modify the stack, this means that when the function returns, the only item in the stack is the input parameter. The input then gets used for output, and poof, you have yourself an echo function.

The stack itself is a LIFO queue; the most recent element added gets taken out first. Moreover, there are indices in the stack, that work somewhat non-standard from what you'd expect. Assuming a non-empty stack:

* `-1` defines the top of the stack
* `1` defines the first element of the stack (the stack is one-indexed, no zero-indexed, like you may be used to from many other programming languages, including C/C++)
* `1`, `2`, `3`, ... are all indexed from the bottom
* `-1`, `-2`, `-3`, ... are all relative to the top of the stack.

Visualized; consider a stack of 5 elements. What these are is irrelevant.

The bottom, that's index 1, was pushed onto the stack first. Index 5 was pushed on last. Index 5 can also be addressed with -1, while index 1 can be addressed with -5.

Simply put, the indices are offsets compared to either the top or the bottom, though where the first element is in the first position, rather than in a zero position. There's plenty of proper visualizations on the internet of the stack as well.

Many operations with return types results in values being added to the stack. If you're not sure what you're dealing with in any given situation, [this great Stack Overflow answer](https://stackoverflow.com/a/59097940/6296561) includes a method for printing the stack, which is insanely useful if you're feeling insecure about the Lua stack.

I'll cover the push arguments later, but it's worth taking note of `lua_pop()`. This function removes an item from the stack, and it takes an index in the same system described here. It's particularly useful to get rid of unwanted or temporary values, though that's worth covering later in more depth.

### Arguments and return values

A lot of library functions you make are going to take arguments, and/or return values from the function.

As a heads-up, I'll cover tables with and without metatables, and what exactly both those are, in a later article. For now, we'll stick with primitive input and output types, that being strings, ints, bools, and the obligatory nil (null) value.

#### Arguments

Let's start with arguments; as is tradition, we need a function:
```cpp
extern int demo_cerrarg(lua_State* state);
```

The idea behind this function is to print some argument using the stderr stream. Admittedly, you can already use `io.stderr:write()`, but let's pretend that doesn't exist.

First of all, we need to decide our argument count. We do this with an if statement:
```cpp
// lua_gettop() returns the stack size. At the start of a function, it's equivalent
// to a statement for getting the argument count. Arbitrary conditions let us define parameter counts
if (lua_gettop(state) != 1) {
    return luaL_error(state, "One argument expected");
}
```

The exact condition depends on what you want to achieve. If you only want to allow one argument, you use `lua_gettop(state) != 1`, if you want to check that there is an argument, use `< 1`, etc. In this case, we want to cause an error if we don't or have more than one argument. **Note:** this check is strictly speaking not necessary, as various check functions do the checks for you, and enforce types. In many cases, this means checking the stack isn't important. However, as the exercise later in this section demonstrates, there are places where it's useful.

For the initial function, we'll take a single string, and print it to stderr. We can do this using `luaL_checkstring(state, n)`; `luaL_checkstring` makes sure the nth argument in the stack is a string, and converts it to a `const char*` for you to use in C. In this case, we can skip the intermediate variable and jump straight to the printing:

```cpp
std::cerr <<
    luaL_checkstring(state, 1) << std::endl;
```

It's important to remember that Lua still has no idea what functions you do or don't want exposed. Consequently, the functions array in `luaopen_demo` as to be modified:
```cpp
static const luaL_Reg functions[] = {
    {"cerr", demo_cerr},
    {"cerrarg", demo_cerrarg},
    {nullptr, nullptr}
};
```

And finally, some Lua to play around with it:

```lua
-- This should error
-- demo.cerrarg();
demo.cerrarg("[error] Hello from Lua");
demo.cerrarg(42);
```

... but wait. How is the second statement allowed? 42 is clearly not a string!

This is a [quirk with Lua](https://stackoverflow.com/a/4790999/6296561), and one we can see with internal functions as well. `warn()` also uses `checkstring` under the hood, and also seemingly only takes strings, and yet...

```lua
warn("@on"); -- required, warnings are off by default 
warn(52);
```

> Lua warning: 54

What happens here is that the checkstring function converts integers, and only integers, to strings. Userdata might also be convered, but I don't have a testbench to verify, so this may be a point to address in a later article.

Regardless, nil and booleans still throw an error.

As a last resort for edge-cases like this, we can use `luaL_checktype`:
```cpp
// Necessary check only for strings. See https://stackoverflow.com/a/4790999/6296561
// TL;DR: checkstring allows integers and strings, this makes sure it only takes strings
luaL_checktype(state, 1, LUA_TSTRING);
```

Note that this is prior to the print statement. Depending on your API, however, this won't matter. The Lua API takes care of thet conversion for you, so if the user messes up, that's on them. However, if this isn't desirable, `luaL_checktype()` is there to save the day.

##### What about (other) types?

`luaL_checktype()` can be used for all types, but isn't typically necessary. Unless you absolutely, definitely need to avoid implicit conversion, you only need conversion methods.

These methods are:
* `luaL_checkstring`
    * `luaL_checklstring` -- identical to `checkstring`, but the length parameter lets you get a `size_t` containing the length of the string. This may or may not be necessary
    * `lua_tostring`/`lua_tolstring` -- used by `checkstring` and `checklstring` under the hood.
* `lua_toboolean`
* `lua_tonumber`
* `lua_checkudata`

These functions, as well as other functions are described in detail in [the Lua manual](https://www.lua.org/manual/5.4/manual.html). Tables stand as an exception to these, because it isn't easily converted to a C/C++ form.

In general, these functions do a lot of conversion, including a few unintuitive ones, and aside `luaL_checkstring`/`luaL_checklstring`, there aren't any proper type checks done.

However, quite a lot of this boils down to how dynamic languages work, and this requires special consideration in the API design. How you use the parameters defines what type checks you need for them, if any, and your mileage may vary. If you need strict types and don't want any implicit conversion, `luaL_checktype` is the function for you.

##### What about optional parameters?

Lua does offer a few functions to make these easier:

* `luaL_optstring`/`luaL_optlstring`
* `luaL_optnumber`
* `luaL_optinteger`
* `luaL_opt`

These and other functions are also described in detail in [the Lua manual](https://www.lua.org/manual/5.4/manual.html)

These include a parameter for the default value, if the parameter isn't supplied as a function argument.

As mentioned in the previous section, `luaL_checktype` is more or less a must if you absolutely need specific types with no obscure conversion systems. Unfortunately, there isn't an easy method to let you do this check. You can make a helper function instead:
```cpp
if (lua_gettop(state) >= indexOfRequiredArgument) luaL_checktype(state, indexOfRequiredArgument, type);
```

... where `type` is a constant defined by the Lua API. See the manual entry for `lua_type` for the list of valid constants.

To explain the code, imagine you have a function that takes 3 required arguments, and a fourth optional argument. If three arguments are passed, you know that `lua_gettop()` returns 3. If you have 4 arguments, it returns 4. 

Since our fourth argument is optional, we invoke the helper function (or just replace the index) with 4 for `indexOfRequiredArgument`. If you have two optional arguments (argument 4 and 5 are optional), this still works. `gettop()` returning 5 is still greater than or equal to four, so it still type checks the fourth parameter. Calls to check the fifth parameter still work as normal.


##### Exercise to the reader

Can you modify [the stack printer](https://stackoverflow.com/a/59097940/6296561) and function to allow for an arbitrary number of arguments? Userdata can be disregarded for the time being. The exact format of the output can also be disregarded; whether you use newlines, spaces, or commas is fully irrelevant. Test cases:

```lua
-- Test cases for cerrargs
demo.cerrargs("a", 42);
demo.cerrargs("a", "42");
demo.cerrargs("b");
-- This should also error
--demo.cerrargs()
demo.cerrargs(false, true, false, 420, "a", nil, nil, nil)
```

Don't forget to add your new function to the functions array in `luaopen_demo`!

#### Return values

Previously, I mentioned how the return values work. By returning an int from the C API functions, you define the number of arguments to return. What this means is, simply, that return values are handled by returning the number of arguments from your API functions, and prior to the return, pushing all the return values onto the stack.

As is tradition with the Lua API, there's different functions for different return types:

* `lua_pushstring`
* `lua_pushinteger`
* `lua_pushnumber`
* `lua_pushboolean`
* `lua_pushcfunction`
* `lua_pushnil`
* ... there's quite a few of these, and I highly encourage you to look them up [in the manual](https://www.lua.org/manual/5.4/manual.html)

There's additionally functions for table operations, metatables, and userdata, but those are a topic for another time.

Let's demonstrate one of these; we'll start by defining a function in the header file:
```cpp
extern int demo_mathmagic(lua_State* state);
```

The goal of this function is to take a number as input, add the number 42, and return the value.

We already covered input arguments, so that's straight-forward:
```cpp
double rawNumber = lua_tonumber(state, 1) + 42;
```

Adding in 42 directly saves us a second statement, though I've decided to save it in a variable for clarity in the article. Now we push the number and return 1:

```cpp
lua_pushnumber(state, rawNumber);
return 1;
```

After `pushnumber()`, our stack consists of two elements (or more if there's more arguments); at position 1, there's the input number, and at position 2, there's `inputNumber + 42`, but obviously in the form of a number and not a mathematical expression. If our number was 0, that means position 1 contains the number 0, and position 2 contains the number 42.

As outlined earlier, `return 1` signals to Lua that the top element of the stack (position 2) is a return value. You can verify that it works by running a couple calls against the function:
```lua
print(demo.mathmagic(0));
print(demo.mathmagic(10));
```

However, it's worth noting that in this process, the integers are converted to doubles, to support decimal numbers. This means `demo.mathmagic(0.4)` results in 42.4, rather than 42, 43, or something else, all depending on how the internal rounding is handled when the type is converted from a double to an integer in the Lua API.

Using these together in a bigger example is left as an exercise to the reader, in whatever way you see fit. Until tables become a topic, return values themselves are shockingly trivial, and are much clearer to work with than function parameters. You use a relevant function for the thing you're returning to add the thing to the stack, make your C function return the correct number corresponding to the number of return values, and voila, you have a return value of whatever type you may have.

#### Side-note: memory management and userdata

Userdata and memory or lifecycle management are two topics of potential importance, depending on what it is you're implementing.

Take the io library that's part of Lua's stdlib; it uses metatables to add a custom garbage collection method, that also closes the file pointers. However, tables are a topic for another article, and so are metatables; the plan is to cover those in the third installment to this series.

Without tables, you're constrained on what options you have for return values. As for userdata, that's particularly useful for defining objects in Lua that match objects in your C/C++ code, though interestingly work as an extension of tables.

Regardless, we'll be revisiting this in the future.

#### "I'm confused"

Welcome to the club.

Arguments and return types in Lua are exceptionally heavy in terms of code, and there's a lot of unintuitive bits involved. Particularly surrounding type conversion and other bits around the input, there's a lot of seemingly wildcards, unless you completely familiarize yourself with how the functions work.

If you're struggling to understand the behavior of individual functions, I highly encourage you to play around with them; check what happens when you pass a string to `toboolean`, and if you're actively working on an API, see what happens if you pass some unexpected input.

This article cannot substitute practice; try to make a few test libraries, and stretch the functions as  far as you can. Even though you're currently limited on what you can return, there's still plenty of functions to make for science. Examples include math applications, a manual implementation of `os.execute()`, time parsing

## Closing words

Lua, while a simple language, packs a ton of complexity on the API side of things. Personally, coming from a static programming background, the extreme implicit type conversion is hard to deal with. Functions that seem like they do more than they actually do are also easy to stumble into.

That said, the Lua API is also flexible, and enormous. You're given a boatload of freedom to extend the standard library of the language to whatever special functions or objects you may have. The lack of official documentation (the outdated Programming In Lua doesn't count) does make it an up-hill battle. However, as with everything else, it takes practice.

Lua's types aren't as strict as C/C++ types, and that clearly becomes an issue when trying to extract Lua values into C/C++. Strict type checking isn't done by default, and there's a lot of functions that all seem to do the same thing. It's a jungle.

That all said... it's easier to read the reference manual when you have a rough idea what you're looking for, and that rough idea is what this series aims to provide. By filling in the theory and application gaps the Lua manual and countless outdated don't provide, the goal is to make it easier for you to get up to speed with Lua 5.4 with a background of nothing. That unfortunately means this series isn't a complete replacement for trial and error, which I highly encourage you to take a few moments to do now.

## Useful resources
* [Lua reference manual](https://www.lua.org/manual/5.4/manual.html); useful for finding what functions does, not so much for figuring out what to use if you don't remotely have an idea what you're looking fro
