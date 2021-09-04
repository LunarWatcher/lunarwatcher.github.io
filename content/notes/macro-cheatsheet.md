---
title: "Macro Cheatsheet"
date: 2021-09-04T15:33:11+02:00
tags: ["c++", "macros"]
---

| Feature | Example | Comment |
| --- | --- | --- |
| `#arg` | `#define FUNC(x) #x` | Converts `arg` to a string |
| `##arg` | `#define FUNC(x) something##x` | Converts `arg` to plain text. Useful for sneaking a variable argument into a function name |

