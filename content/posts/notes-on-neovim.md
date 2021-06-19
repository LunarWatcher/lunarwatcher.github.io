---
title: "My notes on Neovim"
date: 2021-03-07T17:30:46+01:00
tags: ["editor", "vim", "neovim"]
---

So I decided to give Neovim another try (and specifically nvim-qt). Here's what happened. <sub>Note that I'm not looking for a "solution to my problem" or any crap like that. This is purely based on my observations and experience with Neovim.</sub>

Also, obligatory disclaimer that this ended up being a stream of consciousness, and may therefore lack a bit of structure.

---

I decided to give Neovim a try after reading up on Vim 9, specifically surrounding compatibility with neovim. I went to the [Vim9 README][README] for the performance stats as well (purely for the pointless trivia). This is largely because I'm diving deeper into the realm of plugin development (I have no idea why). This was largely while looking into which language to use for a plugin, for stdlib availability. There's bits I don't feel like reimplementing for the plugin I was looking into. I also got side-tracked into performance stats, because I do that some times.

The relevant bit of the Vim9 README is the second point: deprioritizing interfaces.

I initially misunderstood the point behind it until I started writing this post, actually. Anyway, that spiraled down into [reddit][reddit-1], [more reddit][reddit-3], and [vim9 compatibility with neovim][reddit-2]. A few of these arguments resonated with me (although I'll get back to these later), and I decided to once again try neovim.

---

My general workflow for dotfiles [relies on makefiles][zoe-makefile]: I make a new target, throw in whatever I need, run it, and call it a day. At the time of writing, I started 6 hours ago, and abandoned it about 2.5 hours ago. I got tons of obscure build errors, and tried workarounds that didn't work. It took me longer than necessary to realize that I cannot build a few of the third party depndencies by invoking make from make, if that *make*s sense.

I broke up the entire command into building third party deps, and it worked from the terminal. Had to split off neovim compilation into a .sh file for it to work. (**compat 1** - these will make sense later).

Why it failed to compile beats me, but I rework it into a shell file and it somehow magically works. You might ask why I went to compile it in the first place, but that's because I couldn't find any PPAs doing up to date nightly builds, and because I like to keep my editor up to date. That's why I also compile vim from scratch, something I will get back to.

So I run nvim after linking up a standard .init linking back to my .vimrc, and this is where the real "fun" begins.

At least with my colorscheme, any errors during startup are hidden (**annoyance 1**). That means I have to manually run `:messages` after booting to see what went wrong. My font is considered invalid. To be more specific, the font that's valid in vim, gvim, and nvim is invalid in nvim-qt (**compat 2**). Okay, so I look through the docs, find the right format, plug it in, and we're good.

Then there's the GUI tabline... It has to be disabled with `:GuiTabline 0`, a command that's only a part of nvim-qt. For those of you who aren't familiar with nvim, nvim presents one of its major advantages being the separation of UI and backend, with the end goal of being able to embed nvim literally anywhere instead of adding some cheap vim emulation crap like other editors and websites (overleaf, anyone?) have. Sounds promising, right? Especially for someone like me, who uses a GUI to get around terminal input processing issues? **Wrong.**

The secondary implication of this is that `init.vim` (or `.vimrc` in my case, which I'll refer the init file as from this point) is _only sourced for nvim_. `nvim` itself is never a GUI in the gvim/nvim-qt sense of the word. By extension, this also means `has("gui_running")` is always false, and would never work even if it was a thing. Again, when the `.vimrc` is sourced, it's _always_ false, because the GUI (that's nvim-qt in my case) attaches `nvim` itself after the fact. This is by no means an unknown issue ([#94](https://github.com/equalsraf/neovim-qt/issues/94), [#102](https://github.com/equalsraf/neovim-qt/issues/102), [#182](https://github.com/equalsraf/neovim-qt/issues/182), [#213](https://github.com/equalsraf/neovim-qt/issues/213), as well as issues addressing general GUI options).

Simply (and bluntly put), neovim is incapable of detecting a GUI during startup (**compat 3**). For me, this is a necessity - I use several maps that aren't possible in a terminal. These issues have existed for several years and aren't addressed. Autocmds and terminal aliases injecting variables are the only ways it's allowed to work.  `$TERM` can be empty if and only if neovim is started from the start menu - not from a terminal. On one of the issues that I may have lost track of, someone suggested checking `&term`, as it's always equal to `nvim` in nvim-qt. That's wrong. It's always nvim in the `.vimrc` as well, meaning it's useless for detecting UI or not.

That also leaves me, someone who randomly decided to switch to nvim for no real reason aside being midly pissed at vim, unable to get nvim working properly without a shitton of if-else statements, weak checks looking for a GUI, and the only option presented is to use a `ginit.vim` (init file for GUIs). In order to do that, I'd have to fragment my [clusterfuck of a `.vimrc`][zoe-vimrc] heavily, which would take a substantial amount of time when I also want to maintain compatibility with gvim if I decide to jump back (which I already have).

I fight through a few of these issues, and somehow manage to get all the meta issues out of the way. Coc.nvim worked in the .vim files, stuff loads (although a bit glitchy because of the GuiTabline removal. **annoyance 2**), and I give it a try on a C++ project I have laying around that's largely for vim testing at this point.

And coc.nvim doesn't work.

While writing this bit, I randomly figured out why. Neovim's config location relocated `coc-settings.json`. None of my config was carried over, disabling the two C++ language servers I have hooked up (**annoyance 3**, **compat 4**). Coc.nvim itself gave no notice of this, and I didn't think to imagine that the config was empty all of the sudden. The extensions showed up as installed. One might argue that this is coc.nvim's fault rather than neovim (hell, it's [even an issue](https://github.com/neoclide/coc.nvim/issues/2841)), but its config location (and difference between operating systems) has always been a massive pain in the ass. One of the things Vim has done right is config locations - I know `~/.vimrc` is guaranteed to work on both the operating systems I might find myself on (Linux and Windows), and I don't need to go hunting for the actual config location.

After I got everything up and running, I tried installing and running TreeSitter with C++, and it was honestly disappointing. It highlighted a single variable while I was typing, but it didn't get close to the screenshots in the nvim treesitter repo.

---

There's dozens of migration problems I can list, such as the lack of GUI variables, general pain in the ass configuration, and the annoyance that needing to separate certain bits of config presents for someone like me, with a shitton of intricate editor config. When everything was running, neovim just felt like vim with slightly longer characters for separators, a bit more responsive UI when updating vim plugins, and a somewhat less buggy completion popup (but a substantially uglier one). I have highlighted a few bits of this post with compat and annoyance. These are core issues in migration and/or documentation as a direct part of nvim, or as a side-effect of nvim.

Why did I bother trying in the first place, though? I mentioned earlier that a few of the arguments did resonate with me, and they're completely correct. Vim has added a lot of hackish implementations with an unnecessary amount of extra implementation work. One of the second arguments here was that it wasn't done in a way that was compatible with nvim, but to be honest, nvim is so incompatible with vim that the argument of introducing incompatibility falls equally much in their court as it does in that of Vim. At the same time, the general motivation behind the arguments [were countered][reddit-4].

Vim itself doesn't need to be compatible with neovim's implementations either. Neovim already goes out of its way to do several incompatible changes without trying to make changes in a way that can be merged back into vim, so they're not in any way in a "better" position. That alone to a certain degree proves a point I'm trying to make, and that I noticed in this entire mess: neovim and vim aren't compatible. The projects have fundamentally different reasons for dragging development in whatever direction it ends up in, meaning that over time, they will inevitably be truly incompatible. As proven in this post, neovim is by no means a drop-in replacement for vim, as they claim on their website. They might've been at one point, but that's definitely not the case anymore. What the "final straw" will be to properly prove that they're incompatible, however, is a different story. Might be Vim9, might be the loss of language interfaces, might be a disagreement over lua or a GUI feature, or some bridge they haven't built, and much less crossed, yet. At this time, guessing what could be the cause for a complete split would be just that - guessing.

There's already a noticable divide in terms of compatibility. Neovim has at least one option (`guifont`) that's incompatible with itself. "Wait, what?", you're probably asking. "How can it be incompatible with itself?" -- the honest answer is, I have no clue. Might be a qt/gtk/X11/other UNIX weirdness thing, but with no options to detect whether or not nvim is booting with a specific UI, the only option is overriding in ginit. That again assumes guitfont doesn't instantly trigger an error, because if it does, overriding would still cause an error. Compat 3 mentions the inability to properly detect a GUI launch, and the consequences this has for me.

Compat 1 (and I wish I could add links to that, but Hugo's markdown engine doesn't support it at this time) is one of the weirdest bugs I have seen in general. As as side-effect, neovim goes straight in with a workflow-altering change. Even if I don't use the bundled dependencies, I can't build simply because it excludes dependencies from the explicit list that I don't know how to install. Vim's installation [isn't pretty][zoe-makefile-vim-install-frozen], and is arguably one of the most unnecessarily complex commands I've seen, but it at least works on my system regardless of the call context.

Annoyance 2 covers weird GUI behavior. While I have to admit a few of the GUI implementations look nice (gvim out of the box is horribly ugly), they're not nearly as practical as gvim. I get the same input processing capabilities, but I have no way to detect whether or not I have those input processing capabilities. That presents several challenges, and just presents a few additional compatibilitiy issues (compat 3): GUI load is decoupled from nvim load, presenting a sudden code fragmentation, at least in my case.

Neovim claims to be a drop-in replacement for Vim, being fully compatible and all that, but somewhat interestingly, Vim is able to maintain compatibility with vi better than neovim is at maintaining compatibility with vim, completely disregarding delays between patches in the two projects (considering they're both active - we have to be reasonable too). It might've been at one point, but as pointed out in [the fourth reddit link][reddit-4], neovim and vim are diverging, and will continue down that path. In the meanwhile, I hope they drive the development of each other forward. Of course, the question of "who brought the idea" seems to be a driving force in Neovim's rising popularity. This is potentially an extremely unpopular opinion among neovim users, but if Neovim indeed was sparked by a bad PR and that async was planned on a "when a good PR shows up"-basis, that does mean neovim didn't bring all these ideas to the table, but potentially accelerated their implementation. That's still good from a user's perspective 

This is actually my third attempt at neovim (the second one actually entering neovim and messing with config; the second attempt overall was one with more failed compilation), and the first one was on Windows. The clipboard in nvim-qt was broken and was the reason I bailed on it. From some comments [on this post][geoff-1], it's abundantly clear that there's several things that've been rejected from Vim over a lack of Windows compatibility, at least where it's expected to be compatible. The [alleged start of neovim][reddit-4] was actually triggered by an incompatible PR.

Repetitions of how Vim's code is horrible are one of the arguments that've also made me stay away from neovim. Sure, it has horrible bits, but it's 30 years old this year, and has had to use systems that were big back then, but aren't now. Vim necessarily has to update itself, and just from the blog post I linked, it's noticable that change is happening. It mentions `eval.c` clocking in at 25k lines of code - it's currently down to 6000. And hey, it still works on all the operating systems I want it to work on, so I consider that a win.

And just to be abundantly clear here, I'm not saying that everything about nvim is wrong or horrible. There are good parts of neovim, but the primary selling points for me have been adopted into vim, making the differences between the two fairly small in some areas. There's the seemingly small things that just build up over time that makes it a bad option for me. A few system compatibility issues also make it substantially less attractive for me - I like using one editor that works on any computer I'm on. That's interestingly not a description that fits Neovim.

... nor does it entirely fit Vim. Vim is substantially faster on Linux than Windows for an instance, largely due to internal mechanics of process spawning.

I'm also not saying Vim does everything perfectly. It most definitely has its flaws, both in the processes surrounding Vim, as well as in the editor itself. Not to forget the code, but at the end of the day, I'll still stick with the editor that gives me the least amount of a headache - and that's Vim. I really do hope Vim influences Neovim and vice versa, though. Competition often helps bring out the best in editors, and Vim has historically not had that many direct competitors.

In the meanwhile, I'll go back to Vim and make it better for my use.

---

# TL;DR:

* Refuses to compile if the compile is initiated from a Makefile (even if the normal command line build is fine)
* GUIs being detached means the vimrc has to be split up to work (not as bad for new .vimrcs, a royal fucking pain in the ass for existing ones, and horrible from a compatibility perspective)
* One of nvim's goals (detaching GUI from vim) effectively breaks certain backwards compatibility aspects
* Certain nvim options are incompatible with nvim-qt (notably `set guifont`, which takes two different argument styles in nvim and nvim-qt). The secondary implication of this, without GUI detection, is additionally that there's no good way to set the font if GUIs and TUIs are incompatible with each other.
* Several plugins use incompatible config locations, on top of nvim already using incompatible config locations (which again are incompatible between operating systems)
* Neovim is no longer compatible with Vim to the extent one can call it a "drop-in replacement"
* Neovim, from a user perspective, struggles to maintain consistency between platforms in functionality (ref. clipboards) and basic things like config (specifically config locations, as indirectly mentioned in a previous point in this TL;DR:).


[README]: https://github.com/vim/vim/blob/master/README_VIM9.md

[reddit-1]: https://old.reddit.com/r/vim/comments/ey91bd/i_have_mixed_feelings_for_vim9_script_what_do_you/fggezgd/
[reddit-2]: https://old.reddit.com/r/neovim/comments/h8perv/will_neovim_merge_vim_9s_upcoming_vimscript/
[reddit-3]: https://old.reddit.com/r/vim/comments/ebz0cj/vim_9/
[reddit-4]: https://old.reddit.com/r/vim/comments/ey91bd/i_have_mixed_feelings_for_vim9_script_what_do_you/fghqnwi/

[zoe-makefile]: https://github.com/LunarWatcher/dotfiles/blob/master/Makefile
[zoe-makefile-vim-install-frozen]: https://github.com/LunarWatcher/dotfiles/blob/5758b92a89ed9b82a295bed45f37f991fdab0c91/Makefile#L97-L111
[zoe-vimrc]: https://github.com/LunarWatcher/dotfiles/blob/master/.vimrc

[geoff-1]: https://geoff.greer.fm/2015/01/15/why-neovim-is-better-than-vim/
