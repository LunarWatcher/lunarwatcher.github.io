---
title: "Runtime library conflicts with CMake, and why CMake doesn't respect your options"
tags: ["cmake"]
date: 2022-06-02T19:01:26+02:00
---

Starting with CMake 3.15, we get the fantastic [`CMAKE_MSVC_RUNTIME_LIBRARY`](https://cmake.org/cmake/help/latest/variable/CMAKE_MSVC_RUNTIME_LIBRARY.html). This makes explicit `/MD`/`/MDd` flags, or equivalent with `/MT`, unnecessary.

**However**, just having CMake 3.15 or up ain't enough. If you don't bump the minimum version to 3.15.

It seems that CMake doesn't just check your current version; the minimum version, for newer versions, acts as a form of compatibility mode. If you set the version to 3.10, CMake acts as if it's 3.10 even if it's 3.15, or 3.23, or 4.20. Admittedly, I'm not sure how far this goes. This is merely an observation between two relatively compatible versions, but where a newer version had a variable that didn't work when the minimum version didn't have it.

 Using a minimum version under 3.15, while trying to rely on `CMAKE_MSVC_RUNTIME_LIBRARY` to properly set your MSVC framework will result in your version defaulting to `/MD`, instead of `/MDd` for debug.

This caused some nasty conflicts for me, because while CMake used the wrong flag for my code, it used the correct flag for Conan. So my code was forcibly built in release mode, while conan libraries were built in debug mode, resulting in the good 'ol nasty conflicts we're used to with MSVC.

**TL;DR:** if you're using new, fancy CMake variables, don't forget to also bump your minimum CMake version, or they're probably not going to work.
