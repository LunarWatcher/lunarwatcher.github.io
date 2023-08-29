---
title: "Hugo on GitHub Pages: The modern alternative for deploying non-jekyll pages to GitHub Pages"
date: 2023-08-29T20:25:37+02:00
tags: ["hugo", "github", "github pages"]
---

This is a revision of [an old article of mine]({{<ref path="/posts/2021-07-18-hugo-on-github-pages.md">}}), which relied on using a separate branch, and a GitHub action that pushed the deployable page to it. This is still an option, and it still works. However, there's now a significantly cleaner option that doesn't involve using a branch that's cleaned and force-pushed to.

Thanks to changes to GitHub Actions, it's now possible to push to GitHub Pages from GitHub Actions. This makes any type of non-Jekyll page deployment significantly easier. This guide can consequently be applied to _any_ site generator, as long as it's able to output HTML. 

If you already have an action building a Hugo page, or a page built with your favourite website framework, you can skip straight to [the section on deploying](#deploying)

## The setup

Before you can do anything, you need an action capable of building your page. This section is specifically for Hugo. If you don't use Hugo, you need to make significant changes for it to work.

The setup is fairly trivial:
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
      # This step generates the site. By default, hugo dumps it into the `<root>/public` directory,
      # a fact we'll be taking advantage of in a later step.
      - name: Run hugo
        shell: bash
        run: |
          mkdir public 
          hugo --minify
```

## Deploying
