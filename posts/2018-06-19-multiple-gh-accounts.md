---
published_date: "2018-06-19 00:00:00 +0200"
description: Short guide on using multiple GitHub accounts on one computer in a way that doesn't require manual account changing
tags: ["git"]
title: Multiple GitHub accounts on one computer
---

I have two GitHub accounts; one for personal use, and one for work use. Occasionally, I want to use these on the same computer, but most SSH systems don't like this. There are a few ways to get it to work; one of the obvious is to manually switch out the keys every time an account switch is made. However, this is clunky and annoying to do, so I needed an alternative. This method uses SSH keys and SSH config, and should work on all modern systems with access to ssh.

## Setting up  SSH keys

If you already have SSH keys for all your accounts, you can skip this step.

To start off, `cd ~/.ssh`. Create the directory if it doesn't exist. 

Then generate the keys:
```bash
$ ssh-keygen -t ed25519 -f ~/.ssh/github_main -C "main.email@example.com"
$ ssh-keygen -t ed25519 -f ~/.ssh/github_secondary -C "secondary.email@example.com"
# Repeat for more
```

Note that the exact type of key isn't really important; if you have a different type of key already, that doesn't affect teh rest of this approach.

Once you've done this, add the right key to the right account. On GitHub, you do this under settings -> keys ([direct link to github.com/settings/keys](https://github.com/settings/keys)). If you're following this article on a different Git Provider, go to the appropriate place to add keys there instead instead. Repeat for other accounts and other keys. Make sure you copy the right key, and make sure you copy the public version (`.pub`). 

## Setting up multi-account support

Once you've added all the keys to your accounts, the next step is config. Still in `~/.ssh`, create a file called `config`, if you don't have one already:

```bash
touch config
```

And open it in your favourite editor.

Adding support for multiple accounts is done with SSH config magic in the config file. The idea is, simply, to use different Hosts for different accounts. If you're familiar with how the config file works, this probably sounds off; if you change the Host, then surely, that breaks SSH?

You'd be correct; however, you're not required to use real hosts in SSH config files. You can name a host whatever you want, but if the Host doesn't correspond to a real URL or IP, you need to define a HostName to point somewhere that does exist. This has many applications, including letting you specify names to wrap IP addresses for, for example, local servers. In this case, we take advantage of this to specify multiple sub-domains of GitHub, all pointing back to the real GitHub:

```
Host github.com
  User git
  IdentityFile ~/.ssh/github_main

Host secondary.github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/github_secondary
```

This allows specific URLs to be used to identify different GitHub accounts. You'll need one Host entry per account. Once this is done, you can access one account by using `github.com` URLs, and the other with `secondary.github.com`. 

## This approach in practice, and verifying the config


Since the hostname now identifies the URL, picking which account to use is reflected in the URL. For verifying if you can connect to GitHub with SSH keys, you can use this command: `ssh git@github.com`. This will give you a message like this:
```
PTY allocation request failed on channel 0
Hi LunarWatcher! You've successfully authenticated, but GitHub does not provide shell access.
Connection to github.com closed.
```

Repeat this command for each of your accounts, If you have a `secondary.github.com`, use `ssh git@secondary.github.com`. If everything is set up correctly, you'll see the same message with a different username for each account you've set up.

As a practical example, let's say you want to clone the repo [for this website](https://github.com/LunarWatcher/lunarwatcher.github.io). If you want to use your:

* Main account: `git clone git@github.com:LunarWatcher/lunarwatcher.github.io`
* Secondary account: `git clone git@secondary.github.com:LunarWatcher/lunarwatcher.github.io`

Note how the domain itself changes from `github.com` to `secondary.github.com` for the secondary account. This works with any number of accounts as well, as long as you remember to switch the domains when using a different account, and add config for each account. This also means that when you copy the link to clone a repo from GitHub, you may have to modify the URL to clone with the right credentials.

## Other notes

There's, strictly speaking, nothing requiring you to even use `github.com` in any part of the hostname. This is my personal preference though, as I prefer hostnames at least partly identifying where the connection goes. It also ensures that if I suddenly don't have my config (or my config, for some reason, breaks, I'm not sending SSH requests to random servers unrelated to GitHub).

You can, technically, use something that isn't a domain either, such as `personal_github` and `work_github` as the hostnames if you prefer - or something completely different. 

