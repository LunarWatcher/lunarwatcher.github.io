---
title: "Fun with SSH"
date: 2022-06-12T23:26:21+02:00
tags: ["ssh"]
---

Three months ago, I decided to [dig into self-hosted NAS solutions]({{< ref path="/posts/2022-03-06-network-attached-storage-on-a-pi.md" >}}), because I wanted to free up a port, and I was tired of repeatedly asking "where tf did I put my disk now?" whenever I had to move it because laptops are painful.

I switched to a desktop after my MSI gaming laptop (don't buy MSI gaming laptops, it'll break fast and you'll regret buying it; and yes, I'm still pissed about a three year old laptop breaking. I digress), which most definitely solved the USB shoratage. I believe I have 7 "normal" USB slots, as well as a USB C slot on the front, and plenty of IO options overall. Genuinely don't understand how I survived, but it was a problem at the time.

Additionally, during breaks long enough for me to go home, I was getting tired of carrying around an HDD (and once again asking where the hell I put it this time).

In conclusion, I needed a NAS, and I did get one.

That NAS is powered by SSH. I did not know SSH could do that before I hooked it up. 

The main advantage with SSH for me is that it's the only service I actually have exposed to the internet. The more it can do, the fewer services I need to expose, and the harder I can fortify my network when I need to connect to it remotely.

Now, unfortunately, I need a Windows laptop because my uni is annoying and hasn't fully built out computers for exam use. The only way I have a chance of maintaining a functional Windows partition is if this laptop is Windows-only; a concern I didn't think about when I sat there enjoying my Linux-main environment back in March. Y'know, before the great ~~reset~~ laptop death.

## VPN?

I have absolutely no need for a VPN for most use-cases, but I'm easily nerd-sniped. When I randomly asked myself "is VPN over SSH a thing", I had to try. The answer is [yes](https://wiki.archlinux.org/title/VPN_over_SSH), and the command is tiny:

```
ssh -TND 4711 pi@<ip>
```

After that, it's just a matter of setting up a proxy connection to use `localhost:4711`. The arch wiki has an entire section on that, but I use Linux Mint where I don't need to do that. I have a handy dandy GUI where it's trivial to set. 

Admittedly, I haven't tested whether or not that command results in a part accessible to the rest of the network, but my use-case is so limited it's likely irrelevant. 

## How Windows deals with an SSH-centric system

Windows wasn't my main focus when setting up an SSH NAS, because I wasn't expecting to use it as a driver OS, well, ever. Personally, anyway; I'm sure I'll have jobs in the future where I get stuck on Windows, but my NAS ain't for work, so that's absolutely irrelevant. It's no secret that Windows is a pain to work with at times, and support for ssh came shockingly late.

As a result, it probably doesn't come as a shock that sshfs on Windows is... not great.

I've mainly mounted from the terminal on Linux, in part because my private key is password protected, and adding a network share to fstab is scary. I know, weak argument, but I prefer messing with high-level stuff that can't fuck up my OS if I make a single typo.

I'm sure there are some better options, but neither of the GUIs that also support Windows isn't it. In fact, neither of them support password-protected private keys. That's not stonks if you have a password-protected private key.

Does not help that doing this on Windows is pretty much a hack.

On the bright side, using the control panel, the proxy is actually supported. Settings does not yet support SOCKS proxies, but it does the trick. Unlike sshfs, though, it doesn't require nasty non-standard commands to run.

Here's the flow on Linux: `sshfs pi@<ip>:/<path>`. It's straight-forward, I can close the terminal afterwards, and it just works. It's some times weird if the network disconnects, but I'm sure there's a better way to handle that somewhere.

On Windows, however, I have to run two commands:
```
set PATH=C:\Program Files\SSHFS-Win\bin\;%PATH%
sshfs-win.exe svc \sshfs.kr\pi@<ip>\<path> Z:
```

Bonus: using `sshfs.exe` instead of `sshfs-win.exe` makes the disk fully impossible to unmount, at least if `-d` isn't supplied. It's registered as a local disk with `sshfs.exe` for whatever reason, and the explorer does not provide a button for unmounting. Killing the sshfs process simply makes the explorer error out, but it doesn't remove the disk.

Rebooting did make the drive go away, but that's a bit overkill.

Windows' own UI does _not_ like the password protected private key, and neither do any of the other UIs; neither sirikali nor sshfs-win-manager work with password-protected private keys.

Password-protecting might be the reason it's a bit annoying on Linux as well, admittedly, but it's so much more convenient to work with, at least for my relatively limited use at the moment. The command isn't a clusterfuck anyway.

How extensively Windows can be used in an SSH-centric system is unclear at the moment. It barely supports the basics at the time of writing. Consequently, I wouldn't recommend going full SSH if you plan on having any Windows computers actively using it.

## Closing words

SSH is a shockingly flexible system; and the three use-cases mentioned here are only the tip of the iceberg. Additionally, I'm aware that X11 supports forwarding over SSH. I have not tried this, because the devices I ssh into are headless, but it's enabled out of the box.

There's also stuff like `scp`, which is `cp` but across devices using ssh, but these are built-in commands leveraging ssh. rsync also support ssh, potentially providing options for remote data backups.

I have absolutely no idea how deep this rabbit hole goes, but a remote shell, filesystem, a VPN, and a remote desktop with nearly no server-sided config continues to amaze me. All of it being hosted through a single service also comes with the benefits of less stuff to defend.

And on top of that, there's also tunneling. This is something I'm gonna get more into when I get a second pi (my 3B+ is about to hit its capacity for hosting), and while I'm not yet sure how far I can get, it would be really cool to hook it up in a way where `pi@host` connects to the internet-facing device, while `otheruser@host`, still requiring authentication first, forwards the connection to the second host. My hope is that this is possible in a way that does two-stage authentication; first once to connect to the internet-facing pi, and then one to connect to the second pi.

This may be an application for the VPN, but this is all a problem for future me when I actually have two devices to experiment on. I'll likely publish a blog post with what I find when I cross that bridge.

Finally, I get all these fancy things, and all I need to do is harden ssh. Which I have, but that's also a story for later. This also means that my pi only needs to monitor traffic on a single port, for a single service. Nothing else is hosted, putting all the pressure on sshd to not have problems, instead of opening for multiple points of failure.
