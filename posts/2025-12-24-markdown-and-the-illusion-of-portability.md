---
date: 2025-12-24T15:13:38+01:00
---

# Markdown and the illusion of portability

This is the first post I'm writing after scrapping the web component of this "web"site (now just a repo with some files no one is going to read), and not one, but two painful migration attempts to other static site generators before abandoning the push outright. 

After [hugo](https://github.com/gohugoio/hugo/) turned to AI slop, I first tried to migrate to [Zola](https://github.com/getzola/zola), which is about to contain AI slop once tera v2 stabilises. I then tried [cobalt.rs](https://github.com/cobalt-org/cobalt.rs). It doesn't have AI slop as far as I can tell, but it _does_ involve more breaking of my setup, and after successfully pushing through with zola only to find breaking tradeoffs and AI slop I didn't notice in my initial sweep, I could not be bothered. Cobalt.rs does look like the most promising migration target, but it's just far too much effort.

As you might expect when switching static site generators, all the templates were invalid, and required a rewrite. This is due to different templating engines, and is something I expected to be a pain ahead of time. This was true with both zola and cobalt. However, neither cobalt nor zola support the same kind of frontmatter that hugo did. Aside supporting fewer fields, cobalt has different names on certain things than both hugo and zola. 

Frontmatter is, strictly speaking, not standard markdown, nor are they a proper standard. The most common convention is YAML-based frontmatter, but zola uses TOML-based frontmatter. Even if frontmatter was a proper standard, that only tells you the standard syntax, and not the standard data it supports. Over time, I've slowly been adding more features to the templates I used, and consequently, more non-standard data stored in the frontmatter. In hugo, this was intended. In zola, a separate `[extra]` section was used. I abandoned my attempt to migrate to cobalt before I found out what they did. 

Hugo also supported templates directly in the markdown, which meant parts of the markdown wasn't portable either. I initially did this because I wanted a way to properly link to the markdown files, and have it translate to the real links when the site was built. Worked great until hugo turned to AI slop and I had to rip it out, and was stuck with some files with non-standard markdown. 

Don't get me wrong, I love markdown, and I love the principle behind static site generators; but just because the content itself is easily extractable doesn't mean extracting it is effortless, much less turning it around and using it in a new static site generator. You don't have to look far to find claims of the contrary. Systems using markdown because it means it's portable is semi-regularly cited as a benefit in various first- and third party accounts regardless of the category of tool. You can find it for static site generators, text editors or note tools, and whatever else.

The core markdown absolutely is portable, but depending on what system you put the markdown in, you might get a lot more non-standard features than you bargained for. Obsidian, my main tool for notes at the moment, also uses markdown, but by default, its links are wikilinks, i.e. the kind of links used in [wikitext](https://en.wikipedia.org/wiki/Help:Wikitext). This isn't portable markdown, and if I switch to something that doesn't support wikitext, I'll need to rewrite it. 

Just because the core text is portable doesn't mean all markdown documents are portable. If the system it's contained in supports non-standard stuff, it isn't really fully portable and ready to plug directly into another system.
