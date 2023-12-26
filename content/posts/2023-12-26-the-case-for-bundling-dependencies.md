---
title: "The case for bundling dependencies*"
date: 2023-12-26T15:33:12+01:00
tags: ["c++"]
---

I recently stumbled into [a page on the Gentoo wiki](https://wiki.gentoo.org/wiki/Why_not_bundle_dependencies) making a case against bundling dependencies while trying to fight a CMake install script, as I tried to bundle some dependencies and had a bad search term that led me to that page.

While they have many good points, they have a few points worth discussing.

## Standards

The biggest elephant in the room is standards, of which there are many to make any developer absolutely fucking miserable.

For the sake of argument, assume you have a program with 3 different dependencies. Optimally, you'd set something up so they can be retrieved with the package manager, the build system automatically handles linking, boom, you're done. 

There are two problems:

1. There are many different package managers
2. There are many different package naming schemes

Consider systemd's development package. If you, like me, are on a Debian-based distro, you'll want `libsystemd-dev`. On CentOS and Fedora, `systemd-devel`. On Arch, `systemd-libs`. On Nix, `systemdLibs`. OpenMandriva has `libsystemd-devel`. Gentoo may or may not be using the plain [`systemd` package](https://packages.gentoo.org/packages/sys-apps/systemd) for the development libraries[^6]. 

On top of that, there's different package managers used, with some distros even supporting multiple that may or may not be present on any given system.

I have no clue how many different variations there are total across the different major distributions, but needless to say that attempting to automate the installation process is an exercise in subjecting yourself to pain.

### Why duplication is already happening

Ubuntu is pushing Snap. There's also Flatpak. Self-contained AppImages are becoming a thing. AppImages are just a binary type and not a package manager, but there are some attempts to make package managers for them[^1][^2][^3]. These provide duplication with the system they're run on, though in different ways. AppImages being fully self-contained means one binary contains all the dependencies. Snaps and Flatpaks are proper sandboxes on top of separately managing dependencies. The push seems to be in the direction of "sandbox all teh thingz" (which I'm not a fan of, but that's an aside).

To talk about why, you have to look at the objectives of all these three. What do all the three projects have in common? 

All three of them aim to run everywhere. Why? Because Linux doesn't have a common package manager, so both Snap and Flatpak tries filling that void. AppImages are more for ease-of-distribution than being a standard, but still, the goal is to be distro-independent, with bundled dependencies being a selling point. Dealing with cross-distribution dependencies has been a pain in the ass for years, and there's no signs it'll change in the near future. 

All these three represent the polar opposite of apt, pacman, rpm, and other major package managers and/or distributions forms; rather than everything being shared by default, very little to nothing is shared. This kills most of the security advantages you get with the classic package managers, where many or all dependencies are shared. There's two primary reasons for this:

1. Convenience, particularly when the instructions don't include copy-pasta install commands[^4]
2. Hardware has gotten better, cheaper, and more widely available. Storage and RAM use isn't as much of a concern when even low-end devices ship with 8-16 gigs of RAM.

On top of these, there's stuff like Docker, which is fully emulated by design. Admittedly, Docker isn't inteded for installing every piece of software, but again, "runs everywhere" is one of its selling points for the stuff it's meant to run. Got a web service with some dependencies? Have a copy-pastable docker-compose file that sources the image for the service, run it, and you're done. Is it as light-weight as running natively? Hell no. Docker is arguably worse for storage and RAM use. Not only do you risk copies of the libraries used, but you need a copy of the C/C++ stdlib, and a copy of the entire kernel.

## Package availability

There are many packages that, simply, aren't in package managers. This includes [libcpr](https://github.com/libcpr/cpr), a fancy C++ wrapper around curl. This is [partly addressed by the Gentoo wiki page](https://wiki.gentoo.org/wiki/Why_not_bundle_dependencies#Easing_up_adoption_despite_odd_dependencies), but not with any solutions. The current answer is "just bundle it and then fix your software", but that's difficult to do, especially for people without a background in distributing to package managers. Getting the maintainer onboard is the common strategy, but this also comes with its challenges.

Especially in a commercial context, it's incredibly difficult to justify it. Imagine saying "I need 1-2 weeks to get one dependency into apt before we can continue with this project" to your boss when the simple solution is spending 5 minutes on setting up FetchContent in CMake. Yes, there are caveats, and yes, there could be an option to disable it if/when it's available in the package manager, but if it works with FetchContent, and the downsides are fairly small, and it's deployed commercially with commercial maintenance, the downsides are offset quite quickly.

This is particularly true for people like me, with no prior experience getting anything included in debian proper. The most I've done is create a .deb with self-bundled dependencies, and .debs are not remotely portable.

## Versioning

One of the major problems with package managers is versioning. With many dependencies, you get one version, and you'll be happy about it. There's many problems with the way package managers handle versioning today:

* Some libraries break ABI compatibility between updates
* Some software needs newer versions
* Stable distros (such as debian) often ship old versions - sometimes _very_ old versions. Linux Mint, based on Ubuntu 22.04, provides [Node.js 12.22](https://packages.ubuntu.com/jammy/nodejs).
    * If you want to update, you have to install it separately and manually, meaning you go entirely outside the package manager ecosystem to install it. Want to uninstall it later? Tough shit, you'll need to keep track of the files and remove them manually.

Version management is enough of a concern that there's an entire and separate category for version managers. Nix is one of the major actors in the field, with asdf being another receiving major use.

### The upsides and downsides of sandboxing

I'm going to shamelessly ignore a few arguments regarding security. The sandbox also has several disadvantages when it comes to separating software that's intended to communicate, meaning exceptions have to be created that, in my opinion, defeats the purpose of the sandbox. [There's an xkcd for this](https://xkcd.com/2044/) demonstrating the problem.

But in the land of dependencies, there are upsides and downsides. If two different programs need two different dependencies, that's not a problem. If you're using the native package managers, it absolutely is, and you need to stop using two different versions right this instant[^5].

## The middle-ground

Summarised, the current state of package managers is either share everything (see apt, pacman, etc.), or share nothing (snap, flatpak, and while it still isn't a package manager, AppImages), with systems and distribution forms that don't share anything being preferred among many users because it's much more convenient than dealing with dependencies.

Dependencies are by no means trivial to sort out. Version conflicts can be a problem, and so can dependency diamonds. Thats' why package managers exist; to abstract and sort out these problems. However, the value of package managers is undermined when _all_ the commonly used ecosystems have their own package managers, their own naming conventions, and their own package update routines. This has pushed many of the alternative package managers in the completely opposite direction, with the disadvantages that comes with. The introduction of additional package managers also incurs the wrath of the [standards problem](https://xkcd.com/927/); any standard that doesn't get wide traction just becomes competition for the existing package managers. That's what Flatpak and Snaps are now; they're competing standards that only serve to further complicate the existing clusterfuck that is package management on Linux.

There are a few takeaways from the different package managers currently in use:

1. Version management is increasingly becoming a concern
2. Cross-distribution support matters
3. Simplifying the workload for end-users as well as developers is becoming important
4. Version management shouldn't be at the expense of reusability where possible

We need a package manager that addresses all these problems. More importantly, we need a standard package manager with standard package names, and a standard system for declaring dependencies. This is easier said than done.

All the new package managers currently in existence exist because there are limitations with the other package managers. Many of the established ones were created concurrently instead, and just never unified. Getting agreement on a unified standard is also an enormous challenge _at best_, and impossible at worst. 

Wayland, an X11 replacement, is currently being adopted by an increasing number of desktop environments. The first version was [released in 2008](https://en.wikipedia.org/wiki/Wayland_(protocol)), about 15 years ago at the time of writing. X11 is 39 years old. There are arguments for and against both, but currently, the migration to Wayland is happening. If a package manager is adopted as fast as Wayland, we might see one around 2040-2050, and that's assuming it doesn't just become another competing standard due to resistance. 

It's needless to say that this is a bit problematic when lots of software is currently being developed, and most package managers advise in favour of a solution that's a disadvantage to developers and end-users (particularly for software not included in Your Favourite Package Manager:tm:). Hell, even my idea is straight up against the philosophy some distros take to package management, which further comlpicates this. 

## Implications for dependency bundling

The Gentoo article sides with the traditional take on package management; everything should be managed because there's upsides to doing so. There is, and they should be, but as the Linux ecosystem currently stands, there is one enormous downside that needs to be accounted for: there are massive downsides to only using package manager packages for developers and, often, end-users. Finding the right dependencies, and communicating what dependencies are required, becomes a massive pain in the ass. You might have the instructions right for one distro, but maybe not for spins or other versions of that distro, or for entirely other distros for that matter.

If I want to support only using package manager dependencies, I need to put in a massive amount of work - work that the Gentoo wiki claims would be lessend if software didn't manage dependencies on their own. Ultimately, there isn't a simple answer here, but a tradeoff between security, ease-of-updates, and ease-of-development. As the Linux ecosystem currently stands, ease-of-development is not prioritised. It might be within individual distros, but not if branching into multiple distros, with varying package availability.

For me, ensuring I can run the stuff I make whereever it is I'm developing (excluding software that intentionally doesn't run on specific operating systems) is much more convenient than trying to package everything. This is especially true when I don't expect my software to be considered for inclusion in any major package managers for the near foreseeable future. Putting in work to maybe eventually get my software included in package managers simply isn't worth it, when I can install it with all dependencies to `/opt` and call it a day with significantly less time and documentation required, as well as drastically decreasing the effort required by the user. 

Naturally, this doesn't mean all dependencies should be bundled. For example, [dnf2b](https://github.com/LunarWatcher/doesnotfail2ban) uses systemd for retrieving journald logs, and does so by dynamically linking a system-wide library. All the remaining dependencies are bundled, however. Some as shared objects, and some are header-only libraries. Dependency management in C/C++ is an entire debate onto itself, but this post is getting long enough.

To be blunt, if we want a world where dependencies aren't self-managed, we need a standardised, cross-distro (or even cross-platform) package manager that addresses versioning concerns, stability concerns for stable distros, and doesn't require nearly as much overhead to distribute to. Until the major distros decide to do so, bundling dependencies is often easier to do for developers, and to install for end-users. Yes, there are security implications, and may require more explicit updates depending on how the libraries are configured, but at least it can be distributed with one set of instructions, rather than having instructions that vary from distro to distro. 

[^1]: https://github.com/srevinsaju/zap
[^2]: https://github.com/vikdevelop/apm
[^3]: https://github.com/simoniz0r/spm
[^4]: I spent an unnecessary amount of time to build Vim from source due to this. Getting all the required libraries is difficult on a good day. Appended it to a makefile so I never had to worry about it again.
[^5]: Some exceptions exist, of course. Distros bundled both Python 2 and 3 for a long time. I can install 3-5 different versions of Clang as well. However, this is for very major versions. I can only install Python 3.11 and 3.12. Got software using 3.5 with some pip dependency that doesn't support 3.8+? Tough shit. I fairly recently ran into a similar problem with node, where I had a too recent version for a program I wanted to install. Granted, I installed said too new node.js outside apt, but still. 
[^6]: Searching the gentoo package archives for systemd-dev only yields the systemd package, with no apparent development package. I was unable to determine if there's some other way to get it, or if it's just directly part of the plain systemd package. Take this with a bucket of salt.
