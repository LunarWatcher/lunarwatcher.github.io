---
title: "Shady development ordering"
date: 2021-08-19T22:50:13+02:00
tags: ["genesis", "code design"]
summary: Tiny devlog on how I some times end up doing stuff in a really bad order when I have no idea what I'm doing.
---

I'm a huge fan of [scc][scc]. Lines of code [isn't always a useful metric](https://en.wikipedia.org/wiki/Source_lines_of_code#Disadvantages), but as a single developer [on a single project](https://github.com/LunarWatcher/Genesis), there's a few things I can find out.

Here's the count at the time of writing:

```bash
───────────────────────────────────────────────────────────────────────────────
Language                 Files     Lines   Blanks  Comments     Code Complexity
───────────────────────────────────────────────────────────────────────────────
C++ Header                  27      1065      260       130      675          7
C++                         25      1386      264       125      997        113
GLSL                         6        85       26         3       56          1
Markdown                     4        33       11         0       22          0
CMake                        2       136       18        40       78          4
Plain Text                   1         2        0         0        2          0
───────────────────────────────────────────────────────────────────────────────
Total                       65      2707      579       298     1830        125
───────────────────────────────────────────────────────────────────────────────
```

I also know what the code does. I have some theoretical scene management, basic physics engine design, and rendering. I also know this isn't something that takes 1830 lines.

Just from browsing the code, I can tell it's heavily affected by code sprawl. What I need to do is a substantial amount of cleanup. While migrating to Scenes, I indirectly changed the need for `PhysicsWorld`. It's now a somewhat redundant class that more or less just wraps some Renderer functionality.

Yet, separating out the physics may be necessary as the engine grows. These are all things I should be figuring out, especially because I'm really out of my depth here. Complete game engine design is far above what I've done before, so I don't have a concrete plan, or full control over everything I do. As a consequence, code quality some times suffers.

Yet, I sit down to start doing something, and decide to add settings instead of figuring that out. Nothing quite like shady development ordering in a sprawling project where I have no idea what I'm doing :')

It'll still work itself out after another refactor or two. There's so many things that pop up that I didn't think about that affect the architecture, and that I now need to account for. I guess inevitably needing to refactor is unavoidable.

[scc]: https://github.com/boyter/scc
