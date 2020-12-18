
---
date: "2020-12-17T22:42:47Z"
toc: true
title: Why I use Vim
tags: ["vim", "editors"]
---

There's arguably more than enough of these posts on the internet as it is, but after reading [this](https://rudism.com/vim-creep/) story, I felt inspired. Unlike that though, this is based on my actual experiences rather than that of a fictional character. I've also had this post in mind for quite some time, so I figured it might just be about time to get it out there.

**Disclaimer:** My sense of time is trash. All times listed should be assumed to be guesstimates. If a certain bit of time doesn't make sense, it's most likely my fault.

## Background

### The beginning

I started coding about 6 years ago, and the first language I learned was Java. Like the vast majority of Java devs at the time, I started using Eclipse. At the time, JetBrains wasn't big enough to have crept into every bit of Java dev.

The start was alright, I messed around with it, and liked it quite a bit. I used it for several languages that I largely learned because I had nothing better to do with my time, and it just worked. Until I tried Android.

### The Android phase

I spent about 4 years actively doing Android stuff, for whatever reason. I made a lot of useless apps, most of which ended up in a dusty corner of my harddrive never to be seen again, and definitely for a good reason.

I tried getting started with Eclipse, and after a few tries and a lot of trouble, I got it working. Then Android Studio rolled out.

I was forced to switch over because Google were going to phase out Eclipse. Not gonna lie, the first time I used Android Studio, which is based on IntelliJ, I fell in love. It was fast, it was modern, and it made Eclipse look like some program from the 90s both visually and technically. Shortly after, I switched over to JetBrains products for Java, and later got it for Python as well.

### The webdev phase

I started venturing into webdev about 3-4 years ago, in parallel with a lot of other stuff (I'm weird, okay?). Found brackets, stuck with that, was mildly unsatisfied, switched to Atom.

I stuck with Atom, and used that for web stuff for a good 6 months to a year. Then I heard about Sublime and wanted to try that. It stuck for some smaller things. 3-4 years ago, I had Atom, Brackets, IntelliJ, PyCharm, Android Studio, Sublime Text, and probably more installed. (I'm leaving out Notepad++ because I didn't use it for proper coding, but I used it for editing some things from time to time, primarily JSON).

### The Kotlin phase

I got into Kotlin in late 2017, but started using it more and more up until the end of 2018. At the time, I was still stuck on my old, heavily used and abused computer. As Windows tends to do on old devices, it was getting slower. This eventually forced me over on Linux, but that's also another story.

This computer is a computer I've since nicknamed "The one-off generator", because it generated so many problems I've never seen before, haven't seen since, and that people don't experience in general. Some time around 2018/2019, I got so mad at IntelliJ because it refused to work. To put it like this, I could compile a project and it fails, but if I did it from the command line, it worked fine. I believe this was connected to my last project, which involved annotation processing. I'm not entirely sure though, this might once again be a case of me messing up time.

PyCharm broke, I kept it installed (I don't know why), and installed VS Code. At this point, I was largely messing around with Kotlin outside Android, with some on Android, but Android had been getting on my nerves for a few months and I decided to stop. No offense to the people who like Android dev, but in my opinion, it's absolutely horrible and the reasons why are so many and require enough explanation to probably make up a post on their own.

My frustration with IntelliJ peaked and I got to a point where I felt I had to get far away from that trash (... to be clear, this is what I felt at the time). I slowly stepped away from Kotlin as well. As much as I love Kotlin, and eyeballed Kotlin Native and _hoped_ I could switch to that, I didn't have much choices when it comes to non-JetBrains editors.

I did discover VS Code in the process, and it became a core element in the next phase:

### The C++ phase

Admittedly, the C++ phase is a two-parter. I initially started in 2018 and worked for a few months, then took a break for various personal reasons, and came back to it at the end of 2019. I've since been working continuously in C++.

This is where stuff started to get interesting. At the time, I was on Windows, so I figured I'd try Visual Studio. CLion was off the table the entire time because it was (and is) expensive, and I was somewhat reluctant to go back down. Now, I for one can't stand using OS-specific build systems, and at the time, it seemed like I couldn't use CMake, so I backed out. I bounced through Code::blocks, and got out when I couldn't figure out the build system.

I landed in VS Code and used it for a relatively long while. Messed a round with config, and then I started using my Pi actively. Now, if you don't know what you're doing (like me at the time), C++ on Windows is a lot harder than on Linux. Consequentially, as a combination of Windows weirdness and C++ needs, I had 7 (!!) terminals installed at the peak, which including the built-ins were: CMD, Powershell, Git Bash, MinGW, Cygwin, Windows Terminal, PuTTY. Building stuff usually went through MinGW and GCC, although I somehow managed to use Clang with CMake for a while. It came to a point where CMake thought it was being smarter than me and decided to block Clang on Windows unless it was clang-cl, but that's a different story, again ^^". 

At this point, VS Code was getting on my nerves, and so did everything built on that utter pile of garbage known as Electron. It was slowing down, possibly alongside my computer but it's hard to tell apart, I needed something that also worked on my Pi, so I decided to try Vim. Did some basic stuff, didn't figure out much, got out, jumped to Emacs, got some stuff going, and chilled there for a few months. Wrote some stuff, primarily web though IIRC.

Towards the end, I was using Eclipse, and I actually checked this because it's one of the few events that are easy to find.

## Who cares?

Glad you asked!

It came to a point where I was doing stuff on my Pi, I was doing C++, and I was tired of quite a few things. Emacs was a pain to deal with because the keybinds were pretty bad, not  gonna lie, although the part that got me hooked about it initially was the existence of a built-in package manager. Naive little me assumed no built-in package manager &lt;=&gt; there is no package manager, because that's usually how it works in other editors. I'm going to be getting back to this later, because it's actually kinda important to the secondary point of this post.

I was doing Advent of Code 2018 in Kotlin and C++, in a combination of at least Emacs and Eclipse, and I got into a discussion with someone on C++ IDEs/editors. Quick side-track, but when I read the Vim story, it resonated with me because of this discussion. The person I was talking with said, and I quote:

> why not just vim? 

I slightly dismissed it with the excuse that navigation in Vim and Emacs is hard, but I still didn't entirely abandon it. The primary reason was a bit of interest: If someone that experienced like it, it can't possibly be as bad as it looks, right?

In January, I asked for a bit of help. I got myself set up with a .vimrc heavily based off their vimrc, and it pretty much escalated from there. I got started with the mandatory config and a plugin manager, as well as some plugins and a minor workflow. The clusterfuck C++ toolchain hacks on Windows are unrelated here, but I had an editor, and I was using it.

## Yes, but why?

Do you remember all the editors I've mentioned so far? I've even left out some because I don't remember all. One of the things that bothered me before I started using Vim was exactly the number of different editors. One editor for Python, one for webdev, one for Java/Kotlin, one for C++, one for this, and one for that, and one for this specific niche use, and some other for editing certain files. The number of editors on my system was ridiculous. Nowadays, except a standard preinstalled text editor and LibreOffice, I have Vim.

"why not just vim?" came at the perfect time for me. I was fed up with slow editors, lack of customizability, and that the editors some times didn't do what they were advertised to do. In combintion with a basic setup, I moved over to vim, and I fell in love with it because it's everything the other editors aren't. It's customizable. It's fast. It's responsive. It's flexible. _It's everywhere_. I use the same config on my Pi as I do on my desktop, and it works like a charm on both, in spite of the Pi being used over local SSH. I don't have to settle for a worse editor because the system specs aren't up for it. [My `.vimrc` is 765 lines](https://github.com/LunarWatcher/dotfiles/blob/master/.vimrc), and that's bigger than what most people do with it, at least from what I've seen, and it's actually portable. I'm also a huge fan of dotfiles in general, because it means that file alone, along with manually installing vim-plug, is enough to recover my entire Vim setup. Admittedly, some plugins have dependencies, but they always tell me what's missing so I can fix it. That alone helps justify the lack of external dependency bundling, as messing with dependencies is something I only need to do once. It's also something I've automated in a script, because I can.

"Because I can" is actually something that comes back to a lot of my Vim use. I have fzf and vim-clap, even if I don't use vim-clap too much. Why? Because I can, and it doesn't have a negative effect on my experience using Vim. I can also make changes to config, some times based on a "sure, why not?", that actually turns out to have a massive positive effect on my workflow. The freedom that Vim gives in having a turing-complete config language is essentially infinite, and that's one of the many things I like about it.

I've gotten more and more IDE functionality since, especially when I just a few days ago switched from YouCompleteMe to coc.nvim. With coc.nvim, I use clangd and ccls, and I have everything. I have error highlighting, I have auto-import, I have fix suggestions, I have warnings, I have signature help that beats YouCompleteMe by a huge margin. I've spent an embarrasing amount of time just tinkering with my vim config, not because I had to, but because I wanted to. Vim in general lets me develop my editor around my workflow, rather than having to build my workflow around the editor. It's more specifically a bidirectional: there are parts of Vim I have to conform to, such as modal editing, but even that can be customized.

Modal editing in general works for me. I can input commands in normal or visual mode that wouldn't make sense in just a normal insert mode. For an instance, thanks to an autosurround plugin, if I highlight some text and type `S)`, the text is surrounded in (). (i.e. `this highlighted` -> `(this highlighted)`). This is largely useful when I have to redo parenthesis for whatever reason, but that wouldn't make sense in insert mode only. Is ) a request to replace the text or is it a request to surround? Editors assuming they know which honestly frustrate me, because there usually isn't a way to tell it to not surround stuff, but replace instead. With modal editing and commands, I can.

Just for good measure, modal editing is the concept of having separate modes for editing. Pretty much all mainstream editors are non-modal, which means there's only one mode, and that's insert mode. There's of course keyboard shortcuts, and things that may resemble normal mode commands, but it's all done without leaving insert mode. Until I started using Vim actively, I actually preferred this.

Remember the bit I said about package managers earlier? This largely matters because Vim requires config to be usable. I always assumed people just used plain Vim, which is why the person who helped me get started actually did manage to help me get started. They opened my eyes to the existence of package managers, which I hadn't thought about because it wasn't built-in. Most mainstream editors today offer extremely little scripting, and very few of them offer the ability to write package managers or other functionality that overhauls the base software. That is a major strength Vim has, and admittedly Emacs too, even if I'm not a fan of (l((i)((((s))(p))))). As a result, Vim appears to be a lot scarier and hard to use than it actually is. Yes, modal editing is something that takes time to learn, but achieving that, it's still more than achievable to customize the editor **with little effort.** I need to highlight this bit and reiterate that my `.vimrc` is largely over-engineered, and doesn't represent the average complexity, or even the smallest config necessary to get you up and running. Different requirements also result in different config requirements, and as a generalist, my config requirements tend to be a lot more complex than absolutely necessary.

## Summary

To sum it up, I switched to Vim after the right word at the right time saved me from an editor mess. Since then, I've gotten more into it and started tinkering a lot with it. As a side-effect, I've also gotten extremely used to the command line. This is, however, not a requirement, but it happened because I wanted to make my workflow heavily terminal-centric. The primary reasons I use Vim are for its flexibility, performance, modal editing, and ability to do whatever the fuck I feel like with my editor. In fact, this entire blog and even this article has been written in Vim, some times making use of a few writing plugins I have for making writing over a longer period of time a more enjoyable experience. Vim is one of the weirdly few editors where if I don't like something, I change it. More importantly, I _can_ change it, and usually easily. Most of the editors I have used have often ended up sacrificing customizability for development around a specific workflow - a workflow that might not be entirely for me.
And yes, I've made mistakes using other editors that might seem obvious to people using them actively, but what happened cannot be undone. With an increase in the functionality I feel I need to have a good code editor, Vim is feeling more and more natural to use. It's also living proof of what happens when you have a community of developers develop an editor, as well as a community of developers continuously writing plugins based on individual needs. Forks of Vim have also come into existence when the community found that core bits of the editor were lacking. I still prefer plain Vim, but most notably Neovim has helped to drag Vim's development in a modern direction. For an editor from the 90s, it's still very much alive.

And finally, so we're on the same page, I'm not writing this post to try to convert you, the reader, to Vim. Try Vim if you want, but if you prefer some other editor, use it. Vim isn't for everyone just like IntelliJ and the other far too many editors I had aren't for me. I primarily wrote this post to share why I like it and what got me into it, not to convert people. Getting into an editor war is not something I'm interested in. As long as your editor works for you, and you enjoy using it, it doesn't matter what you use.
