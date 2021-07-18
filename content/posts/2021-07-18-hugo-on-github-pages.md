---
title: "Hugo on GitHub Pages"
date: 2021-07-18T14:44:30+02:00
tags: ["hugo", "github", "github pages"]
---

I used to base this site on a blog entry on another blog. The gist of it was, there's a source branch while the master branch contains the deployed page. 

A part of the reason I did this in the first place was because I had to. I _had_ to deploy on a branch and I had no choice but to use the root directory. This seems to have changed since, meaning the `docs/` folder on any (including the primary) branch can be used.

I noticed this ironically while writing this post, but I decided against switching to the `docs/` folder on the primary source branch because I don't wanna have to pull after I commit. It also defeats the purpose of GitHub actions in this context, since local `hugo serve` while testing actually writes all the files. Or at least can write the files.

If GH actions is used with an line `docs/` folder, it's easy to get (auto-solvable) conflicts that require a merge commit. I'm not a fan of this because it causes a messy branch structure, so I'd like to reduce the probability of that happening. Of course, now that the docs/ folder is a viable option, there's nothing preventing this easy approach anymore. If you still like keeping one source branch and one deployment branch, this article is for you.

Note that the GH Action used here can be adapted to use the `docs/` folder, but because it requires a pull, I do not recommend it.

## Why use a branch at all?

Aside conflicts, I have a few other reasons:

1. Clean commits. The source repo always contains commits detailing the source operation. Because the HTML is minified, it's a distraction to see these in the same commit that makes the source changes, or in a commit on the same branch.
2. Folder freedom: if I ever add a docs folder to the source repo, this won't affect the deployment.
3. GitHub actions can actually push a fully clean version of the site without interfering. No manual work needed when a file is removed.
4. The HTML isn't pushed or pulled, meaning a slight reduction in upload/download
5. ... the various generated files not being pushed also means they don't show up in your activity or language stats. I've had my recent language stats severely scewed by making a tiny markdown change to my site.

Of course, these are mostly subjective arguments and aren't meant to convince you. You either like it, or you don't - and possibly for different reasons. The above are mine.

## The actual deployment
