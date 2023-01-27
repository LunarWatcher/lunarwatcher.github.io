---
title: Multiple return values from the \_\_index meta method
tags: ["lua"]
date: 29-12-2022T02:32:23+01:00
---

You don't.

A test with upm found that an `__index` method declaring two return arguments is disregarded. They're somehow flattened into the same variable instead, but the normal `x, y = func()` syntax doesn't work, and `x` is still the same return type. The comparison of a normal function worked as expected with two return values, so this behavior is unique to `__index` (and possibly other meta methods).

Fuck knows what Lua actually does in this context, but it does _not_ respond well to `__index` returning multiple arguments.

Use a table if you absolutely *have* to return multiple values from `__index`, or use normal functions instead. As already mentioned, normal functions are able to return multiple arguments. It's just `__index` that misbehaves.
