---
title: "Heat issus and fan control on MSI laptops"
date: 2020-02-09T14:49:17+01:00
tags: ["annoying-bugs-linux-edition", "linux", "msi", "cinnamon"]
---

pwnconfig and fancontrol are the most widely referred to programs for fan control under Linux, and they've also been presented as alternatives to at least one Reddit thread asking for a Linux alternative to Dragon Center. 

MSI has fan control capabilities on Windows, so it's reasonable to assume the direct alternative (pwmconfig and fancontrol) works on Linux, right?

**Wrong.**

In an unnecessarily long debug session, I started with this notorious error:

> There are no pwm-capable sensors modules installed

After following various modprobe suggestions and messing with my BIOS settings, this didn't lead anywhere. `it87` and `nct6775` were the top two recommended modprobe targets on Google. That being said, these could potentially work for other people. They just didn't work for me, and I doubt they ever will.

Now that I look at it, this error makes sense because there are no fans with pwm support. The MSI fans, at least on my laptops (GS73 Stealth 8RE and GP70 Leopard Pro 2QF) are controlled by ACPI, which is completely unrelated to pwm, and by extension, most traditional fan control systems. Unfortunately, this also prevents thermald from seeing and using the fans. I'm not sure if this is tied to the control method or if there's another underlaying reason (such as the undetected SMBus detected by `sudo sensors-detect`), but nonetheless, a different approach is required. 

Another red flag here is that `sensors` only shows the core temperatures. Apparently, it supports displaying the fan speed on certain systems, presumably with pwm compatibility. This assumes `sensors-detect` can find it, however. For fans, pwmconfig is among the backing requirements for this to work. If pwmconfig doesn't detect it, neither will sensors-detect. 

Fortunately, there is an alternative exclusively designed for use with MSI on Linux - [ISW](https://github.com/YoyPa/isw/). [This issue](https://github.com/YoyPa/isw/issues/40#issuecomment-569489478) outlines install on Ubuntu rather well, so I'm not going to repeat it here. It's fairly straight-forward anyway. 

ISW manages the fan, which effectively replaces the cooling component to Dragon Center. It also supports Cooler Boost on systems with support for that. The switch isn't as fancy as on Windows, but it does its job as expected.

# Bonus: temperature spikes when switching between virtual desktops with Cinnamon DE

Disable Cinnamon's effects. Doing this, at least for me, significantly reduced CPU use when switching desktops (from one core doing 50% to one core barely doing anything noticeable). 

These random spikes of CPU activity do generate heat, especially on my CPU with 6 cores and a max speed of 4.1GHz. It's much better at managing heat if the load is constantly high, for an instance while playing a game, but this tiny load caused by the desktop switching causes an unnecessary load on a single core. Might just be my laptop for all I know, but if you've observed this too, try disabling the Cinnamon effects. 

That being said, I disabled all my effects long before this, and for some reason, it still caused a problem. I went into customize and enabled customization, and disabled _everything_ there as well, after which the CPU spikes disappeared. 

![Under the "customize" tab in the effects customizer, enable setting customization and set all the effects to none. Set the time (presumably the transition time for the effect) to 0 as well.](/img/heat-issues-fan-control-cinnamon-effects.png)


