---
title: "Devlogs: part 1"
date: 2021-12-24T23:24:25+01:00
tags: ["programming-meta", "devlogs"]
toc: true
---

## 25.12.2021

### auto-pairs
Fixed several annoyances, and expanded tests, as a part of responding to [#55][ap-55].

Still not sure what m and ms really do. I'd assume the s indicates "start", considering it checks the line prior to the cursor, but I don't really get it. Also not sure how it correlates to open == close, and the if statement does introduce a new question of how the close check relates to balancing.

I wonder if the two loops can be merged? Need to revisit for 4.0.0

[ap-55]: https://github.com/LunarWatcher/auto-pairs/issues/55
