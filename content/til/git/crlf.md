---
title: "Windows is pain: getting rid of CRLF"
tags: ["git", "windows"]
date: 2022-12-23T17:24:56+01:00
---

I can never seem to get autocrlf to work properly on Windows. It isn't a problem on Linux, but it's always a problem on Windows. I've had to revisit this several times, because Git on Windows suddenly decides to flood my repo with CRLF without me notificing. I do have a select few words to whoever thought having CRLF was a good idea, but let's save that rant for another time.

So note to future me, here's how you overkill ensure new systems work properly:

```
git config --global core.autocrlf input
```

`false` is evil, and pollutes CRLF everywhere. `true` does excessive normalisation, but ensures everything is CRLF locally (which probably isn't a big deal; it's worse on Linux. C++ just reads the \n as newline, and preserves the \r, resulting in a lot of weird parsing shit), but that it still commits LF rather than the garbage CRLF line endings.

```
git config --global core.eol lf
```

is the nuclear option, but probably has to be combined with another autocrlf option. According to [this Stack Overflow answer](https://stackoverflow.com/a/9977954/6296561), that option is indeed `core.autocrlf input`, with `core.eol lf`, and forces lf line endings on checkout. Assuming your editor doesn't forcibly convert LF to CRLF, this ensures only LF is used.

## `autocrlf=input` in practice

This just contains examples of how Git acts with `autocrlf=input`. No new information is introduced here.

```bash
[Clean checkout]

Olivia@Ari MINGW64 ~/programming/test (master)
$ file README.md
README.md: ASCII text

[opened in Vim, set ff=dos, save and quit]

Olivia@Ari MINGW64 ~/programming/test (master)
$ file README.md
README.md: ASCII text, with CRLF line terminators

Olivia@Ari MINGW64 ~/programming/test (master)
$ git add -A
warning: CRLF will be replaced by LF in README.md.
The file will have its original line endings in your working directory
g
Olivia@Ari MINGW64 ~/programming/test (master)
$ git status
On branch master
Your branch is up to date with 'origin/master'.

nothing to commit, working tree clean
```

The files are all successfully checked out as LF, as demonstrated by the first file call. Curiously, changing the filetype does result in it appearing in the status briefly:
```bash
[LICENSE modified from the checked-out LF to CRLF]

Olivia@Ari MINGW64 ~/programming/test (master)
$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   LICENSE

no changes added to commit (use "git add" and/or "git commit -a")
```

but `git add -A`, the warning about conversions appear, and poof, it's gone.

This does still mean warnings appear, but these can be blatantly ignored. Them being there means it's doing its job.

Do note that I'm not affected by editor pollution; Vim preserves input, so if it gets LF, it keeps LF and writes LF unless told otherwise. The Git plugin I have doesn't force any options down my throat, but I mainly use Git from the terminal. Certain Git plugins in certain editors may introduce unwanted options that ignore these options; consult the manual for your editor if you're struggling.
