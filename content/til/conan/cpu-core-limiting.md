---
title: "Limiting Conan's CPU usage: modern edition"
tags: ["conan"]
date: 2022-09-02T21:51:26+02:00
---

Turns out that my Raspberry Pi doesn't like building on all its cores. The build is so memory heavy after installing the 64 bit version of the OS that it runs out of memory and completely chokes. The obvious way to fix problems like these, particularly when the problem is from concurrent builds, is reducing the amount of cores used. There's still other reasons for limiting Conan's CPU use. I'd list some, but you're here, so I'm sure you've brought your own examples. I'll spare you the list.

`CONAN_CPU_COUNT` is the well-documented way of changing the CPU cores Conan uses.
However, this doesn't seem to work anymore, and the docs do not say it doesn't work anymore. Thanks for fantastic documentation, Conan /s

I believe this is related to a move to [adding config to profiles](https://docs.conan.io/en/latest/reference/profiles.html), which itself also is the answer; the `tools.build:jobs=<count>` option has to be set (`tools.microsoft.msbuild:max_cpu_count` if you're using msbuild). This can be supplied via the `-c` option for `conan install`.

This option, at the time of writing (but this may change; the system is marked experimental) `conan config set conf.tools.build:jobs=1234`, where `1234` is the actual count.

This is particularly useful in environments with limited memory. I had to set this option to get several of my C++-based projects to build at all after upgrading Raspbian to the 64 bit version. It presumably uses more memory because sizes, but it eats through the RAM at max cores.

This is also a per-profile solution; set it and forget it, and it applies to (in theory<sup>[1]</sup>) all Conan builds (including `conan install` and [conan-cmake](https://github.com/conan-io/cmake-conan)).

<sup>[1]: I've only tested this with `conan install` and conan-cmake. As long as the particular system you use doesn't explicitly override these config options, it should respect the global options.</sup>
