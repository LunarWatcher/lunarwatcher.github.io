---
title: "IPv6 leak with OpenVPN"
tags: ["linux", "openvpn"]
date: 2024-12-25T00:23:25+01:00
---

## Problem
For some reason, OpenVPN has an IP leak problem when no IPv6 routes are specified. This means that if using OpenVPN to what I assume to be purely IPv4 VPN servers (looking at you, ProtonVPN), but you're on a network with both IPv4 and IPv6, ip leak services detect the local IPv6, but the VPN IPv4. This is mildly annoying, because using an OpenVPN client instead of the ProtonVPN client is far more convenient.

The native ProtonVPN app does not have this problem, to be clear. The leak only happens when using the OS-native OpenVPN client, which I massively prefer for two reasons. First, it lets me get a VPN connection straight from the network manager applet. Second, the ProtonVPN app  eats like a gig of RAM, and while I have plenty of RAM, it's just such a waste of compute for little to no benefit.[^1]

{{<figure
    alt="Screenshot showing the network-manager applet on Linux Mint, Cinnamon edition. The applet contains three sections; a censored block of wireless connections, an OpenVPN connection with a ProtonVPN entry, and a wireguard section with an active connection"
    src="/img/2024-12-25-network-manager.png"
>}}

[^1]: I like ProtonVPN, but seriously, the desktop app is absolute fucking trash in desperate need of optimising, especially on Linux. A full fucking gig of RAM (and that's before connecting) is completely unnecessary.


## A tangent on Wireguard

Wireguard is the main (and currently only) VPN I use in my homelab, and it does not exhibit this problem. Granted, getting Wireguard to cooperate is a bit more involved, and it's possible that my config accidentally blocks IPv6. IPv6 addresses _are_ in the list of passthrough IPs, but beyond this, I'm not sure how the internals of it work. The relatively standard config I have just works:tm:. My home network does _not_ have IPv6, so I have no way to verify if it's kinda sorta working as intended.

Even if it's failing to do IPv6 requests, it is behaving as I would expect a VPN connection to behave.

## Getting OpenVPN to cooperate

Spent a good few hours on this one; had to use the advanced connection manager to fully disable IPv6 for the VPN connection (Advanced Network Configuration -> vpn entry, settings -> IPv6 -> disabled). This can also be done from the terminal with this `nmcli` command:
```bash
nmcli c modify "vpn name" ipv6.method disabled
```

The internet recommended `ignore` and `link-local`, but this does not work. This just disables passthrough of IPv6 requests, which is literally the exact opposite of the goal.
