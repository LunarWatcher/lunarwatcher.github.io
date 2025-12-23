---
title: "Hugo on GitHub Pages with GitHub Actions"
ingress: "The modern alternative for deploying non-jekyll pages to GitHub Pages"
date: 2023-08-29T20:25:37+02:00
tags: ["hugo", "github", "github-pages"]
slug: "hugo-on-github-pages-the-modern-alternative-for-deploying-non-jekyll-pages-to-github-pages"
---

> [!caution]
>
> As of late 2025, Hugo has [started accepting AI slop contributions](https://github.com/LunarWatcher/dotfiles/blob/master/docs/AI%20slop%20victims.md#hugo-gohugo). I'm discontinuing my use of Hugo as soon as I can code it out of this website, and cannot in good faith recommend it. I strongly recommend finding a static site generator that doesn't build on AI slop. At the time of writing, I plan to switch to [Zola](https://github.com/getzola/zola). [Jekyll](https://github.com/jekyll/jekyll) (built directly into GitHub) is also clear at the time of writing. This may change, so double-check for AI slop before you pick one.

---

This is a revision of [an old article of mine]({{<ref path="/posts/2021-07-18-hugo-on-github-pages.md">}}), which relied on using a separate branch, and a GitHub action that pushed the deployable page to it. This is still an option, and it still works. However, there's now a significantly cleaner option that doesn't involve using a branch that's cleaned and force-pushed to.

Thanks to changes to GitHub Actions, it's now possible to push to GitHub Pages from GitHub Actions. This makes any type of non-Jekyll page deployment significantly easier. This guide can consequently be applied to _any_ site generator, as long as it's able to output HTML. 

If you already have an action building a Hugo page, or a page built with your favourite website framework, you can skip straight to [the section on deploying](#deploying).

As usual, this is used to power this website, and the current live version can be found [here](https://github.com/LunarWatcher/lunarwatcher.github.io/blob/master/.github/workflows/Deploy.yaml) ([permalink to the version at the time of writing](https://github.com/LunarWatcher/lunarwatcher.github.io/blob/c7f1876687828e74e9a8f8705dc1e4968688690e/.github/workflows/Deploy.yaml)). 

## The setup

Before you can do anything, you need an action capable of building your page. This section is specifically for Hugo. If you don't use Hugo, you need to make applicable changes for it to work.

The setup is fairly trivial:
```yaml
name: Deploy pages
on:
  push:
    # This needs to be replaced with the branch you want to deploy from if you use a non-standard name
    branches: [ master ]
  workflow_dispatch:

jobs:
  hugo:
    runs-on: ubuntu-latest
    steps:
      # Required for checking out the repo
      - uses: actions/checkout@v2
        with:
          submodules: true
      # Required for setting up hugo; if you use a different site generator, this needs to be changed.
      - name: Setup Hugo
        uses: peaceiris/actions-hugo@v2
        with:
          hugo-version: 'latest'
          extended: true
      # This step generates the site. By default, hugo dumps it into the `<working directory>/public` directory,
      # a fact we'll be taking advantage of in a later step.
      - name: Run hugo
        shell: bash
        run: |
          mkdir public 
          hugo --minify
```

## Deploying

Deploying is deceptively easy compared to the previous version.

First, go to your repo, then settings -> pages. Under "Build and deployment", pick GitHub Actions as the source.

Then, there's three changes that need to be made to the Actions workflow.

First, at the root level, the following needs to be added:

```yaml
on:
  # Omitted, but included for positional context.

permissions:
  contents: read
  pages: write
  id-token: write

jobs:
  # Omitted, also included for positional context
```

This is required, as GitHub Actions doesn't assign the default action token with write permissions [unless explicitly defined.](https://docs.github.com/en/actions/using-jobs/assigning-permissions-to-jobs#defining-access-for-the-github_token-scopes)

When this is added, the next step is uploading an artefact, and deploying to GitHub Pages:

```yaml
      - name: Upload artifact
        uses: actions/upload-pages-artifact@v2
        with:
          # As previously mentioned, Hugo dumps the generated page into the `public` directory.
          # The public directory is therefore uploaded as an artefact, which is required for the
          # deployment action, for reasons I'm honestly not entirely clear on (read: I didn't bother checking)
          path: 'public/'
      - name: Deploy to GitHub Pages
        # This step deploys the artefact uploaded in the previous step to GH Pages. The artefact
        # should therefore represent the root directory for your page.
        id: deployment
        uses: actions/deploy-pages@v2
```

And that's all the required config. No committing, no (force) pushing to a separate branch. It just uploads it, and GitHub takes care of the rest.

### What about other page systems?

As long as it outputs HTML, or another format browsers can read, upload the directory containing the generated page output as an artefact using the `upload-pages-artefact` action, and then use the deploy-pages action. Figuring out the steps required to build the page is left as an exercise to the reader, as I'm not going to cover other page generators here. GitHub still takes care of the rest, and leaves you with a functioning page hosted by GitHub.
