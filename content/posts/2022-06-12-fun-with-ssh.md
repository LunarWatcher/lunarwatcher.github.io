---
title: "Fun with SSH"
date: 2022-06-12T23:26:21+02:00
lastmod: 2023-12-29T17:06:15+01:00
tags: ["ssh"]
ingress: SSH is disgustingly flexible.
---

Three months ago, I decided to [dig into self-hosted NAS solutions]({{< ref path="/posts/2022-03-06-network-attached-storage-on-a-pi.md" >}}), because I wanted to free up a USB port, and I was tired of repeatedly asking "where tf did I put my disk now?" whenever I had to move it because laptops are painful.

I switched to a desktop after my MSI gaming laptop died[^1], which most definitely solved the USB shoratage. I believe I have 7 "normal" USB slots, as well as a USB C slot on the front, and plenty of IO options overall. Genuinely don't understand how I survived, but it was a problem at the time.

Additionally, during breaks long enough for me to go home, I was getting tired of carrying around an HDD (and once again asking where the hell I put it this time).

In conclusion, I needed a NAS, and I did get one.

That NAS is powered by SSH. I did not know SSH could do that before I hooked it up. 

The main advantage with SSH for me is that it's the only service I actually have exposed to the internet. The more it can do, the fewer services I need to expose, and the harder I can fortify my network when I need to connect to it remotely.

Now, unfortunately, I need a Windows laptop because my uni is annoying and hasn't fully built out computers for exam use. The only way I have a chance of maintaining a functional Windows partition is if this laptop is Windows-only; a concern I didn't think about when I sat there enjoying my Linux-main environment back in March. Y'know, before the great ~~reset~~ laptop death.

## VPN?

I have absolutely no need for a VPN for most use-cases, but I'm easily nerd-sniped. When I randomly asked myself "is VPN over SSH a thing", I had to try. The answer is [yes](https://wiki.archlinux.org/title/VPN_over_SSH), and the command is tiny:

```bash
ssh -TND 4711 pi@<ip>
```

After that, it's just a matter of setting up a proxy connection to use `localhost:4711`. The arch wiki has an entire section on that, but I use Linux Mint where I don't need to do that. I have a handy dandy GUI where it's trivial to set. Granted, it is a bit tedious to do. Would be a lot more convenient if there was a light-weight VPN adapter that sets up a VPN connection for the proxy, so it's a single click to connect like proper VPNs, but I'm not aware of any such programs.

Admittedly, I haven't tested whether or not that command results in a part accessible to the rest of the network, but my use-case is so limited it's likely irrelevant. 

## How Windows deals with an SSH-centric system

Windows wasn't my main focus when setting up an SSH NAS, because I wasn't expecting to use it as a driver OS, well, ever. Personally, anyway; I'm sure I'll have jobs in the future where I get stuck on Windows, but my NAS ain't for work, so that's absolutely irrelevant. It's no secret that Windows is a pain to work with at times, and official support for ssh came shockingly late.

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

## Forwarding/tunnelling to other devices

Because my self-hosting ideology heavily prefers reducing the number of exposed ports to a bare minimum, I only want one server exposed to the internet. This allows me to specialise its security measures to make sure a malicious actor can't just move onto the next port and have a different device to play with, where security measures haven't kicked in.

However, I still have a need to access both. I have two options for this:

1. Connect the VPN, then manually configure the OS to use the SOCKS proxy, and then connect to it as normal
2. Somehow forward the ssh request via the exposed server to the internal server, without just running the ssh command on the server. Running the command on the server requires the certificate to be on the server, which is insecure[^2].

As it just so happens, option 2 is in fact possible, and more convenient. 

The `~/.ssh/config` file is ridiculously powerful if you know roughly what you're doing. Aside standard declarations, you can use the `ProxyCommand` property with `nc` to forward an ssh command to an internal server.

```sshconfig
# The Host line can become an alias as well. As long as Hostname is set to the public IP,
# it'll work identically to a DNS lookup. The hostname can also be an address, if you
# have a DDNS service set up.
# I strongly recommend dedyn.io for it, but there are many alternatives and many preferences
Host nova.remote
    Hostname <public IP>
    Port <exposed port>
    IdentityFile ~/.ssh/homelab

Host sinon.remote
    # NOTE: unlike the Hostname for the externally exposed service, this has to be the _internal_ IP for the
    # server. The connection to the network is handled as part of the ProxyCommand call, which is run from
    # within the target network.
    Hostname 192.168.0.179
    IdentityFile ~/.ssh/homelab
    ProxyCommand ssh olivia@nova.remote nc %h %p
```

Through mechanics I'm not going to pretend to understand, the IdentityFile on the source system is proxied to the destination system when `ProxyCommand` is used. The IdentityFile for accessing servers does not exist on the server, so if it was attempted sourced from there, the `ProxyCommand` would be denied access.

This means a single exposed server can grant forwarding SSH access to other SSH-enabled servers on the network without exposing more than a single SSH port. 


**Note:** I'm not sure what happens if the exposed server and internal server has different IdentityFiles. It may or may not fail, though I'm pretty sure it should be fine. Take this with a grain of salt.

## Closing words

SSH is a shockingly flexible system; and the use-cases mentioned here are only the tip of the iceberg. Additionally, I'm aware that X11 supports forwarding over SSH. I have not tried this, because the devices I ssh into are headless, but it's enabled out of the box.

There's also stuff like `scp`, which is `cp` but across devices using ssh, but these are built-in commands leveraging ssh. rsync also support ssh, potentially providing options for remote data backups.

I have absolutely no idea how deep this rabbit hole goes, but a remote shell, filesystem, a VPN, and a remote desktop with nearly no server-sided config continues to amaze me. All of it being hosted through a single service also comes with the benefits of less stuff to defend.

Finally, I get all these fancy things, and all I need to do is harden ssh. Which I have, but that's also a story for later. This also means that my pi only needs to monitor traffic on a single port, for a single service. Nothing else is hosted, putting all the pressure on sshd to not have problems, instead of opening for multiple points of failure.

[^1]: The specs might be impressive, but MSI laptops have awful build quality, and design flaws that have been known for years.
[^2]: Running the SSH command directly on the exposed server is a massive security problem. Regardless of whether or not the servers are configured to accept the same SSH key, if a server is breached, they only get the public key. The public key is, well, public, and can be shared. However, to connect to an SSH server with an SSH key, you need the _private_ key. If you put a private key on the server, and that server is breached, any servers accepting that key are also compromised. It doesn't matter if you use one key or many keys; if you store them on a server that's breached, all of them are compromised. This is a horrible, horrible idea. You can admittedly password-protect the keys to prevent the servers from falling immediately, but passwords can be cracked with enough time and computational resources. The better option is not storing keys on a publicly exposed server.

