---
title: "Enabling footnotes in Hugo"
tags: ["hugo"]
date: 2023-06-21T23:56:41+02:00
---

I've been unable to find concrete instructions for this, but my [ecosia](//ecosia.org)-fu might be off today. In either case, this is how you set up footnotes for Hugo:

Hugo footnotes aren't actually part of Hugo, but are a feature from, at least, goldmark. Enabling it is surprisingly trivial[^1]:
```yaml
markup:
  goldmark:
    extensions:
      footnote: true
    renderer:
      # Not entirely clear on whether this is required or not, but feel free to play around with it
      unsafe: true
      footnoteAnchorPrefix: ""
      footnoteReturnLinkContents: "^"
```

And for a bit of recursion, the source code for this file:
````markdown
Hugo footnotes aren't actually part of Hugo, but are a feature from, at least, goldmark. Enabling it is surprisingly trivial[^1]:
```yaml
markup:
  goldmark:
    extensions:
      footnote: true
    renderer:
      # Not entirely clear on whether this is required or not, but feel free to play around with it
      unsafe: true
      footnoteAnchorPrefix: ""
      footnoteReturnLinkContents: "^"
```

...

[^1]: Minimal config required
````


[^1]: Minimal config required
