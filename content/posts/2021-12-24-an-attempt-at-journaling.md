---
title: "An attempt at journaling"
date: 2021-12-24T23:39:11+01:00
tags: ["meta", "programming-meta", "life-meta"]
series: ["devlogs"]
---

TL;DR: I'm going to be keeping a public devlog for my open-source repositories, within reason.

## Introduction

<sub>Note that this intro excludes links to projects because I can't be arsed to get them. There's a lot of projects, and they're all linked on the front page of this blog for your clicking, then pointing and laughing-convenience :p</sub>

I have a few projects that've been struggling.

This is largely due to me being in way over my head, and losing some "sane infrastructure" in the process. I'm not really sure how to best explain the problem, but here it does anyway:

Learning new stuff is hard, and I'm learning a lot at once. I currently have several active projects (which I assume that most people who ever read this is going to have at least some measure of in advance, considering most of my traffic comes through GitHub anyway; if you're not aware, the link to my GitHub account is on the front page), with a tech stack so varied that it's bordering ridiculous.

There's three primary languages, in order of activity: C++, Vimscript, and Python, the latter of which primarily has one project attached to it, but uses so much regex that it's putting even my pattern matching abilities to the test. (I'm not what I'd classify as a professional at regex specifically, but pattern detection is my game).

With Vimscript, I primarily have one active project: auto-pairs. I have several plugins, including one that I even wrote a blog post about and then never really got deep into, because actually getting started turned out to be harder than I planned. Funny that :')

Then, there's C++, my new main language. I currently have several active projects, and one side-project, that I aim to sink more time into. However, there's also one I don't plan on finishing any time soon: Genesis, an attempt at a game.

I've been doing C++ for about 2-3 years I believe, so I do know the language, to the extent you can know C++. I constantly learn new and better ways to manage things, but I've also had to figure out new ways to do things. Code design in sufficiently large C++ projects is... hard, especially coming from a primarily JVM background, where imports didn't use to be a thing that forced you to redesign your code, and re-evaluate your life choices when you realize a library you had to use didn't support modules yet, so it caused obscure and silent reflection errors in certain cases, but not others, because tests are apparently special.

This isn't a rant on how Java has gotten substantially worse though.<sub>And please spare me of the Java-defending comments, that's not why we're here. This is purely a subjective experience, and no objective or subjective answers will change that</sub>

On top of that, it's been far too long since I last did gamedev, and when I did, I didn't do much OpenGL. I did use OpenGL once, in Java, but my interests shifted (if I had a Bitcoin every time my interests shifted, I'd control the entire market cap) and I didn't really touch gamedev again. OpenGL is a can of worms, and I ended up making the decision of doing a 3D world, with a game that's heavily inspired by Dwarf Fortress and the likes.

## My motivation

My point, you ask? I lose track of what I actually do. This is a learning "problem", to which I have a very concrete strategy. I need to consciously manage the things I do.

On a tangent, I started learning Korean 97 days ago, using Duolingo. Around a month ago, I realized just using the app wasn't going to be enough. There's so many concepts that are foreign -- but also really cool -- that I need a better system to deal with.

Speaking for myself, I like structure. That's part of why Duolingo is also working against me on grammar, but the website is substantially better than the app, thanks to the handy dandy tips outlining some of the reasoning, grammar, etc. Yet, unless I structure these explicitly, and mostly in writing, I struggle.

Programming is somewhat different. I'm not gonna take notes of every data type I come across -- I'm not on that low a level. But I do need to keep track of generic problems, _especially_ in places where I'm out of my depth. 

[Public accountability as a strategy](https://www.reddit.com/r/gamedev/comments/azx9eu/advice_on_public_devlogs/) is viable. This entire idea was actually inspired by [100 days of code](https://www.100daysofcode.com/), but instead of using it purely for accountability, I use it for structure and as a public record for my public projects, and instead of 100 days and daily minimum requirements, I'm going to go as far as I can, and expect to not always do it daily. I do still have other things that take priority, and needing the long-term side of things makes even a modified 100 days of code unviable for my particular use.

Also, there's something nice about keeping a public record of various challenges. Aside potentially helping others, it can help me find stuff to write about. I often find myself wanting to write something, but without any ideas for what to actually write. Keeping an informal record is, on its own, a source of potential, proper articles.

## The plan: public devlogs

Overall, I plan to write down a lot more than I currently do. Some of this isn't going to be public, for various reasons that include simply not wanting to keep a public record of all the obscure things I decide to learn or mess around with, some things being too sensitive to keep in public, etc. The list goes on and on, but the planned format for all of them is the same; markdown files, sorted by dates and probably category.

What I will keep public, however, is work on my open-source projects. On the programming front, effectively all my code (that isn't done for uni) is open-source and available here on GitHub, and consequently will be listed in the [public devlog.](/notes/index.html#logs) (this is where you want to go if you're here for the devlogs :p)

The general format is partly inspired by 100 days of code:
```
# [Header with date, and without brackets]

<!-- if one project -->
Project: [name]
<!-- else -->
## Project 1
...
## Project 2
...
... etc, each project containing:
<!-- endif -->
* A description of the problems solved, if applicable
* Notes on problems or things that were discovered and not handled, and that need to be fixed or researched later
* Notes on future problems or things to do
```

The length of each point, as well as what's included, may change with each entry. While one entry can have single word answers, another can have several paragraphs. This is to make sure that the "ruleset" for the entries stays adaptive, and not restrictive, to best suit my needs.

To end this post off, if you're looking to get into this style of journaling/dev logging/etc., I highly encourage you to figure out what your needs are before you get started. This is an extremely subjective field, and depends on your learning style, or other various needs or desires. Figuring out what format works is the hardest part, especially if you haven't tried anything similar in the past.

---

Henlo, future Olivia here. Formats are hard.

The initial plan outlined here (keeping stuff as short as possible) is still the primary plan, but I've already run into a game design issue where I'd like to write more in public.

Annoyingly, this means I need to get rid of the original format, and start posting it under {{<ser>}}devlogs{{</ser>}}. The current format adjusts to weeks, but within reason. Sufficiently short devlogs may span several weeks, but a single page still has to contain a longer period of time, for it to be possible to organize at all.
