---
title: "Vim Cheat Sheet"
date: 2021-03-06T22:35:35+01:00
tags: ["vim", "vimscript", "cheat-sheet"]
toc: true
---

There's already a number of cheat sheets out there for Vim and Vimscript, but I rarely find one that works. Or at the very least an easily searchable list with specific keywords describing what a function does. So I made one. (Or at least made a reference that I'll add stuff to when I find neat tricks).

This is largely meant to cover "lesser known" functions, but will cover others that may not be lesser known, purely because I felt like including it, or because it took embarassingly long for me to become aware of its existence.

## Files

| Function | Description | Tags |
| -------- | ----------- | ---- |
| `writefile()` | Writes to a file, and creates said file if it doesn't exist. Largely useful by being a pure script feature, meaning you don't have to open a buffer to make a new file. | create, write, erase |

## Folders

| Function | Description | Tags |
| -------- | ----------- | ---- |
| `mkdir`  | Creates a directory, but it supports several arguments. If the second argument is `"p"`, it both creates parent directories as needed, and newer versions of Vim don't throw if the directory exists | create, trees | 

## Vim features

| Keyword | Description | Tags |
| --- | --- | --- |
| `silent!` | Bang version of `silent`, and it completely discards errors. Put it in front of anything causing an error, and it'll be handled quietly. | errors, error handling |
| `scriptversion` | (New Vim only): makes it possible to set the language standard. Not to be confused with `vim9script`, though it's in a similar alley for classic strings | version |

## Strings
| Function | Description | Tags |
| -------- | ----------- | ---- |
| `split()` | Potentially familiar, but the second argument supports regex | split |
| `..` | Alternative to `.` for string concatenation. Does the exact same thing but with no a mbiguity with the standard access operator, which also happens to be `.`. | String concatenation operator |

## Regex

| Flag | Description | Tags |
| ---- | ----------- | ---- |
| `\v` | Very magic - means characters are interpreted differently. The major implication here is that you can write () or [] groups without needing to escape characters. Same with or - generally, it removes the need for a lot of escaping. | magic, escaping |
| `\V` | Essentially the opposite of `\v`, but a bit more extreme. Largely useful if you've got a bit of a regex that you'd have to escape. Both `\v` and `\V` can be used in the same string, which makes it exceptionally useful in scripting contexts. `\v` still has a lot of uses, notably in `substitute` if you need regex, and you've forgotten about `:sm`. Function use is much more relevant, however. | no magic, escaping |

Note: I'm not entirely sure why it's called magic. It just makes interpretation feel slightly more like traditional regex (assuming magic is on).

