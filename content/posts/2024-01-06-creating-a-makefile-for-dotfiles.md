---
title: "How to set up a makefile for managing dotfiles and system configurations"
tags: ["dotfiles"]
date: 2024-01-06T01:39:59+01:00
series: ["Dotfile management"]
toc: true
---

In the previous post in this series, I briefly described the general system I use for dotfile and system management, based on makefiles. This post dives into the technical details, including everything you need to set up your own makefile-based automation system.

Also note that the full make code in this article can be found in [this GitHub repository](https://github.com/LunarWatcher/makefile-dotfile-template). You can also see my implementation [here](https://github.com/LunarWatcher/dotfiles/blob/master/Makefile).

## Intended audience

If you want a system that only manages your dotfiles, and doesn't deal with dependencies, I recommend either using a very simple makefile (i.e. you don't need anything more than a single target), or if you need something more fancy, using a dotfile manager. The makefile framework used here is primarily intended for a broader use-case, where dotfiles, the dependencies of the dotfiles, and potentially other software is at the very least installed by the makefile.

The makefile demonstrated here is more of a system setup automation tool than a pure dotfile manager. If this is what you're after, this post is for you. However, note that this is just one possible setup. Your exact setup depends on what you need and what you don't need for your setup processes, and you can probably expect to make changes to the template here. This is a starting point, and not a one-size solution.

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
# This will be demonstrated later.


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

There's a fairly lazy way to deal with host-specific additions, which makes it an excellent place to start. For once, all the three major operating systems agree on a name of a command for getting the hostname; `hostname`. 

```make
help:
	... content omitted

# Defining the hostname 
host := $(shell hostname)

$(info -- Running on host $(host))

DEPENDENCY_TARGETS =
# All the other variable declarations omitted

-include make/hosts/$(host).mk
```

As per the makefile spec, `-` means "ignore errors if the include fails". This means that if a file for the hostname doesn't exist, nothing happens. Otherwise, the file is loaded. I'll get back to the contents of these included files in a later section.

### Identifying operating systems and Linux distros

Identifying operating systems is more annoying. Unlike with `hostname`, there's no portable way to identify the OS. Instead, we need a combination of a few techniques. 

Note that this if statement has not been indented. It cannot be indented with tabs, or its contents are interpreted as part of a target, which causes errors. It has to be space indented instead, which I opted not to do because my editor does not like mixed indentation[^4].

```make
ifeq ($(OS),Windows_NT)
currOs := win
else
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
currOs := linux
# The distribution should be able to be portably extracted by using
# /etc/os-release
# Note that there are more steps than just parsing this file on certain
# distributions. See
# https://gist.github.com/natefoo/814c5bf936922dad97ff
# for more details and alternatives
currDist := $(shell cat /etc/os-release | sed -n 's/^ID=\(.*\)$$/\1/p')
endif
ifeq ($(UNAME_S),Darwin)
currOs := macos
endif
endif

host := $(shell hostname)

# Debug information
$(info -- Running on host $(host))
$(info -- Detected OS $(currOs))
$(info -- Detected distribution $(currDist))
DEPENDENCY_TARGETS = 
# ... other variable declarations

# Note that this should be performed _before_ loading the host-specific file.
# This way, the host-specific targets can properly set up their dependencies

# First, check the OS
ifeq ($(currOs),linux)
$(info -- Linux identified)
# On Linux, we pay more attention to the distro than the OS
# Note that this is, strictly speaking, an implementation detail,
# and you can configure this however you want

# Note that the distro names need to be in line with the method you use to get
# the distro names. As demonstrated in the link in the OS identifier, there are
# many different ways to go about this. Use whatever method makes sense for the
# systems you use, and their available identification methods
ifeq ($(currDist),linuxmint)
$(info -- Loading Mint-specific stuff)
include make/distros/mint.mk
endif # mint

ifeq ($(currDist),ubuntu)
$(info -- Loading ubuntu-specific stuff)
include make/distros/ubuntu.mk
endif # ubuntu

endif # linux

ifeq ($(currOs),win)
# Windows; no file has been included for this demo. Use the `include` command.
# File content is demonstrated in the next section
endif
ifeq ($(currOs),macos)
# Mac; no file has been included for this demo
endif
```

Strictly speaking, there's nothing preventing a similar approach to the hostname solution to simplify the include blocks themselves. Using `-include make/distros/$(currDist).mk` also works, but I felt this approach gives more control for my own use-case.

### How the loaded files work

So far, the only thing set up is the loader, and not the files themselves. However, if you've been paying attention, you can probably guess what's happening next.

Each file you load contains its own set of targets, and these are added to the various target variables declared previously. For example:

```make
# make/distros/ubuntu.mk
ubuntu-dotfiles:
	@echo "Install some ubuntu dotfiles"

DOTFILE_TARGETS += ubuntu-dotfiles
```



#### Distro base

If you, for example, want to support multiple debian-based distributions without re-adding the same targets over and over, you can simply include another file. For example in `make/distros/mint.mk`:

```make
include make/distros/debian-base.mk

mint-bloat:
	@echo "Remove garbage"

CLEANUP_TARGETS += mint-bloat
```

Here's an example of what `make/distros/debian-base.mk` may look like:
```make
debian-base-update:
	#sudo apt update && sudo apt upgrade -y
	@echo "Update apt"

debian-base-dotfiles:
	@echo "Copy some debian-specific dotfiles"

DEPENDENCY_TARGETS += debian-base-update
DOTFILE_TARGETS += debian-base-dotfiles
.PHONY: debian-base-update
```

That way, any distros based on debian can use the same shared file for the family root.

If you then need to support Debian proper, you can do one of two things:

1. Use the base file directly
2. Use a separate file that also includes the base file, similarly to the mint example above

#### Handling device groups

Device groups are handled in the distro and OS-specific files by appending to the group-specific targets. For example, to add targets to be executed by the home group, you'd use:

```make
# make/distros/ubuntu.mk
ubuntu-home-packages:
	@echo "Install some ubuntu home packages"

HOME_TARGETS += ubuntu-home-packages
```

Substitute `HOME_TARGETS` for the other groups you may have

#### Handling other groupings of shared dotfiles

This is not included in the demo project, but in my case, I have some files that are shared across UNIX in its entirety; in other words, common tools that exceed just my main distro, and that I want elsewhere.

There are a few ways to manage this:

Common dependency files, similar to the distro base file. An `include make/common/unix.mk` at the start of relevant files is an easy way to share dependencies. If you're sharing between hosts, you can have a common file for that too. Includes are incredibly nice to use for problems like these. Depending on your implementation, you could also have a common file that doesn't explicitly add its targets to any of the runtime variables, but where the targets instead are added on-demand as direct dependencies of  targets in derivative files

For Linux in particular, adding a `make/os/linux.mk` file with all the dotfile copying also works. This can be added prior to loading the distro-specific files in the main Makefile. For example:
```make
ifeq ($(currOs),linux)
$(info -- Linux identified)

include make/os/linux.mk

ifeq ($(currDist),linuxmint)
$(info -- Loading Mint-specific stuff)
include make/distros/mint.mk
endif # mint

ifeq ($(currDist),ubuntu)
$(info -- Loading ubuntu-specific stuff)
include make/distros/ubuntu.mk
endif # ubuntu

endif # linux

ifeq ($(currOs),win)
include make/os/windows.mk
endif
ifeq ($(currOs),macos)
include make/os/macos.mk
endif
```

If you don't plan to use any other distros or operating systems than what you currently use, and there's no redundancy between the groups, this is effectively a non-issue that you don't need to worry about. This is of course unless you're planning ahead for a potential future where you'd need it.

### [This thing] doesn't seem optimal

This article, as well as my own makefile at the time of writing, is based on a massive revision I made to my previous makefile setup. That setup was _much_ more bound to a single system than the revision. As such, it isn't optimal even for me. Additionally, any system meant to automate on a this big a scale is not going to be applicable to everyone. I'm doing stuff you might not need, and additions you make might be stuff I don't need. That is fine, and by design.

The template demonstrated in this article (and that, as a reminder, is available [in full](https://github.com/LunarWatcher/makefile-dotfile-template) in a clonable format) is one possible starting point for an implementation. Your mileage will likely vary. The beauty of implementing this from scratch is that if something isn't optimal for you, or at all for that matter, you can fix it to fit your workflow better.

## Closing words

One thing I didn't expect to deal with when I started tinkering with configuration files was a system as meta as this. I don't expect to get everything right with my current revision of dotfile management, but it's fun to tinker with anyway. Hell, I already have plans for things I want to change and add to the system based on the current framework. It's kinda funny to me that an automation system that, initially, did nothing but copy files, can become just as important as the files it manages.

The amount of flexibility provided here is also incredible. I have not yet automated everything I can (or even plan to) as part of this system, but just having the ability makes it so much easier to set up systems. I don't do it _that_ often, but when I do, it saves me a significant amount of time. This is particularly true when I also have to configure stuff I haven't automated - either because I just haven't done it yet, or because it's unfeasible to do so. Or naturally, if there's files I don't keep anywhere public for security reasons, and therefore have to set up manually.

Then again, I really like automation in general.

---

If you want to see what my implementation looks like (which at the time of writing is heavily based on the setup demonstrated in this article), [it's available on GitHub](https://github.com/LunarWatcher/dotfiles).


[^1]: If you're the type to distro hop, you can of course still add a fallback handler for automating stuff. I haven't done it because I don't need to.
[^2]: I modularise the services so I can reconfigure it later if needed, but as a rule, the configurations of host-specific files and software is fixed until I'm forced to reconfigure the hardware.
[^3]: Like shell files, make doesn't run on native Windows. MinGW and Git Bash can both be used to get around this, though I don't recall if MinGW affects the Windows home directory by default.

    There used to be a port, but it hasn't been touched since 2006 (!). [Chocolatey does offer a make package](https://community.chocolatey.org/packages/make#individual), though I have not attempted to use it (nor do I have chocolatey installed for that matter). This might make it easier to run the makefile natively, but this is left as an exercise to the reader.

[^4]: Or I have not configured it in a way that allows for easier mixed indent. In either case, it's a pain in the ass, and not doing indentation is easier for now.
