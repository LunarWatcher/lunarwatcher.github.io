---
{
    "title": "Untitled arch commentary",
    "date": "2026-07-16T22:45:43+02:00",
    "type": "notes",
    "taxonomies": {
        "tags": ["linux", "arch"]
    }
}
---

I am *checks calendar* 2.5 months into arch. I'm really pleasantly surprised by it.

## Installation

The installation experience isn't much to brag about. arch-install definitely makes the experience acceptable, but the lack of a default graphical installer does make the initial setup mildly annoying.

I wouldn't have had a chance a good few years ago, since there definitely is an extra learning curve to arch. Getting past that though, holy fuck, arch-install! It lets me export JSON files with the entire configuration, so I can get the core packages I need set up automagically. Parts of my dotfile setup are still dedicated to post-arch setup steps, largely because I still have non-core setup for various types of machines. 

I theoretically have a server-compatible setup already prepared, and while I really want to migrate my server to arch, migrating an LVM cluster is a bit hard. Not impossibly so, but there's pre-uninstall and pre-reinstall steps, and because it's all on the same hardware, I don't have anything to go back to if I fuck up the pre-uninstall. In retrospect, lvm was a bit of a mistake. I do not have enough disks to justify it. It does have two disks in it, so I could in theory shrink out the 2TB SSD and move the data to it (and possibly to the 1TB OS SSD, not sure how much data I have on it now), then wipe the 16TB disk and move everything back to it, but shrinking volumes takes aaaaaaaaaaaages, and there's just no good time to do it.

Anyway, server migration tangent aside, automation as a core feature of one of the top recommended ways to install arch? Fucking brilliant, I love it :3

## Migration problems

... or rather, mostly lack thereof.

Prior to migrating to arch, I had switched to KDE on Mint, largely because I had to do that on my work laptop[^1], and I really enjoyed it. Plus, I had fewer bugs with it[^1].

The migration included a bump from KDE 5 to 6, which broke some of the stored config I had. Not a big deal, I just migrated it manually and re-exported for KDE 6, and now my config will follow KDE head (with one version behind for potential future Linux work laptops on Ubuntu et. al, where KDE will be older than arch).

## Post-migration problems

Around the great AI slop machine-driven security patches (also known as anthropic increasing their stock value through fear), bluetooth broke. I tried and failed to roll back the kernel, which was annoying. Arch isn't really meant for rollbacks - I _could_ roll the kernel back, but everything is pinned to the latest versions of things, so rolling back is still spicy.

The patch came like a day later, and I got everything connected again.

### Non-arch post-migration problems

Also driven by AI slop machines, I had to axe my backup software. I have used [timeshift](https://github.com/linuxmint/timeshift/) for years, and timeshift is still fantastic - unfortunately, it's rsync-based, and rsync [turned to AI slop and took down everything that used it](https://github.com/linuxmint/timeshift/issues/548). Great fucking job.

Fortunately (?), I had misconfigured timeshift by mistake. It was set to make scheduled backups, but it was never set to start :facepaw: The good news with that mistake is that rsync never had the chance to fuck anything up. I had to uninstall rsync and timeshift, since rsync cannot be trusted anymore. RIP rsync though - it used to be so good that no one really bothered making anything comparable to it. It became an industry standard, and the maintainers decided to completely fuck over everyone by using AI slop machines.

[unison](https://github.com/bcpierce00/unison) looks like a solid replacement, and [just three weeks ago, it got an anti-AI CONTRIBUTING.md](https://github.com/bcpierce00/unison/commit/91421d0617b0fb543c0eee51bcb4d4791d8b0631) - love to see it. Not sure if it overlaps enough with rsync's use-cases for me to be able to add it to scripts for example. I have not read its docs or anything yet, I just know it exists, and I have a plan to look at it Later&trade;.

## Initial impressions

Aside fangirling over automation for longer than I'd like to admit, it really is a solid experience. Pacman is ass, and installing from the AUR is harder than I thought. I ended up avoiding it entirely, and haven't really missed it. Aside for nightly firefox, but I just downloaded the zip and stored it somewhere. It self-updates, so I don't really need to go through a package manager.

Discord being bundled in the package manager is great. Discord on Ubuntu didn't auto-update - that changed literally like within a couple days of me switching to arch though, so really bad timing on my part :p

One of the projects I wrote at one point to meet my needs is a package manager. I wrote it because I needed newer packages than Ubuntu could provide. I haven't even installed it :p Everything being up-to-date is fantastic, since I enjoy getting regular updates to the software I use. That does mean more risk (re: the kernel problem in the post-migration problems section), but honestly, aside system components, there's not really much risk in solid software that isn't developed with AI slop machines.

KDE in an actual KDE-dedicated system is also great. I do miss notification badges - notification badges were something I missed from Windows on Cinnamon for ages, but it was added I believe some time in the last year. I lose track of when it came. Then I of course switch DEs to one where notification badges aren't a thing. Will need to look into if there's like a replacement widget for the standard dock. I really like having notification badges.

KDE under Mint was a bit jank, because it coexisted with another DE that had its preferred default software. Not having that definitely makes KDE feel better. KDE also has a lot of really good software in general, though I only actively fangirl over Krita. Admittedly got that on steam rather than directly on my system.

Going back to AUR for a minute, it seems to be a fair bit more involved than I had hoped to get it to work. I assumed it would just be an equivalent to PPAs where you just add a package repo and it's done, but it's a whole other ecosystem that requires an additional package manager. And of course, [the biggest of the AUR helpers is AI slop now](https://codeberg.org/ethical-foss/open-slopware#aur-helpers). I'll get around to experimenting with paru (currently untainted) at some point, but it'll be at least a little while.

Even without AUR, the official repos contain _so much more stuff_. Both Obsidian and Discord just being available is great. 

I will definitely be staying on arch on my daily-driver. For the record though, I do still like mint. Bugs aside, the Mint project has done a lot of great work reversing a lot of the dumb shit Canonical has been doing. Blacklisting snap by default and bringing back apt packages that are just thin wrappers around snap commands on Ubuntu proper is a solid move. I can't really recommend Mint enough, especially as a beginner distro. It pulled me through a solid ~8 years of Linux use, and I have no regrets

[^1]: Technically work laptop VM, because it's Windows-as-a-shitty-BIOS. Cinnamon's compositor (? - the thing in cinnamon called muffin, I don't remember what it was classified as) has a bug that inexplicably breaks rofi in hyper-v. I've also had a number of other bugs with it on my main machine with screensharing, where I've been unable to share a monitor on Discord without screentearing. I initially blamed the driver, then Discord (because discord is ass), but looks like it was the DE. Not where I expected that to go.

