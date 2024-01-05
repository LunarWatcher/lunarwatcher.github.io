---
title: "How to set up a makefile for managing dotfiles and system configurations"
tags: ["dotfiles"]
date: 2023-12-31T02:21:56+01:00
series: ["Dotfile management"]
draft: true
---

In the previous post in this series, I briefly described the general system I use for dotfile and system management, based on makefiles. This post dives into the technical details, including everything you need to set up your own makefile-based automation system.

Also note that the full make code in this article can be found in [this GitHub repository](https://github.com/LunarWatcher/makefile-dotfile-template). You can also see my implementation [here](https://github.com/LunarWatcher/dotfiles/blob/master/Makefile).

## Intended audience

If you want a system that only manages your dotfiles, and doesn't deal with dependencies, I recommend either using a very simple makefile (i.e. you don't need anything more than a single target), or if you need something more fancy, using a dotfile manager. The makefile framework used here is primarily intended for a broader use-case, where dotfiles, the dependencies of the dotfiles, and potentially other software is at the very least installed by the makefile.

The makefile demonstrated here is more of a system setup automation tool than a pure dotfile manager. If this is what you're after, this post is for you. However, note that this is just one possible setup. Your exact setup depends on what you need and what you don't need for your setup processes.

### Prerequisites

This post assumes you're familiar with at least elementary makefile syntax. [Here's a tutorial contains pretty much everything you need](https://makefiletutorial.com), and then some, if you aren't familiar with it. Should you choose to ignore this prerequisite, the main thing you need to know is that makefiles are indented with tabs. Specifically, this applies to the rule definitions. Paradoxically, if statements cannot be tab-indented, _unless_ its contents are part of a target definition. This is not a matter of preference, this is a hard requirement from the makefile spec.

## Identifying the core requirements

With a system that has the potential to be as complicated as this one does, standardising the interface is important. To do so, there are three questions that need to be answered:

1. How do you determine what should be installed, and what kind of device you're dealing with?
2. How much variety is there in your system configurations? This refers to OS and  distro variations. If you primarily use Windows and Linux, and only use one family of distributions, that's very different to having multiple different distros and using the whole trifecta of major operating system families.  The more variety you have, the more code you need.
3. What automation and file categories do you have to work with? 

In my case, the answers are:

1. Identify the OS and distribution; Linux Mint is my daily-driver OS, while Windows is a secondary OS. Anything else is non-standard and not automated[^1]. Additionally, on Windows, I'll primarily be using Git Bash as a compatibility layer for simplicity[^3].
2. Minimal; all the Linux distros I use are debian-based, and Windows doesn't see extensive enough use to be extensively automated. However, I do have two device types; regular machines for daily use, and servers. I also expect that I need a separate type for installing stuff for work in the future, though this is a non-issue at this time.
3. I have quite a lot to work with.
    1. **File categories**: distro-specific files, host-specific files[^2], common files, and OS-specific files. For example, installing my zshrc on Windows is pointless, but the vimrc is portable, and should be installed everywhere.
    2. **Automation categories:** distro-specific, type-specific (daily-driver and server), and host-specific

Before you write your own makefile, I recommend answering these questions for yourself and your own applications. 

## Makefile strategy

Simply put, the idea is to use a combination of fixed targets that  define the order of actions (as well as supported actions), and a combination of fixed targets (for truly common dotfiles that work on all targets) and variables that dynamically define the targets that are to be executed as what part of the pipeline. For my use-case, I use:
```make
help:
	@echo "Default target; I use this to list the main interface targets"


# Variables need to be declared before the other scripts are loaded

# Used to load all common dependencies, including 
# software used by the dotfiles
DEPENDENCY_TARGETS =

# Used to load the dotfiles themselves
DOTFILE_TARGETS =
SOFTWARE_TARGETS =
CLEANUP_TARGETS =

# I have two primary groups; home and server.
# I plan to add work in the future, but the main difference is the supplemental software that gets installed.
# The kinds of groups you want to install are fully up to you. A similar system can also be used for other
# groups of software, depending on what you need and how you set up your machines.
HOME_TARGETS =
SERVER_TARGETS =

# Load stuff
# This will be demonstrated later

common-dotfiles:
	@echo "Symlink stuff for portable dotfiles"

dependencies: $(DEPENDENCY_TARGETS);
dotfiles: common-dotfiles $(DOTFILE_TARGETS);
software: $(SOFTWARE_TARGETS);
cleanup: $(CLEANUP_TARGETS);

core: dependencies dotfiles software
common: core cleanup

home: core $(HOME_TARGETS) cleanup
server: core $(SERVER_TARGETS) cleanup

.PHONY: home server common core cleanup software dotfiles dependencies
```

However, out of the box, this does very little. If you run it right now, all it'll run is the `common-dotfiles` target. Since all the variables are blank, many of these targets are just empty targets that don't do anything. This is intentional, and very useful. This means that if the entire file is run on an unsupported configuration, only the common files are extracted. This is to allow for the install process to go further where it can, but without trying something unsupported. It also means not everything has to be populated. Maybe your dependency install process automatically grabs all the software you want, or you have a package manager that automatically cleans it self up.

The various target variables are populated by different, domain-specific files. Some examples include OS-specific files, distro-specific files (including files for distro families), and host-specific files.

### Identifying hostnames



### Identifying operating systems

### Identifying distros

### Handling device groups

[^1]: If you're the type to distro hop, you can of course still add a fallback handler for automating stuff. I haven't done it because I don't need to.
[^2]: I modularise the services so I can reconfigure it later if needed, but as a rule, the configurations of host-specific files and software is fixed until I'm forced to reconfigure the hardware.
[^3]: Like shell files, make doesn't run on native Windows. MinGW and Git Bash can both be used to get around this, though I don't recall if MinGW affects the Windows home directory by default.

    There used to be a port, but it hasn't been touched since 2006 (!). [Chocolatey does offer a make package](https://community.chocolatey.org/packages/make#individual), though I have not attempted to use it (nor do I have chocolatey installed for that matter). This might make it easier to run the makefile natively, but this is left as an exercise to the reader.
