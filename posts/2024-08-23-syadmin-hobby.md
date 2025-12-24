---
title: "Self-hosting is fun: everything in my homelab"
tags: ["homelab"]
published_date: 2024-08-23 00:51:29 +0200
---

I got my first Raspberry Pi back when 3B+ was the latest model - 6 years ago, all the way back in 2018. All I kept on it for several years was Pihole, and to this very day, it is still running pihole. But at a point, my needs scaled out of the Pi, and I ended up getting more hardware. While I'm still not quite at the "I have a server rack in my basement"-level (yet!), I do now have dedicated compute for server applications, and an increasing list of hosted services.

On today's episode of me writing stuff without a plan because I can, I want to talk about what I host, why I host it, and some hard lessons learned along the way.

## Hardware

My hardware is nothing fancy, but I'd like to introduce it anyway. 

As already mentioned, there's my Raspberry Pi. It hosts one thing, and one thing alone; Pihole. It used to host more, but I made the mistake of upgrading to a 64 bit OS, which cut my effective available RAM in half. I moved the last service off it just a few months ago, leaving Pihole left as the only service. I do have a weak spot for Raspberry Pis, but due to availability issues at the time I needed to upscale, I went a bit further than I had planned at the time. 

This leads me to my second piece of hardware; an old Optiplex that I repurposed. It'll be the main focus of this article, because it hosts all teh thingz. 

Due to space constraints, I currently don't have any standalone networking hardware, though that is high on my list of things to get once I get more space.

## Networking and security strategy

My security strategy is fairly simple; do not expose anything to the public internet, unless it's absolutely critical and required for the Thing:tm: to function. All traffic should route via SSH or VPN.

The only service exposed that isn't SSH or the VPN server is NTFY, and  that's operation-critical for reasons I'll get back to later. If you don't know what NTFY is, it's a push notification service that can be integrated into, among other things, monitoring software, or just invoked from the command line. I find it to be incredibly useful for getting notifications if the uptime monitor detects an outage, or if I'm waiting for a long-running task to complete (like tasks that run for days). I'll get more back to how I use it later.

However, anything hosted publicly, whereever possible, must also be hosted on non-standard IPs. This is to make it harder for the many internet scrapers to detect and access my services, which lessens the load on my other security systems. Pro tip for anyone considering self-hosting stuff on private networks: if malicious actors can't connect to your services, the systems defending them don't need to be as hardened.

Everything else can only be accessed from within the network itself, obviously either by actually being connected to the network, or by connecting with a VPN.

### DNS

DNS-wise, I have both public DNS resolution (via [desec.io](//desec.io), a dynamic DNS service) and network-local DNS resolution. The services available locally are resolved an defined in Pihole (as a combination of A-records and CNAME records). There are other ways to go about this, of course, but this is the strategy I'm sticking to.

## Software

### Pihole

Pihole used to be something I hosted just for the DNS-level ad blocking, and while that absolutely is high on the list of reasons I keep it, I also keep it for some of its networking capabilities. 

Specifically, its ability to define local CNAME and A records. As previously mentioned, Pihole currently serves as the main DNS resolution system. My servers do have a special `/etc/hosts` file with the local names though, because routing all server traffic via pihole leads to Fun Results:tm: if (when) there are DNS problems.

### Miniflux

RSS isn't quite dead yet, and it does have some useful applications. 

Rather than using a desktop RSS reader, I self-host an RSS reader. This is really useful for integrations with other stuff, though particularly Discord and NTFY.

### Hazel

[Hazel](https://github.com/LunarWatcher/hazel) is a much more recent addition, and one that started out as an adapter to allow Miniflux to post to Discord, and later NTFY. It's my own software, and it's something I work on for fun and for my very specific and often very niche applications.

It's currently in the process of evolving into a dashboard to replace Heimdall, which I have not listed here, as I don't really use it anyway and have plans to remove it entirely. 

<sub>Obligatory note that I don't suggest anyone else use Hazel, at least not yet. It's far from finished, and it's poorly documented and breaks regularly as a result.</sub>

### NTFY

High on the list of things I wish I discovered much sooner is NTFY, a push notification service.

I use it to monitor various stuff, including the state of my homelab, and to keep track of long-running tasks. I also hooked it into various other services, including Miniflux (though via Hazel, because Miniflux itself doesn't directly support NTFY)

### Uptime-kuma

At a certain point, I hosted so many services that I needed ways to manage the services. That's where uptime-kuma comes in.

Combined with NTFY, these two services make up the backbone of my monitoring systems. I monitor all the services I host here to make sure I can keep them up. For the most part, it just sits around doing nothing, but when shit does hit the fan, I get notified within a couple minutes of the outage.

There are specific things it won't catch, because it isn't hosted separately from a lot of the things it does host, but that just means there's a few failure modes that won't be detected. For now, it's fine, and a tradeoff I just have to accept.

<sup>Fun fact: Thanks to hosting monitoring systems, I accidentally managed to catch an outage in [billion dollar software](https://meta.stackexchange.com/q/402184/332043) around 45 minutes before the company themselves found the problem.</sup>

### SSH

While a bit of a given for at least some server use-cases, SSH is incredibly powerful.

By hosting SSH, I also automatically get a NAS (via sshfs). I can also use [forwarding](/posts/2022/06/12/fun-with-ssh.html#forwardingtunnelling-to-other-devices) to access other non-exposed SSH devices, leaving one hardened device as a network entry point. This means I only need to expose one port to access any servers I need to, drastically reducing the number of attack surfaces.

Obviously, accessing other devices this way still requires SSH authentication for each step, so the other devices still require SSH auth even after clearing the first auth wall. It's a neat system though - I love it.

### Wireguard

Wireguard is part of my security strategy, as previosuly mentioned. 

It is worth noting that I'm planning to replace Wireguard with OpenVPN at some point, because I've come to find it much easier to work with OpenVPN than wireguard. In turn, the OpenVPN server is [much more of a pain in the ass to set up](https://www.digitalocean.com/community/tutorials/how-to-set-up-and-configure-an-openvpn-server-on-ubuntu-22-04). Ironically, Wireguard is much more annoying to set up client-sided, at least from the command line. Funny that.

### Baikal

By far one of the more practically usable things I host, Baikal is how I do calendar stuff now. Granted, prior to installing Baikal, I took the masochistic route of keeping track of my schedule on paper, because past me thought that was more convenient for a good few years.

Baikal is an implementation around CalDAV, one of the major standards for digital calendars. The advantage to this is that it's incredibly versatile. While I did have to install a dedicated app on my phone (DAVx5) for the syncing bit, I can use _any bit of software_ as long as it supports CalDAV, or syncs with a system calendar set by whatever does the actual syncing.

It also has support for tasks, which I've started finding useful. I've  yet to find a good desktop client at the time of writing, but it's incredibly powerful to sync it alongside my calendars.

### Misc. support services

In addition to the services mentioned so far, there are a few supporting services I use:

* nginx: while not optimal and tedious to set up, it just works, and is trivial to update and doesn't require recompiling just to add base functionality.
* Syncthing: though I mainly use SSHFS, this is useful for certain applications (particularly Obsidian) where I need to actively sync notes, and may want offline access.
* Certbot, for reasons I'll get back to
* Misc. bots and other software for Stack Exchange, including the bot that drives the meta comment archives for SO and MSE. 


## Lessons learned along the way

### Finding things to self-host is surprisingly hard

If you go onto the interweebs to try to find stuff to host, the list is shockingly short. The same recommendations appear over and over; a few specific programs for streaming video content or any other form of media are high on the list of recurring recommendations. 
There are lists like [awesome-selfhosted](https://github.com/awesome-selfhosted/awesome-selfhosted) on GitHub that include more options, including some more niche applications, but finding stuff I need in those lists is still a challenge.

For a lot of my use, the answer is just "use sshfs". I don't need a dedicated thing hosting my pictures, because I just use sshfs. I don't need a dedicated thing for audio content (of which I have little anyway, because Spotify exists), because sshfs.

If there's anything I need to actively sync, syncthing is just as easy to use. For a lot of my use, using native programs to access media works just as well as having dedicated server software taking care of it. 

With this requirement for my use-case, the list of options drops fast, because this fundamental principle drives far more open-source projects than you might expect. Finding stuff worth hosting that I have practical use for has taken a few years.

To be clear, there are a lot of options out there for pretty much everything - but getting into the mindset of identifying proprietary software to replace with self-hosted software takes a while, and is arguably made more difficult by the lack of much more comprehensive software lists. Awesome-selfhosted and similar lists usually only include popular options - and that's fine, to be clear, but it does make it much harder to find more niche, but still useful software that fits whatever cursed thing I'm trying to do this week.

### Docker is horrible when general networking and firewalls are involved

... but also surprisingly useful for very specific complex non-public networking scenarios.

Starting with general networking, one of the major downsides with Docker is that it [shamelessly ignores ufw rules](https://askubuntu.com/a/652572/452364), and the workarounds aren't particualrly good. 

I'm sure it's better if the firewall is running on separate hardware, but when doing a combined setup, it's not particularly easy to have a functioning firewall setup. 

But for certain very specific networking things, it is useful. I have a seedbox setup on the very same server I've been writing about today, and it runs QBitTorrent (seeding Linux ISOs and the [Stack Exchange data dump](https://meta.stackexchange.com/a/224922/332043)) in a docker container, with gluetun to route all that traffic via a VPN. Doing this on bare metal would either require routing all the server traffic via a VPN, which isn't desirable in this case, or doing cursed configuration stuff to keep my local apps from  routing via the VPN. The former isn't an option, the latter sounds horrible and I don't hate myself that much.

The separate networking here saved me a lot of time (and may even have made this use-case possible in the first place), but when hosting services accessed locally, and with an on-device firewall, trying to get Docker to respect the inbound firewall is challenging on a good day.[^1]

[^1]: There are a few ways around it, even down at the firewall level, but having to work with weird docker shit just because it doesn't feel like respecting anything else is incredibly annoying.

### Self-signing SSL certificates is... mildly annoying

It's a real shame though, because this prevents effective use of fully local DNS resolution. If you want a properly signed SSL certificate, you need a FQDN, which usually means you need to pay someone (or get lucky and find a free DDNS service).

Up until recently, I exclusively self-signed my certificates, with the idea behind to avoid using a FQDN for _everything_. The reason I stopped is that I kept running into software that didn't support self-signed certificates.

---

To make a long story short, the conventional wisdom that you just install the certificate and you're good is a massive load of crap. If you install it in the OS store, that does cover most, but not all applications. Browsers often have their own certificate stores, so they need to be installed there too. This is all fun and games until you run into an Electron app, which both has its own certificate store.

There are [ways around this](https://stackoverflow.com/a/46789486/6296561) technically speaking, but on a per-application basis, support for self-signed certificates varies dramatically. I only switched after running into something that simply didn't support it at all. 

While some applications have a toggle to ignore certificate signatures, far from all do, which is a problem if your entire digital infrastructure is based on self-signed certificates. 

---

I do need to note that, fundamentally, certificate trust chains are a good thing; it does make it harder for malicious actors to make bogus certificates - but it does also make it harder for real-world (although niche) use-cases like localhost SSL. It's supposed to be possible to get around this, but again, in practice, getting all applications to trust your self-signed certificate is a lot of work. 

To finish  the note from earlier, this is why I started using certbot, and switched away from both self-signed certificates and local domains; to not have to fight apps almost every single time I want to access my own digital infrastructure.

### Monitoring is incredibly useful

For some reason or another, software eventually breaks. Having monitoring in place to catch it has been incredibly useful. 

It's also nice to see the uptime graphs, but that's just because I like seeing stuff working well :D

The custom dashboard I'm working on is meant to fit part of this, though not for dealing with uptime as much as merging stats and other things I like keeping an eye on in one place. Where it evolves from there is something I'll have to figure out as I go along. The dashboard is one of a few projects I went into with no clear plan for the end goal, but went ahead with it anyway because I have certain concrete sub-goals I want to accomplish, and working with servers is fun.
