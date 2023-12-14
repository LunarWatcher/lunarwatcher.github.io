---
title: "Installing projects with CMake is unnecessarily difficult"
tags: ["cmake"]
date: 2023-12-14T19:04:58+01:00
---

There is no easy way to install stuff with CMake. Sort of. CMake has an `install()` function that deals precisely with installation, and is used to generate an `install` target for your favourite generator. That should really be the end of it. 

If the size of the scrollbar didn't give it away already, it isn't.

`install()` should be the way to make it easy, but it has a bunch of complications and seemingly pointless restrictions that just make it obnoxiously difficult to set up.

For example, if you have any dependencies that themselves use `install()` in their own CMakeLists, you're going to run into some problems. In my case, the problem was that I had several dependencies that declared it, and they used it to install headers. That's fine if the goal is installing the dependency standalone and system-wide, not so much when I only want to install shared objects and binaries, as well as various files. 

For example, [libcpr][libcpr][^1] installs both headers and static libraries, while I only want my executable to install. The install location isn't in `/usr/`, so it isn't part of the search path, and I don't want to install non-shared objects to avoid conflicts with system packages. Yet, the install process installs a bunch of crap that I do not want installed. Fixing this, or otherwise running CMake in a way that only installs executables, is surprisingly non-trivial.

## Preventing installs of non-runtime files

Headers and static libraries do not need to be part of the install. Disabling them is not so easy.

There's two options:
1. If it exists, use a per-library switch to disable installation targets in the dependency
2. If this isn't offered, or you can't be arsed to dig it up, add `EXCLUDE_FROM_ALL`.

### FetchContent and `EXCLUDE_FROM_ALL` with CMake 3.27 and below

In 3.27.x and below, the only way to EXCLUDE_FROM_ALL is to use GetProperties, and use EXCLUDE_FROM_ALL in the subdirectory declaration.

```cmake
FetchContent_Declare(cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.0)

FetchContent_GetProperties(cpr)
if (NOT cpr_POPULATED)
    FetchContent_Populate(cpr)
    add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
```

This is not _nearly_ as compact as a normal FetchContent declaration.

### FetchContent and `EXCLUDE_FROM_ALL` with CMake 3.28 and above

CMake 3.28, which at the time of writing was released 8 days ago, simplifies the process significantly. 
```cmake
FetchContent_Declare(cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.0
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(cpr)
```

### `EXCLUDE_FROM_ALL` with a subdirectory

As indirectly demonstrated in the FetchContent approach for 3.27 and below, if you're using a submodule, just add `EXCLUDE_FROM_ALL` to the declaration:
```cmake
add_subdirectory(your-dep EXCLUDE_FROM_ALL)
```

This works wonders for avoiding building test dependencies unless explicitly building tests as well, by the way.

### When is this even a problem?

This is primarily a problem for "end projects", i.e. projects that can't be directly reused. Examples of this are primarily executables of various kinds, where the project itself isn't intended to be re-linked into other things. 

Particularly, it matters when the dependencies themselves aren't externally managed, but are rather handled directly by the project. The main motivation to do so is ensuring all required features are available, which isn't a guarantee with certain package managers, where the packages are often very out-of-date. See Debian's package manager, for example. This also propagates down to Ubuntu and its derivatives. 

For example, in 2023, apt offers me Node 12.22, the previous LTS, which is now unsupported by a lot of software. The state of Linux package managers is an entirely different problem, however, and one that's discussed in much more detail elsewhere.

## No automated installation dependency resolution

In spite of CMake being aware of every dependency built by CMake, you can't just define
```cmake
install(TARGET your-executable)
```

and have CMake install every `.so`/`.dll` for you. That would be too easy. 

Granted, there are some good reasons for this, and some outdated reasons, some of which are outlined [here](https://stackoverflow.com/a/52110751/6296561) (as a side-note, a different answer mentions `IMPORTED_RUNTIME_ARTIFACTS`, but it still requires explicit declaration). However, these aren't brand new issues that no one has solved before. There are many build systems that have far easier installation and packaging systems than CMake, though the ones I'm aware of are not for C++.

One of the alleged problems is already fixed. FetchContent sorts out the [dependency diamonds](https://en.wikipedia.org/wiki/Dependency_hell#Problems) entirely on its own, and makes the targets available to the global scope anyway, so dependency conflicts are less of a concern.

I spent a few hours trying to figure this out, and the answer just seems to be "no, deal with it", when it seems like it'd be a non-issue with a more sane installation system. Again, many other build systems have already figured this out. Many other languages have trivial installation systems, and that deals with dependency conflicts entirely by themselves.[^3] To be fair, some of these languages are very different to C++, and need very different build systems. However, it does mean that a lot of the alleged problems have been solved many times already.

### Target resolution

One thing I noticed (and that infuriated me) is that CMake will loudly complain if you try to feed `install(TARGET)` with an alias. Again using libcpr as an example, it exports a target named `cpr::cpr`, which is just an alias for the library. 

For example, if you try
```cmake
install(TARGETS cpr::cpr)
```

You'll get the wonderful message "install TARGETS given target '[target name]' which is an alias". Then it resolves the alias to the actual binary, and I'm kidding. That would be too easy. [The build fails](https://github.com/LunarWatcher/doesnotfail2ban/commit/8670030a7b0d2bccb9ebbba45d08070906d09114). There's exactly 0 good reasons _not_ to resolve an alias, but CMake refuses to anyway.

In fact, CMake is actually capable of doing this resolution, as will be demonstrated in my final workaround. They just [chose not to support it with TARGETS](https://cmake.org/cmake/help/latest/command/add_library.html#alias-libraries), and I'm not going to pretend to understand why.

This is one of the unnecessary

## Why CMake's `install()` function and install system is overcomplicated

Different packages have different installation needs in different contexts. That's fine. If I were to install cpr directly, for example, and install it system-wide, I would want the headers and pre-compiled shared library to be installed. 

It therefore, objectively, makes sense for each library to have install instructions when required. I shouldn't have to declare installs for libraries when they can better write the install functions, and better know what dependencies they have. CMake can detect conflicts, if any, and then let the developer sort those out. This, possibly minus CMake detecting diamond conflicts, is already partly happening today. The reason my install system installed a bunch of crap was precisely that these libraries had their own install instructions. 

The next question then becomes, how can the installations be scoped? This is where CMake starts being bad. 

### Missing COMPONENT standards

CMake has a [`COMPONENT`](https://cmake.org/cmake/help/latest/command/install.html#introduction) option. This is _the_ solution to the problem, had it been set up properly. 

What you instead have is that COMPONENT isn't required, and the component names are fully optional. If they aren't used, the install gets chucked into an `Unspecified` component, which is the one installed when no component is specified. If every single library with install instructions agreed to use `Runtime` for binaries required at runtime, and `Development` for headers and static libraries, I could just specify `-DCOMPONENT=Runtime` and not have any of these problems. 

However, according to the [CMake documentation](https://cmake.org/cmake/help/latest/command/install.html#introduction),
> If COMPONENT is not provided a default component "Unspecified" is created.

This means nothing is sorted automatically when no components are provided, which means there's no common standards[^2]. When there's no standards, what you get instead is chaos. Libcpr doesn't use COMPONENT at all. SQLiteCpp uses `libraries`, but only for the binaries. All the development stuff (including headers) is in the aforementioned "Unspecified" target, that gets automatically installed.

### Most of the solution is already here

`COMPONENT`, and possibly `CONFIGURATIONS`, are the solution. However, because there's no standards, it's often not used in a way that would simplify installation. Instead, there are a bunch of non-standard component names that would all have to be installed separately outside a full install. That assumes COMPONENT is actively used.

Even when it is, as demonstrated by SQLiteCpp, it doesn't use any particularly obvious standards, which means you can't just use a standard command. Imagine running `install -DCOMPONENT=Runtime`, and all the runtime dependencies get installed. This would massively simplify the installation system from an end-user's point of view.

Unfortuantely, I have not seen that many libraries actually make use of COMPONENT. This is in spite of the  `COMPONENT` option not being new. Also fun, in CMake 3.6, `EXCLUDE_FROM_ALL` was introduced as an option to the `install()` function, which means the target is only installed as part of the installation of a component, and not the full installation.

### Caveats

It's worth noting that I'm blatantly ignoring certain challenges here. As mentioned in a footnote[^2], libraries like Boost represent a challenge here. If built as a monolithic repo, a multi-module library where not all the components have to be installed to use specific components might want to use `COMPONENT` to specify which of these modules to install, seeing as `CONFIGURATIONS` is not really meant for modules, but rather, the install type. 

Due to this, fixing install isn't as easy as just "standardise COMPONENT and it'll be fine". A new MODULE flag might have to be introduced, but if that's considered a problem for backwards compatibility, a brand new flag for the install type might have to be used instead. 

If the install system was built from scratch today, most of these challenges could've been addressed. However, `install()` is old, and has been expanded over time to account for new requirements. As a result, it has gotten messy over the years.

## My workaround solution for installations

In summary, `install(TARGETS)` is flaky, you need to explicitly list dependencies no matter what works, and install doesn't resolve aliases[^4]. What _can_ you do then?

First of all, `EXCLUDE_FROM_ALL` any and all dependencies with their own install instructions, provided they don't conveniently happen to not install more than they have to. Determining which dependencies this applies to can be done by running `make install` (or similar for non-make generators) and seeing which files gets installed.

Funnily enough, this seems to be required no matter what exact commands are used for installation.

The solution I settled for is ugly, but it works. Rather than try to install targets or any other modes, I use the `PROGRAMS` and `FILES` modes. The only difference between these two is that `PROGRAMS` sets the executable bit, so the files installed remain executable. Otherwise, it's just a file-based copy operation. This does not avoid manual declaration operations. It's just a tiny step above just giving up and using a shell script to sort stuff out.

By using generator expressions, you can specify which targets to install. This requires manually checking which targets generates shared objects in need of installation, but that can be done with a simple build, followed by checking the folder.

What you then end up with is this:
```cmake
install(PROGRAMS
        $<TARGET_FILE:dnf2b>
    DESTINATION bin)
install(FILES
        $<TARGET_FILE:fmt::fmt>
        $<TARGET_FILE:cpr::cpr>
        $<TARGET_FILE:SQLiteCpp>
        $<TARGET_FILE:spdlog>
    DESTINATION lib)
```

Using the `TARGET_FILE` generator expression, only the relevant binaries need to be copied. Again, which targets need to be copied as files is done by manually checking which libraries are built as shared libraries. Hell, it even follows aliases, something `install(TARGET)` doesn't do _by design_. 

Granted, some of the challenges I've had can probably be resolved by using system libraries instead, because that would mean they're already installed. I have good (ish) reasons not to, but that's not something I'm going to mention in this already long article.

## Simplifications matter

In my case, I don't operate with that many dependencies, so this solution is acceptable. It's another thing to remember when I add another dependency, which I guarantee you I'm going to forget at some point. 

However, for bigger software with more dependencies than I have, managing installations when the system is seemingly intentionally overcomplicated is not great. Increasing the complexity for shipping software is usually not a good thing, and only serves to add excessive overhead to the development process.

Fortunately, CMake is still evolving, and I hope the installation system is next in line for some overdue attention in the near future.


[^1]: I use cpr as a recurring example because it's convenient to do so. However, cpr is far from the only, and certainly far from the worst library when it comes to installation. I had problems with either three or four different libraries, and I'm not going to use all of them as examples. It's also not limited to just these libraries; many, many libraries have this problem.
[^2]: There are good reasons for allowing custom names, though. That said, there's some overlap with the `CONFIGURATIONS` flag. For example, a multi-module library (think Boost) could require a `CONFIGURATIONS` to install a specific module, while leaving `COMPONENT` to specify the type. It's possibly difficult to integrate any solution into existing options, however, and it might prove easier to build something new from scratch. There's many solutions too for that matter, and I don't want to be too technically specific.
[^3]: I have no idea how, if at all, CMake deals with dependency conflicts. Pre-FetchContent, I would understand there not being any kind of system. Post-FetchContent, I'm pretty sure there's some dependency conflict checks for FetchContent specifically, but I'm not entirely sure. I know it flattens the entire dependency structure and resolves that, but I'm not sure what happens if you have two packages using FetchContent that declare different versions of the same package.
[^4]: It can be argued that installing (or even using) aliases is a dumb idea in the first place, but that's a discussion for another  time. I personally don't really see the point in declaring libraries using aliases, largely because the namespace-style aliases don't actually do anything to restrict the scope of anything. I can still access the `cpr` target directly, but their docs recommend `cpr::cpr`, so I'm using that whereever possible.

[libcpr]: https://github.com/libcpr/cpr
