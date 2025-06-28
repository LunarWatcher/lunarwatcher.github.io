---
title: Installing CrowCpp with submodules and Conan without using the Crow Conan package
tags: ["c++", "crowcpp"]
date: 2023-01-27T23:32:11+01:00
nocomments: true
---

> [!warning]
>
> This page is based on Conan 1.x, which is now deprecated and basically fully dead. Some of the things still apply here, but this page should be considered deprecated

CrowCpp's conan package is, at the time of writing anyway, heavily out of date, which isn't great. There hasn't been a tagged version in ages either, so this isn't Conan's fault, but the problem is still a problem regardless of whose fault it is.

On the bright side, it isn't too bad to install. It's just unnecessarily convoluted due to CrowCpp not dealing with its own dependencies.

First of all, add CrowCpp as a submodule:
```
git submodule add https://github.com/CrowCpp/Crow
```
Then add these dependencies to `conan_cmake_configure`:
```cmake
# Crow dependencies
asio/1.24.0
openssl/3.0.7 
zlib/1.2.13
```
asio and OpenSSL are the newest versions at the time of writing, while zlib uses the same version the Conan package for CrowCpp uses. These may need to be updated. As usual, not all of these are explicitly required if another package includes them. You can just piggyback off that version, and it'll be fine.

Then just the submdoule prior to `add_submodule(src)`, or in general before the part of your CMake where you configure your executables:

```cmake
# This enables the optional SSL and compression features.
set(CROW_FEATURES ssl compression)
add_submodule(Crow)
```

Linking is trivial, and is just a bog standard
```cmake
target_link_libraries(target Crow::Crow)
```

And that's it. Their CMakeLists.txt conveniently configures include directories and asio linking.
