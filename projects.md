---
{
    "title": "Projects"
}
---

This page lists some of my projects. For the complete list, see [my codeberg profile](https://codeberg.org/LunarWatcher). This list prioritises projects that are still active. Dead projects only get listed if they had some special value. 

{{ page.table_of_contents }}

## CLI utils

### umbra - a set of ✨ magic ✨ CLI tools

[umbra](https://codeberg.org/LunarWatcher/umbra) initially came about because I wanted to automate away some of the actions I kept repeating, and eventually expanded further into other CLI utilities, largely to replace tools that have turned into AI slop. This is in all likelihood the single non-library project I rely the most on to work more efficiently.



## Libraries


### stc - a C++ utility library

[stc](https://codeberg.org/LunarWatcher/stc) is a small utility/compat library that adds some things C++ does not have, but that isn't worth a whole dedicated library. It mostly consists of standalone headers, though some headers depend on each other. Very much inspired by [stb](https://github.com/nothings/stb) in terms of structure.

### moonbeam - a Linux-only Lua utility library

[moonbeam](https://codeberg.org/LunarWatcher/moonbeam) is a utility library for accessing system resources, JSON, and eventually other stuff. This library exists because I needed to do some advanced scripting to get a non-browser integration with my password manager without leaving my terminal, and didn't want to do all that in bash.

### magpie and raven - a C++-based server library and socket library

[magpie](https://codeberg.org/LunarWatcher/magpie) is a C++-based server library, inspired in name by [Crow](https://github.com/CrowCpp/Crow). It powers some of my projects that require HTTP servers.

Magpie was initially based on asio, a shit socket library that caused memory leaks. After lots of time fighting asio, I made [raven](https://codeberg.org/LunarWatcher/raven), an HTTP-specific socket library. Magpie uses raven for network connectivity, and in spite of being made to be a bare minimum library, has worked better and more reliably than asio. 

### alui.cpp - an (unfinished) GUI library for allegro

[alui](https://codeberg.org/LunarWatcher/alui.cpp) is a UI library for [allegro](https://github.com/liballeg), a fantastic graphics library. It hasn't received all the development it  deserves, and is far from finished (it's only barely usable as-is, and only has a small subset of features). I plan to do a large refactor at some point.


## Frameworks

### amethyst - a small zsh config distribution

[amethyst](https://codeberg.org/LunarWatcher/amethyst) is a small config distribution that came about because ohmyzsh decided AI slop machines were a good idea, which forced me to refactor my config. Rather than bundling it all in my zshrc, I separated it out into a new project. It includes some sane standards, and a bare minimum package installer[^1]

## Games

### nyaa

[nyaa](https://codeberg.org/LunarWatcher/nyaa) is an undefined, currently unplayable 2% of a plan for what will eventually be a game that'll involve dungeon crawling and some undefined open world elements. I wanted to make a game, but games are fucking hard, okay? :p

## Personal projects

### hazel

[Hazel](https://codeberg.org/LunarWatcher/hazel) is a small C++-based server that I use for various stuff I'd like to have, and that requires a server, but doesn't warrant its own standalone server. Currently only serves as a way to port RSS notifications from [Miniflux](https://github.com/miniflux/v2) to discord.

Hazel was initially based on Crow, but later moved to magpie, my own HTTP server library.

## Obsidian plugins

### WebDAV sync

[WebDAV sync](https://codeberg.org/LunarWatcher/obsidian-webdav-sync) is a small obsidian plugin for syncing vaults to WebDAV.

### LiviUtils

[LiviUtils](https://codeberg.org/LunarWatcher/obsidian-utils) is a bundle plugin with utilities. This structure was largely picked because of Obsidian's absurdly slow review time, but it was kept after the move away from always requiring manual review because it's convenient to bundle utilities.

## Utilities

### lspinstaller

[lspinstaller](https://codeberg.org/LunarWatcher/lspinstaller) is a utility script for installing various LSPs. It largely exists because different distros support different LSPs, and require the rest to be downloaded in other exotic ways. That's also before accounting for the LSPs that are installed via pip or npm. Also largely came about because clangd in ubuntu's repos was out of date, and I needed a newer version.

## Web

### violet - a C++-based static site generator

[violet](https://codeberg.org/LunarWatcher/violet) came about because of the AI-sloppification of most other static site generators that used to be worth using.


## Misc

### dotfiles

Though normally not a project, my [dotfiles](https://github.com/LunarWatcher/dotfiles) also include an automation suite big enough that it counts as one.

The main feature of it is the makefile setup, that allows me to just type a single make command to set up a new machine. It also includes a lot of other automation, a `.emacs` and `.zshrc` with lots of utilities, and attempts to gitops most of my core setup. Certainly has its problems, but I am happy with how it has turned out.

[^1]: Its package handling features are too primitive to call it a package manager. It installs automatically, and updates to the latest version when a specific command is run. It has no other features that would technically classify the package handling features as a package manager. I believe it's still called a package manager somewhere, but that's just because it's a recognizable description
