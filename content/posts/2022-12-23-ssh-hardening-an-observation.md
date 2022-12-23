---
title: "SSH hardening: an observation on the efficiency of changing ports"
date: 2022-12-23T16:21:01+01:00
tags: ["ssh"]
---

I often open an SSH port to the internet, largely when I need to access my devices remotely. I've taken numerous measures to harden my servers, but  the biggest problem has always been DDOS protection. 

DDoSes attempting to brute-force passwords are tough out of luck thanks to password auth being disabled, but that doesn't prevent various botnets from trying. Especially over IPv4, it's not news that these bots scour the internet to look for open ports.

In my experience, within a matter of minutes to days, bots start hammering at my recently opened ports. There isn't much they can do, but open ports are always a risk. The more opportunities these bots get to attack, teh higher the chance an unexpected vulnerability is discovered and exploited. Reducing attack vectors is therefore a good idea.

Many articles emphasise the importancy of reducing availability of features. [DigitalOcean's article on the subject](https://www.digitalocean.com/community/tutorials/how-to-harden-openssh-on-ubuntu-18-04) mentions many of the same standard choices; disable password authentication, disable redundant features, restrict access where possible. Among other things, they also recommend whitelisting IPs.

Don't get me wrong; this is all good advice. Whitelisting IPs, if possible, is also more or less a guaranteed stop to most, if not all attacks. You don't even need to do this on the server itself. Many routers support whitelisting IPs in the port forwarding process. The whitelisting can be done fully at a router level rather than on the server.

But then there's use-cases like mine; I open ports to access it from whereever I am. That may or may not be on a predefined set of IPs, but I can't define them in advance because there's dynamic IPs involved as well. Personal use, or open use in general, struggles from similar problems; the highly efficient strategies almost guaranteeing little to no unauthorised access aren't feasible.

What do you do then?

Most articles recommend tools like [fail2ban](https://github.com/fail2ban/fail2ban) (which is buggy as hell and misses a whole lot of attacks), or [CrowdSec](https://www.crowdsec.net/) (which I found to be inefficient as well -- awful block rates. Cool in theory, not in practice). In fact, CrowdSec did the exact opposite, and exposed me to more attacks than fail2ban, and fail2ban already had an uncomfortably high miss rate.

Since none of the standard tools work, I started [working on my own](https://github.com/LunarWatcher/doesnotfail2ban), but my attention has been elsewhere, so it's not complete. I still needed to open a port, and I don't have time to get my own tools ready. The only option left is changing the ports.

Now, because I don't want to specify the port manually, I did leave it on port 22 internally, but I set up my router to forward it from an unspecified port with a numeric value greater than 1000. (Read: external:1234 -> internal:22).

In the past week or so, I've had a grand totalt of three attacks from three IPs, all of which gave up. These used two different attacks:

* 2x attempted password brute-force
* 1x HTTP injection trying to attack what appears to be a smart TV

In a comparable amount of time after opening :22, this is an insanely low amount of attacks. Here's an equivalent graph from last year:

<img src="/img/ssh bans.png" alt="Image showing the ban graph; there's over 8000 bans at the peak" />

Each interval is 1 million seconds, or around 12 days. This graph has some curiosities that are entirely my fault;

* The dip to 0 in the middle is from when I fucked up my fail2ban install
* the dips at the end come from bans expiring
* When the graph flatlines towards the end, that's the number of new bans counteracting the number of expirations
* A few days into the dip, the ban duration was changed from whatever it was set to (I don't remember, nor do I have a way to check), to being a permanent ban

The growth up to the dip is not affected by a high amount of unbans. In a few days, for reasons I'm not going to pretend to understand, I went from a couple hundred bans total with a few attacks per day, to hundreds of attacks per day.

Over those months, several thousands of devices hammered away at my poor exposed port, and it being detected was clear in a matter of days. Going from that to just a couple in a week demonstrates that changing the ports does help.

However, as usual with security, this alone will never be enough. You should always take additional steps to secure your exposed devices, and keep these devices up to date. All this does is demonstrate that changing the port reduces the amount of attacks; but not necessarily the severity of the attempted attacks.

Many of the bots I've observed having a field trip with inefficient password brute-forcing against my pubkey-only server also seem to be accompanied by "dumb" nmap bots, and by default, nmap stops around port 1000. However, it can be configured to scan all 65000 ports, at which point, [it's not a shock that it catches everything](https://nmap.org/book/performance-port-selection.html).

At least for now, switching to a high (and non-standard!) port reduces the probability your port in particular is scanned and attacked. I cannot emphasise this enough: obscuring the open port by hiding it on a non-standard and normally unscanned port, as demonstrated here, does reduce the number of attacks, but [isn't a security measure on its own](https://www.baeldung.com/cs/security-by-obscurity). If a sufficiently large botnet with scanners scanning all ports on all IPs finds you and coordinates an attack, you're right back to needing a fail2ban-like solution.

All changing the port does is reduce exposure to buy time, and from what I've observed, it's quite efficient at that. Thanks to a lot of the mainline internet-scouring bots being dumb and focusing on wide coverage rather than full coverage of fewer targets, it does reduce the number of attacks from these dumb bots. It does not stop attacks from anyone sufficiently dedicated to go after you in particular, or botnets doing wider scans than the average botnet.

**TL;DR:** changing ports has a clear effect at reducing the number of attacks, by hiding from the standard, dumb gruntwork bots of the internet, but security by obscurity is never enough on its own. More layers of security overall help to add more security to a device, and while port swapping is a solid contribution to that, it isn't a protection measure when attacks do happen. Port swaps aren't a replacement for tools like f2b/CrowdSec/etc., but it does reduce the amount of work they have to do by a sizeable margin.
