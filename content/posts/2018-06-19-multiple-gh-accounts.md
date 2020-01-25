---
date: "2018-06-19T00:00:00Z"
summary: Short guide on using multiple GitHub accounts on one computer in a way that
  doesn't require manual account changing
tags: ["git"]
title: Multiple GitHub accounts on one computer
---

This method uses SSH keys, and builds around Bash. It works on Windows, but requires a Bash command line (type `bash` into CMD if installed, or use something like Git Bash or Cygwin)

`cd` into `~/.ssh`. Create the directory if it doesn't exist. 

Generate keys:

```bash
$ ssh-keygen -t rsa -b 4096 -f ~/.ssh/github_main -C "main.email@example.com"
$ ssh-keygen -t rsa -b 4096 -f ~/.ssh/github_secondary -C "secondary.email@example.com"
# Repeat for more
```

Still in `~/.ssh/`:

Create `config` if it doesn't exist:

```bash
touch config
```

Edit it:

```bash
start config
```

Add this. Add additional ones for more accounts:

```
Host github.com
  User git
  IdentityFile ~/.ssh/github_main

Host secondary.github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/github_secondary
```

Copy the SSH key:


Option 1: `cat github_main.pub`. Copy what it prints into the console

Option 2: Copy straight to the clipboard

1. OS X: `cat github_main.pub | pbcopy`
2. Linux: `cat github_main.pub | xclip`
3. Windows: `cat github_main.pub | clip`

Add the key to your GitHub account ([direct link to github.com/settings/keys](https://github.com/settings/keys)). Repeat for other accounts and other keys. Make sure you copy the right key, and make sure you copy the public version (`.pub`).

Finally, change remotes where necessary. If you have three accounts and the config looks like this:

```
Host github.com
  User git
  IdentityFile ~/.ssh/github_main

Host secondary.github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/github_secondary
Host tertiary.github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/github_tertiary 
```

That means:

* The main account uses SSH URLs like `git@github.com:LunarWatcher/lunarwatcher.github.io.git`
* The second account uses SSH URLs like `git@secondary.github.com:LunarWatcher/lunarwatcher.github.io.git`
* The third account uses SSH URLs like `git@tertiary.github.com:LunarWatcher/lunarwatcher.github.io.git`

Notice that the second and third don't use `github.com` as the URL, they use `secondary.github.com` and `tertiary.github.com` respectively. The reason this works is because of the config file; The host name makes sure the traffic is actually directed to `github.com` for `secondary.github.com`, but it uses a different SSH key (see the `IdentityFile` value). Same applies for the third one, just with a separate file. 

Therefore, some remotes need changing.

You should only use SSH to keep track of this. If you use HTTPS somewhere, change it to the appropriate version of the remote. The example one used earlier (`git@github.com:LunarWatcher/lunarwatcher.github.io.git`) is the URL to this repo. If you have two accounts, and pull using that exact one, assuming `Host github.com` is defined, that account will be used to pull. If you change to `secondary.github.com` (make sure the rest of the remote stays the same), the second account will be used to pull. Obviously, if you don't change the username and email, the commits will be done in whatever config the global value is set to. Change the local config where necessary using `git config user.email "your.email@example.com"` and the same for the username. Without `--global`, it's set for the repo. 

Anyways, for the remotes. There's no need to remove and recreate them. You can call `git config remote.remotename.url git@github.com:username/reponame.git` to change the URL of the remote. Change `github.com` to the appropriate version if you're using the non-main account.

And for new repos, always use SSH. And, as already mentioned a few times, change the `github.com` part of it if you're using a separate account.

And you should be good to go! You can now use SSH keys to access multiple GitHub accounts on one computer without removing logins.
