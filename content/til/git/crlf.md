---
title: "Windows is pain: getting rid of CRLF"
tags: ["git", "windows"]
date: 2022-12-23T17:24:56+01:00
---

I can never seem to get autocrlf to work properly on Windows. It isn't a problem on Linux, but it's always a problem on Windows.

So note to future me, here's how you overkill ensure new systems work properly:

```
git config --global core.autocrlf=input
```

`false` is evil and `true` does excessive normalisation.
