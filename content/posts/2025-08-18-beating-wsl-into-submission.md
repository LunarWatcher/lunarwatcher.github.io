---
title: "Forcing WSL to cooperate with non-standard keyboard layouts"
tags: ["wsl"]
date: 2025-08-18T00:05:06+02:00
---

Since at least 2021 (earliest recorded instance), but likely since WSL was initially made, [it has had a bug with keyboard translation](https://github.com/microsoft/wslg/issues/173). 

When using GUI apps in WSL, WSL actually delegates the keyboard translation to the underlying distro rather than handling those bits itself, and then telling Linux what keys were pressed and what char that is. This is not a problem if you use a standard layout, but if you use a custom layout (for example to remove dead keys), the translation will fail, and the keyboard layout falls back to en_US, which is unusable. If the translation fails, the fix is not trivial, as there's no way to configure the keyboard in WSL at the time of writing.

Instead, the config has to be done manually in the underlying window system. WSL, under the hood, uses Wayland + XWayland. Getting the XWayland bit sorted is trivial, because X11 isn't an unstandardised piece of shit like Wayland is. All that takes is a `setxkbmap`, and you're set. Wayland, on the other hand, is configured on a per-window-manager-basis. Each of them have different config systems and different ways and places to set it. This is further convoluted by WSL making it hard to access the files in question, and wiping the files 

## The fix
and the TL;DR: of my pain and suffering; add this code to your `.zshrc` or `.bashrc`. Other shells may require translation before use (or you can just shove it in a `#!/usr/bin/bash` script and source it).
```bash
# Note: this script assumes you're using Ubuntu, and have a
# container called Ubuntu. If you don't, this needs to be changed.

# Check if WSL; this is purely for use in dotfiles that aren't
# WSL-exclusive, and can be omitted if you plan to only use your
# dotfiles in WSL
uname -r | grep -q WSL
if [[ $? == 0 ]]; then
    # X11; this may be redundant but I don't feel like checking
    # TODO: replace no nodeadkeys with your keyboard
    setxkbmap no nodeadkeys > /dev/null 2>&1

    # Wayland
    echo "Note: WSL translation failures are expected. This is just Windows being overly shit"
    WSL=/mnt/c/Windows/System32/wsl.exe 

    $WSL -d Ubuntu --user root --system bash -c "cat /home/wslg/.config/weston.ini" | grep '\[keyboard\]'

    # Unlike the X11 fix, this should not be run more than once. 
    # Otherwise, the pkill line would result in all your GUI apps being closed every time you restart your shell,
    # which would be infuriating
    if [[ $? != 0 ]]; then
        $WSL -d Ubuntu --user root --system bash -c "echo -e '[keyboard]' >> /home/wslg/.config/weston.ini"
        # TODO: replace the layout and variant in the next two lines with your keyboard layout.
        # This appears to be identical to the setxkbmap call, but I'm not sure if this is true for all layouts and all variants
        $WSL -d Ubuntu --user root --system bash -c "echo -e 'keymap_layout=no' >> /home/wslg/.config/weston.ini"
        $WSL -d Ubuntu --user root --system bash -c "echo -e 'keymap_variant=nodeadkeys' >> /home/wslg/.config/weston.ini"
        # Weston needs to be killed for it to pick up on config changes
        $WSL -d Ubuntu --user root --system bash -c "pkill -HUP weston"
        echo "Keyboard shimmed and weston assassinated"
    else
        echo "Keyboard already shimmed, no action needed"
    fi
fi
```
This script has to run at least once per boot of the WSL container. I put it in my `.zshrc` since I always start it before I start any GUI programs, but putting it in a systemd service should work too, if you can figure out how to get it to work reliably when Microsoft schenanigans are involved in complicating what's supposed to be an easy fix. The problem I had while making this a systemd service was getting it to run after WSLg started. This may have been user error, but I do not care enough to verify when stopping at `.zshrc`-loading worked for my use-case.

The rest of this article describes why the wayland bit is so unnecessarily convoluted (aside it needing to exist in the first place; this could've all been avoided if Microsoft bothered fixing a bug or two every once in a while).

## The root of all evil: the separation of WSL and WSLg

For whatever fucking reason, WSL and WSLg are split. When you drop into a terminal, you get access to WSL, while WSLg runs in an entirely separate environment. Not just that, WSLg's entire environment is reset every time you restart WSL, so setting your keyboard is not a one-time thing - it's a one-time per boot thing. 

Doing the changes further requires that you make the changes to a config file that's part of WSLg, and rebooting a window manager that's also part of, you guessed it, WSLg. This means that you need to break out of your WSL container in order to access the WSLg stuff you need. The only way to actually get access to it is using `wsl.exe`, which is a Windows program. This turned out ot be less of a problem than it sounded like at first.

Though I'm sure there's ways to automate this bit in Windows, to be blunt, it sounds horrible to do, and I did not want to it. I initially automated the X11 approach in my `.zshrc`, and used a manually-executed `.bat` script:
```dosbatch
wsl -d Ubuntu --user root --system bash -c "echo -e '[keyboard]' >> /home/wslg/.config/weston.ini"
wsl -d Ubuntu --user root --system bash -c "echo -e 'keymap_layout=no' >> /home/wslg/.config/weston.ini"
wsl -d Ubuntu --user root --system bash -c "echo -e 'keymap_variant=nodeadkeys' >> /home/wslg/.config/weston.ini"
wsl -d Ubuntu --user root --system bash -c "pkill -HUP weston"
```

The good news, and the news that I found out too late, is that you don't actually need to execute `wsl.exe` from Windows. If you execute `wsl.exe` from Linux, it'll be run from Windows instead.

This means that, by hard-coding the path, you can run `wsl.exe` from Linux for the same effect as running it from Windows, which means all the Linux-based automation systems can be used instead.

I did initially plan to use a service, but I found it much easier to set it up the way I have here. Figuring out how to reliably start a service only after WSLg has started, when it still runs in a different container, turned out to be too much of a thing to be worth the effort. It's probably still doable to make a systemd service for it, but this is left as an exercise to readers more masochistic  than I am.

For my use-case, I always end up starting a terminal before I start a GUI program, which means my `.zshrc` become a proxy for "WSL startup complete". By the time I start my shell, WSL has started, and WSLg has started as well, which is just a happy coincidence of how WSL's boot system appears to work, based on some limited testing where it refuses to drop me into a terminal until WSLg also manages to boot. These tests were based on `sudo reboot now` rather than `wsl --shutdown` though, and it appears to have had an awful lot of unintended side-effects, and it has drastically higher reboot time than `wsl --shutdown`. It's possible the reason a systemd service is off the table is because `reboot` just causes WSL to misbehave harder than it normally does, and that it would've worked normally. I could not be bothered verifying this once I had an automated solution, because I've already spent too much time on this.

TL;DR: use real Linux if you can, because WSL is a massive pain in the ass to use with anything but the bare minimum, fully standard, non-GUI setup, and every other use-case is bug-riddled in one way or another.
