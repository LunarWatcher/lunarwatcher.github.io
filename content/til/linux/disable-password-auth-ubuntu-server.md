---
title: "How to disable SSH password auth on Ubuntu Server (22.10)"
tags: ["linux", "ubuntu-server"]
date: 2022-10-22T16:12:31+02:00
---

Ubuntu Server has some garbage defaults, at least for certain installation options, that prevents you from disabling password auth the standard way.

Normally, which you still have to do, disabling password auth is done in `/etc/ssh/sshd_config` by changing `PasswordAuthentication` from `yes` to `no`:
```sshconfig
PasswordAuthentication no
```

Make sure it isn't also set to yes in that same file.

But on Ubuntu Server, at least if you enable sshd as part of the installation process and without importing a key for any reason, they add a file that prevents this. Specifically, they add `/etc/ssh/sshd_config.d/50-cloud-init.conf`, which sets `PasswordAuthentication yes`.

Files in that folder can completely override the standard `sshd_config`.

So if you find yourself in a situation where Ubuntu Server isn't respecting `PasswordAuthentication no`, there's probably a file in `/etc/ssh/sshd_config.d/` that's interfering. Delete it or change the setting in there instead; I personally preferred deleting the entire file, because I didn't want it to begin with.

Note that this can also apply to any other distro, but as far as I'm aware, only Ubuntu Server creates a file like that as part of its install process, and then doesn't have a single easily accessible bit of documentation saying it does.

Don't forget to ensure you have a way in before restarting sshd with `sudo systemctl restart ssh` though. With password auth disabled, you need to make sure you have another way in, such as [a pubkey](https://linuxhandbook.com/add-ssh-public-key-to-server/) or at least hardware access. Otherwise, you're not going to get back in easily.
