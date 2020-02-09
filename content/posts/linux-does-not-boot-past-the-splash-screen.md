---
title: "Linux does not boot past the splash screen with a NVIDIA graphics card"
date: 2020-02-09T14:45:48+01:00
tags: ["annoying-bugs-linux-edition",  "linux", "nvidia", "ubuntu-et-al"]
---

*Tested on Linux Mint 19.3*

For some reason I will never be able to comprehend, the Ubuntu(/derivative) installer decides to go _against_ the recommended option by its driver manager (the proprietary nvidia drivers, even if the proprietary checkbox is clicked) and installs nouveau. This might be a great driver on some systems, but personally? I've never gotten it to work. The installer's choice to install nouveau over the nvidia drivers therefore causes extra work for me after I installed it. Going with open-source is of course fine, but having an option to use proprietary drivers would avoid some issues like this, at least for me.

The problem with nouveau isn't that it's not recommended,  but it's that it's unstable. To what degree is a good question, but with somewhat modern hardware (GTX1060M and GTX950M), I haven't had a single successful install with nouveau. For all I know, it might be better on older hardware, but for me, it has either not worked at all, or it was unstable. Some issues caused by it were worse than others. This one is possibly the worst I've encountered: the OS fails to boot because of it. Other issues include that it simply doesn't work, or causes the display to stop working. Fortunately, with the display issues, ctrl-alt-f3 still worked, so it was fairly easy to fix. For a somewhat more notable source, [Google has blacklisted nouveau](https://www.phoronix.com/scan.php?page=news_item&px=Chrome-Blacklisting-Nouveau) due to instability. That being said, I'm sure nouveau could be good some day and be stable and even my preferred option, but as someone who just needs her shit to work now, it's not an option.

This does look more severe than it actually is, for reasons I don't understand either. The main issue for me was that my OS failed to boot. It got stuck on the boot screen and some times gave me random output from the system, which sent me on a wild goosechase down the completely wrong alleys. The boot screen some times disappeared into a single, white, blinking underscore in the top left corner. I managed to get to the login screen once, but after typing my password, the screen went black and nothing happened. Reaching a terminal wasn't possible either (ctrl-alt-f3 for an instance - nothing happened. Just another blank screen). 

Turns out, this can happen if nouveau is installed. This happened on my system that runs a GTX1060M, and nouveau was to blame. Fixing it is actually simple too. The solution I ended up using is disabling the drivers with `nomodeset` in Grub. Adding it is fairly easy: open grub. I force-rebooted my machine to get past the frozen loading and get back to boot, and grub, though I'm not sure if there's risks associated with that or not. 

Click `e` on the entry for your distro (i.e. Ubuntu or Linux Mint). Close to the bottom, there should be a line that starts with Linux, and contains (among other things) ` ro quiet splash $vt_handoff` (the underscore wasn't visible on my system for some reason, but there should be an underscore there). After the last argument, add `nomodeset`. Click CTRL-X or whatever other keybinding the UI tells you is to boot now (don't save it unless you have no other options - otherwise, nomodeset is cleared after a reboot, which is kinda the goal). 

Example:
```
linux /boot/vmlinuz-<version>-generic [...] ro quiet splash $vt_handoff nomodeset
```

Click the keybind to boot, and if you get in (if you don't, this doesn't work, or you did something wrong), go straight to the driver manager and install the proprietary nvidia drivers. You can install other stuff while you're at it, but fixing the graphics drivers is _the_ priority. After a reboot, the system should boot properly. 


