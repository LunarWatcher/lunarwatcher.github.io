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

## 26.12.2021

### Dawn

Handled a PR for a go template that introduced some doubt around how I'm handling output. Verbosity was intended to keep track of any changes made, but that might also be undesired.

Also not a super fan of git being hard-coded into templates. Might be worth introducing an option to auto-commit after generation, and then removing it from the template. Error handling doesn't appear to be a problem though, so it's fine for now, but would be about the least opinionated way of fixing it; i.e. supporting both in a configurable way, to make sure everyone's happy.

[ap-55]: https://github.com/LunarWatcher/auto-pairs/issues/55
