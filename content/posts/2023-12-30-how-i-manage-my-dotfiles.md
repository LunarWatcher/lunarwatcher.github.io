---
title: "How I manage my dotfiles"
tags: ["dotfiles"]
date: 2023-12-30T17:52:22+01:00
ingress: "There's many different ways to manage dotfiles. Here's how I manage mine, and piggyback off that system to automate other aspects of system setup"
series: ["Dotfile management"]
---

When I started using Vim back at the end of 2018/the start of 2019, I set up my first proper config file. Prior to this, at most, I had a single `.bashrc` that was mostly standard, with a few system-dependent `PATH` changes. On January 25th 2019, [I uploaded the first revision](https://github.com/LunarWatcher/dotfiles/commit/53a4d7d1c461f12d2b759d33c7f1fde212d24d4d) of my `.vimrc` to GitHub. At the time, disregarding the readme, there was a tiny `.bashrc` with Cygwin-compatible maps. Today, there's 19 files, and I have plans in the very near future to add more.

Back when I published the first versions of my dotfiles, there was no automation of any kind. It was just file backup, and I had to manually copy stuff when I made changes, or needed to deploy to a new system. It was far from optimal, to put it mildly. 

## Dotfile managers, and why I don't use them

I do want to acknowledge that there are many tools aimed at dotfile management. There's a GitHub project that, among other things, [maintains a list](https://dotfiles.github.io/utilities/) of many different dotfile managers.

There's nothing inherently wrong with using a dotfile manager. Back in 2019, I didn't think that there would be pre-made systems dedicated to syncing dotfiles. However, I've looked at a few of the implementations at various points in time since then, and I've concluded that they're not something I want to use. 

One of the major reasons I occasionally consider using a dotfile manager is that they implement most of the tedious parts. Got different files for different system configurations? Specify it once and it'll be automated with no extra code or target fuckery. 

However, as far as I'm aware, there isn't a single embeddable dotfile management system. They all require installation of some or another form. Makefiles, on the other hand, come pre-installed on many systems. 

The reason this matters is that it prevents me from writing a makefile that fully deals with boostrapping. When I get a new system, my procedure is simply making directories, cloning my dotfiles, and running `make all` (with some exceptions where I run other commands or additional targets). My makefile is set up not just to install my dotfiles, but to bootstrap my system. It installs compilers, languages, package managers, build stuff, and anything else I need. It also installs steam and discord, the font I use, removes stock software I don't use willingly, and adds other stuff I use regularly. Additionally, by actively using targets, it doesn't do this on every system. I can install just my dotfiles with `make dotfiles`. There's also a target that installs all the dependencies required for the different dotfiles, and a separate target for software.

With a dotfile manager on the other hand, I first need to install stuff I need to run the manager. This ranges from easy with a single apt command, to a combination of apt and another package manager (particularly pip or npm). Specifically if npm is involved, this is not a great solution for me. Because I use stable distros, I have to install node from source to get the latest version as the LTS is often so old that software I need cuts support for it. I've [learned my lesson after Python screwed me over]({{< ref path="/posts/2022-12-23-ssh-hardening-an-observation.md#ban-stats" >}}) with far more important software. The dependency install process is also much more complex and manual on Windows due to the lack of a proper package manager.

I do want to reiterate that there isn't anything wrong with using a dotfile manager. If you prefer to use one, do it. As long as you back up your dotfiles and have a way to install them, that's the important part.


## Goals

Before getting into what, let's talk about the specific goals. As already spoiled, just managing dotfiles isn't the entire goal. The additional goals are:

1. Managing shared files containing system utilities
2. No update process[^1] aside running `git pull` for previously installed files. Naturally, new additions may require re-running a command for the files to link properly
3. Allowing for significant flexibility in automating other aspects of the system installation (except on Windows, because it's ridiculously tedious to automate)
4. This goal was added just a few weeks ago at the time of writing; automating service deployment in my homelab

Before getting into the implementation details, let's talk about the technical details of these goals:

1. Managing shared files is fairly trivial. Lookup paths can be managed with various techniques. Some still need to be installed, but that's not that big of a problem
2. Symlinks can be used to solve this problem, as the footnote already spoiled. This is not as trivial to get working reliably when needing to support Windows[^2], but that is not a major priority for me personally.
3. This is best done by combining makefile targets with dedicated installation files, and heavily ties into the systems required by #4
4. Installing services can be a lot more complex depending on the level of configuration required for the service to be operational[^3]. One of the early services I implemented the install system for is [uptime kuma](https://github.com/louislam/uptime-kuma), which is not the most difficult service to support.

## My current system

There are roughly three categories of functional files:

1. The makefile; handles all the core installation.
2. Support installation scripts for specific services or configurations; meant to automate stuff tied to one specific device, rather than a category of devices, which generally goes in the makefile.
3. The dotfiles themselves, including various support files for them. For example, my `.zshrc` stores the aliases separately, and a few utilities are separate as well. 

The makefile is the most important file here, and it lays the foundation for this article series. It can be used to define what files gets installed, what dependencies go along with them, and a lot of other stuff that I'll be getting back to later. It can be used to define and automate the deployment of entire server configurations if set up properly. Or just copy the dotfiles and do nothing else, if desirable by whoever implements it.

### The effects of portability on dotfile architecture

For portability to work optimally in certain scenarios, the dotfiles have to be modular. This particularly applies to separating OS or distro-specific stuff (depending on the type of file) from the core of the dotfile, so it can be hotswapped depending on the system details. Naturally, there are a couple exceptions to this that apply to dotfiles that can better self-manage without it affecting readability. One important example of this is my vimrc, which contains multi-OS configuration for a couple of very specific things. Separating it out doesn't make sense, but the .vimrc can also deal with it on its own, without it having any noticeable effects on readability, performance, or anything else of importance.

Basically, modular dotfiles for very system-dependent stuff allow for more flexible installation automation systems that don't have any significant negative effects at runtime.

## Why use a makefile rather than shell files?

To be short and to the point, makefiles have one major advantage over plain shell files; they handle target parsing for you. There's nothing preventing the use of shell files over makefiles. Targets are essentially just functions, and pseudo-targets that run other targets are functions calling other functions.

However, with shell files, you also need to do argument processing to invoke the right targets. When using makefiles, this is automatically handled by make, with no further code required. Make is simply a better out-of-the-box tool for the job than plain shell files, especially when makefiles are just as readily available as shell files. 

However, some parts of the install systems are still shell scripts. Currently, this applies to service installation wrappers for my homelab.

## What about OS and distro management?

For the most part, OS and distro management has not been a problem for me. My files are either OS/distro-agnostic (such as my `.vimrc`) or debian-centric, but still compatible with other stuff.

There are [many ways](https://stackoverflow.com/q/714100/6296561) to check for OS support in a portable way, and the neat thing about make is that the commands can be converted to variables and still work. The same goes for entire targets, so it's possible to conditionally select targets using variables. 

It's also possible to use non-portable shell-specific methods, such as regular if-statements in shell, but this limits the execution to UNIX-like environments. Granted, supporting both shell (UNIX) and Windows takes a lot of work regardless of which option you pick. I would recommend saving non-portable methods for device management.

For OS or distro-specific dotfiles, OS detection can be used to, for example, change a folder prefix to source a different set of files. The upside or downside, depending on how you see it, is that these detections have to be handled manually as-needed, and redesigned for each implementation. The upside to this is that the system still fully meets your specific requirements, so you're never lacking in functionality. You also don't have to do any more detections than you absolutely have to. 

## What about device management?

Depending on how far you take the automation systems, this isn't too bad either.

One of the major advantages for device management is that you can do detections based on the hostname, and you can often make more assumptions about the software on the device. If you for example configure systems for a server running Ubuntu Server, the host-specific configuration does have to conform to stuff supported by Ubuntu.

Similarly to OS and distro management, a few if statements and targets stored in variables can allow you to configure device-specific stuff fairly easily. Combine with device-specific scripts, and it isn't that bad to implement.

## Managing secrets and other device-specific variables

One of the things most of the dotfile managers I saw mention is encryption off sensitive files. I don't like this approach, as it's a very clunky way to manage secrets. This is especially true for secrets that may not be present on certain devices. For example, I have [ntfy](https://ntfy.sh/) set up on my network, but only some devices need tokens. I also make sure I use different tokens to minimise the work I need to do if one token goes bad for whatever reason. 

To deal with this, I have [a separate file](https://github.com/LunarWatcher/dotfiles/blob/master/.zshrc.local.template) that I save on a per-device basis as `~/.zshrc.local`. My `.zshrc` sources it if it exists, and does nothing if it doesn't exist. Per-system configuration variable names goes in the template, applicable fields get filled out on a per-system basis. Manual, yes, but more convenient than setting up encryption, particularly if some future event causes said encryption to be insecure[^4].

Encrypting files and pushing them is also an option, though this is left as an exercise to the reader that prefers encryption instead.

## Closing words and future plans

I go pretty far in my dotfile handling, but there are more (and simpler) ways to do it. I didn't need anything fancy at first, and found stuff to add over time. Even if you don't see a need for this level of dotfile management, at the very least make sure you have a backup of them somewhere easily accessible for you. Having a bare minimum backup is the most important part of dotfile management; any automation around those dotfiles is individual, and not something that has to be present from day 1. Ultimately, all configurations are individual. That applies not just for the contents of the dotfiles, but for the systems backing them as well.

I acknowledge that this post was thin on more specific, technical details and examples. This is an intentional move on my part. For one, I'm planning some drastic rewrites to implement OS-specific and device-specific implementations. As part of this, I have a second article in the works that's more instructional. Secondly, I wanted to talk more generally about my management techniques and the rationale behind it in this post, and separate the specific implementation details into an entire separate article. 

Regardless of whether or not the second article (and refactor) is done by the time you read this, [my dotfiles are publicly available](https://github.com/LunarWatcher/dotfiles/), including [the legendary makefile](https://github.com/LunarWatcher/dotfiles/blob/master/Makefile).

[^1]: The only exception to this is on Windows, where symlinks are incredibly difficult to get to work. 
[^2]: To be abundantly clear, both Windows 10 and 11 support symlinks, but they're not trivial to get. They may or may not have to be explicitly enabled in the registry (of all godforsaken places), and for Git Bash to cooperate, it has to be enabled there too during the install process.
[^3]: Some of you are going to be asking "what about Docker?" at this point, to which I have an extended rant worthy of an entire article (that I also don't want to write, so don't expect it to appear). To make a painfully long story short, Docker bypasses firewall rules with no way to disable it. There are ways to ensure security in spite of this, but I'm not comfortable risking having an attack point that I cannot restrict. This is also fully Docker's fault, as they prepend their rules to `iptables` on both boot and reboot. Docker has to be actively supported by various intrusion detection systems for it to work, and doing so is also a pain in the ass. 
[^4]: This is arguably paranoid, but a security problem that has a very, very low chance of happening is objectively riskier than a problem that cannot happen, period.
