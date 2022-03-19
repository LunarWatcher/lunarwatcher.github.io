---
title: "Network shares are weird"
date: 2022-03-06T22:40:36+01:00
tags: ["raspberry pi", "nfs", "nas"]
---

I've been messing around with NAS solutions for a couple weeks now, because why not?

After a while of initially fucking around with various solutions, I settled on samba, because it's a major standard. It's easily supported, and supports integration with Linux Mint's integrated file explorer. That was actually a major factor when deciding on the protocol; if I can avoid messing with fstab and avoid manual mounting, I'd be really happy. That's not where I ended up, unfortunately.

Samba had a problem; a rather major one. In sufficiently large folders of particularly images, or just many files in general, samba completely choked. Opening a single image, typically max 10 MB, took several seconds.

My first round of assumptions were that it was a cable's fault. I was correct. The cable I used maxed out at 100Mbps, but 5GHz wifi wasn't better. The ethernet ports on my router are rated for a gigabit, and the 5Ghz Wi-Fi is rated for 400Mbps. Worse, the performance generally dropped on the client (read: my computer), so in my case, that wasn't much of an option. I did manage to get my hands on a second guaranteed CAT 5e cable, after which my speed well over tripled, to somewhere between 320 and 330 Mbps on average, over a few runs. These measurements were made with iperf3, and consequently are unaffected by the protocols and the HDD.

Yet, samba was slow. I tried applying performance tips from various places around the internet, with little to no impact. This more or less indicates one of two things (or both); either, Samba is an unrecoverably slow protocol. Other tips indicating newer versions of the SMB protocol might help ended up nowhere. `nmap` conveniently indicated Samba 3.x-4.x, so that's not it.

So I tried SSH, because that's apparently a thing I can do. After unbanning myself from fail2ban (who knew nmap on ssh tripped fail2ban?) and connecting, I did notice some interesting results. Using a benchmark of `time cat DSC_0055.jpg > /dev/null`, I consistently got ~0.85 seconds on average for Samba, and 0.38 seconds on average for SSH. Note that there were no attempts to kill any caches between these tests. The tests legitimately returned a consistent result of 0.85 seconds and 0.3 seconds respectively.

Enter NFS.

I decided both protocols were annoying to deal with, and ended up using NFS instead. using the benchmark, I end up with roughly 0.32 seconds. That doesn't seem faster than SSH, which is weird. However, all subsequent runs run at 0.0065 seconds on average. That's even faster than the 0.023 seconds on my pi, but that's not particularly surprising. I have a 3B+, where the IO speeds are the constraining factor, by a huge margin.

Now, interestingly, I initially tried the ssh mount through nemo. This turned out to be a mistake. Using `sshfs`, I get near NFS levels of speed, but with all the benefits of SSH.

I still don't understand why sshfs is so much faster than whatever form of SSH storage Nemo offers, but it works so I'm not complaining. I haven't touched fstab yet, but mounting it is fairly easy:
```
sshfs pi@sinon:/mnt/NAS1/ /mnt/NAS1
```

I had to `chown` `/mnt/NAS1` to do this, however. A pitfall with sshfs, particularly if you've set up your server to only do key authentication, is that it requires you to either have the ssh cert accessible to the superuser, as well as associated config, or `chown` the folder so you can mount into it without sudo.

I'm also not sure what type of read speeds I'm dealing with here for anything bigger, but it's fast enough. I don't do anything with a high data volume, but it manages to save and read the files I need fast, and that's all I really want. Aside backups, the only active use I have of that drive is when I draw stuff, but those files rarely exceed 10-30 MB. The biggest file in there at the moment is a 24MB one, and that's more than small enough for the theoretical ~330Mbps to work out fine.

Granted, there are better ways of doing a hacky NAS, but being a Linux main, this is good enough. I have 0 need for this to work on Windows, [though that shouldn't be a problem](https://superuser.com/questions/1423371/sshfs-remote-directory-mounting-syntax). I'm also doing this with an HDD I was using this way anyway, but with the now added advantage of not being physically connected to my computer's limited ports. Even if I had a full gigabit, the HDD would inevitably become a bottleneck. It might already be; my RPi only has USB 2.0, meaning the capacity maxes out at 480 Mbps anyway, but even that assumes the drive is capable of keeping up. I've lost track of what the drive is rated for, but considering it's an HDD, it could've degraded to the point where it's slower than my transfer speeds.

As a reminder, the measurements done were purely on the network speed, and the HDD was never a part of the 320-330Mbps measurement. Consequently, I have no idea whether it's able to keep up. I could check, of course, but I could also not, which I settled on. It keeps up with what I need it to do, and that remains good enough for me.

**TL;DR:** SSHFS is the best of the protocols I've tried, though there's definitely better options and hardware to explore. Having a (heavily abused; it's running Pi-hole and a number:tm: of bots) Pi 3B+ for pulling the load probably isn't helping performance, but it keeps up and that's all I want. In either case, it's an option worth exploring if you're messing around with self-created NAS systems.
