---
tags:
  - Linux/Networking
  - DNS
date: 2026-01-06T03:17:31+01:00
---

nmcli can be a filthy fucking liar about what DNS it uses. `nmcli` self-reports using 9.9.9.9, which it's set to in the netplan as well:
```bash
❯ nmcli dev show | grep DNS
IP4.DNS[1]:                             9.9.9.9
```

While still quietly using another DNS. The netplan says 9.9.9.9, nmcli says 9.9.9.9, `dig` says local pihole address. Why?

It's likely because, in this particular case, the server was set up with some legacy setup that I never cleaned up after installing networkmanager. `resolvectl` shows the correct situation:

```bash
$ resolvectl dns
Global: 192.168.0.179
Link 2 (eno1): 9.9.9.9
...
```

Note the "global" field; this is a traitorous field. It's set by legacy shit, and should be empty. On my desktop, which respects my networkmanager-defined DNS, it is in fact empty. 

This field is why nmcli lies. Its DNS appears to be steamrolled outside nmcli's control.

More interestingly, for whatever reason, this caused intermittent certbot failures, and after a certain point (the day I'm writing this), near constant failures. On further investigation, this was because `/etc/systemd/resolved.conf` set `DNS` explicitly:

```ini
[Resolve]
DNS=192.168.0.179
DNSSEC=no
DNSOverTLS=no
```

Changing or commenting out `DNS` here (it's commented out on my desktop) changes or removes the global field. Removing it makes networkmanager's DNS be respected. 

I'm not clear on why pihole caused certbot to intermittently fail, and I honestly don't feel like finding out. My assumption is that pi-hole's cache is more aggressive than certbot-cli is designed to deal with. But there isn't really a reason for my server to be on the pihole DNS anyway; it has a `hosts` file that correctly maps all the domains to add some resilience to pihole outages, which has been a recurring problem at times. Though this was admittedly mostly before uptime-kuma turned into AI slop and got axed from my homelab[^1], because uptime-kuma was linked to NTFY, so a DNS outage caused a ton of "outage" notifications.

[^1]: This is such a fucked up timeline
