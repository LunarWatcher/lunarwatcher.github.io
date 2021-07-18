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
2. Folder freedom: if I ever add a docs folder to the source repo, this won't affect the deployment. `public/` is admittedly locked either way, but I can rename it if I want to. The only two folder options for pages are the root directory and the docs directory.
3. GitHub actions can actually push a fully clean version of the site without interfering. No manual work needed when a file is removed.
4. The HTML isn't pushed or pulled, meaning a slight reduction in upload/download
5. ... the various generated files not being pushed also means they don't show up in your activity or language stats. I've had my recent language stats severely scewed by making a tiny markdown change to my site.

Of course, these are mostly subjective arguments and aren't meant to convince you. You either like it, or you don't - and possibly for different reasons. The above are mine.

## Setup

My setup is fairly simple: the master branch contains the sources, and the deployment branch contains the website. Note that I'm executing a rename right after posting this blog entry, because I can.

There used to be a restriction that only allowed `<username>.github.io` pages to have their sources on a branch named `master`, or possibly `main`. I haven't looked deep into that, but the gist of it when I set up my site was that I couldn't have my sources on the master branch, and a custom-named branch for the deployment.

Now that this is no longer the case, you can name your branches whatever you want, but note that this means the deployment action needs to be changed accordingly. We'll get back to this later.

I'm not going to include a Hugo crash course in this post. [Hugo already has a guide for getting started](https://gohugo.io/getting-started/quick-start/), and it covers it better than I can be bothered to do.

There's one thing that's required, however:

Your `.gitignore` *has* to contain `public/`, to make sure you don't conflict with the action. If you need the public folder for something else, make hugo output a different directory, but ignore _that_ directory. Changes to `Deploy.yaml` will be required if you use a different directory from `public/` for the deployment as well.

It won't cause a conflict on GH Action's side, but it will make you push redundant HTML.

## The actual deployment

My old approach used a shell file I named `deploy.sh`. All it did was build, cd into `public`, commit and push that, cd back up, and commit the main repo (and push that). The shell file took a commit message that was reused in both commits.

The massive downside to this was that I took ownership of the commit, which heavily scews my language statistics towards HTML and CSS when I haven't written in either. The pure amount of changes made to a static site when a tiny change is made is insane, by the way.

Anyway, the up to date action can be found [in the repo for this site](https://github.com/LunarWatcher/lunarwatcher.github.io/blob/master/.github/workflows/Deploy.yaml), but here it is at the time of writing:

```yaml
name: Deploy pages
on:
  push:
    branches: [ master ]
  workflow_dispatch:

jobs:
  hugo:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
        with:
          submodules: true
      - uses: actions/checkout@v2
        with:
          repository: LunarWatcher/LunarWatcher.github.io
          ref: deployment
          path: public
      - uses: actions/setup-python@v2
      - name: Setup Hugo
        uses: peaceiris/actions-hugo@v2
        with:
          hugo-version: 'latest'
          extended: true
      - name: Run hugo and commit
        shell: bash
        run: |
          pwd
          cd public && git rm -rf . && cd ..
          git config --global user.name github-actions[bot]
          git config --global user.email 41898282+github-actions[bot]@users.noreply.github.com
          hugo --minify
          cd public && git add -A && git commit -m "Deploy changes for ${GITHUB_SHA}" && git push origin deployment
```

Note the second `actions/checkout@v2`: this is done to clone the deployment branch. Make sure you replace the repo reference with your own reference and the correct branch, if you don't use `master` and `deployment`. Again, there's a number of naming schemes, use whatever works for you. A side-effect of using actions/checkout is that it sets up the GitHub token automagically, meaning you don't have to figure out how that works. (I mean, I have no idea how to push with a custom token. This is definitely the easiest option)

`git rm -rf .` clears out the directory by removing all files tracked by git from the disk. In a normal repo, this will leave untracked files, but because nothing is `.gitignore`d in the deployment repo, this isn't a concern. Everything will be removed except the `.git` folder, which is how we avoid conflicts and force pushing.

The rest of the action is straight-forward if you've ever messed around with it before. When a push is registered on the branch of your choice, the action is run. It can also be triggered manually, though there's rarely a reason to do so.

The action is run on the latest version of Ubuntu, because Linux is infinitely easier to use for these types of things. The username is meant to match the GitHub Actions bot to have it take ownership of the commits instead of you. This is again to make sure language stats and activity stats aren't interfered with, though that's just me. You _can_ take ownership of the commits if you want, by changing the username and email appropriately. Signing these commits is tricky, however, and may not be doable.

My configuration relies on the latest version of hugo, as well as the extended version of hugo. You can set a specific version or not use the extended version if you prefer, though this is [outlined in the action](https://github.com/peaceiris/actions-hugo) written by peaceiris.

---

With the action pushed, new updates to your primary branch are registered, causing Hugo to run and Actions to deploy your page. This is as close as it gets to proper Jekyll, where GitHub itself builds and deploys for you.

Finally, if you do decide to use the action with the `docs` folder on the same branch that the action is set to detect, you **HAVE** to add `[skip ci]` to the commit message. Otherwise, the commit you make is picked up by the action that then rebuilds right after rebuilding. It shouldn't cause an infinite loop, however, but it's an unnecessary use of free CI resources.
