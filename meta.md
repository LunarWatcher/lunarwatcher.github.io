---
{
    "title": "Meta"
}
---

> Last updated: 2026-07-26T23:49:18+02:00

This website was generated with [violet](https://codeberg.org/LunarWatcher/violet), a static site generator I made after hugo fell to AI slop.

Some of the extended parts of this page were inspired by [this blog post](https://home.hedy.dev/posts/meta-pages/), though it was initially just intended to include the stats I added in violet 0.7.0, so I can flex or whatever :p

## Stats

If you don't have JavaScript enabled, this section will not load properly. You can see all the raw numbers [in the data file](/_violet-meta.json) used to power this section.

<div class="flex-horizontal">
<div>

### Build

This site was generated with Violet <span id="meta-violet-version"></span> in <span id="meta-violet-gen-time"></span>ms. It was last generated at <span id="meta-violet-generated-at"></span>

</div>
<div>

### Content

* Total number of unrendered files[^1]: <span id="meta-violet-in-files"></span>
* Total number of pages rendered with templates: <span id="meta-violet-in-pages"></span>
  * These pages result in <span id="meta-violet-out-pages"></span> pages after generation.

</div></div>

## Other stuff about this site

### Tech

This site has had, at least that I can remember, three (four) major (technical) iterations:

* Jekyll: 2018-dec. 2019
* Hugo: 2019-dec. 2025
* (Nothing: dec. 2025-jun. 2026)
* Violet: jun. 2026 (current)

Looking back on my commit history to write this list, I did notice that both the jekyll and hugo changes happened in september, a few days before christmas. I guess december has ended up being my webdev month for a while.

The migration to hugo in 2019 happened because it was just easier to work with than jekyll, because ruby as an ecosystem is _awful_. The switch away from hugo came because, as mentioned earlier, hugo turned to AI slop. It took me a few months to roll my own, though most of that time was in the "I can't be bothered doing this so I'll just keep a repo with notes instead" phase.

(Also, holy shit, has it really been _8 years_ already?)

### Philosophy

Violet has been an interesting challenge. Though the idea initially was to get the site back online, the motivation to start violet came after I watched a video that wasn't good enough to link to, but that talked about the indieweb.

This led me down a few rabbit holes, a lot of 88x31 links, and a fair few webrings, and those fuck knows how many sites (hundreds at least) helped change the philosophy of the site.

The shift to violet mostly aligns with the boundry for what this site should be, a problem I have struggled with for years. In parallel to discovering the indieweb is keeping the good parts of the web alive, [Stack Overflow turning to shit changed how I deal with information, notes, and information sharing](/blog/2026-03-01-information-post-stack-overflow.md). Especially in the post-AI era, human sources of information are both more valuable and more scarce. Fuck AI - with a cactus.

More importantly though, it means that the site changed to be less formal and more unhinged, while also containing more potentially useful or interesting information. Learning is fun and so are 88x31 rabbitholes. I'm still working on ideas for easter eggs and similar. The only one that currently exists is somewhere on the front page (not saying where; spoilers :3), but having fun in more places sounds, well, fun.

### Design

The current design of the site is mostly just the same design I've had for years, but with new colours and a drastically improved navbar. I modelled it after older webdesign standards, but without going so old that it looks like it's from the early 2000s. I got my first computer when I was like 9 or 10 I think (2010 or 2011 - maybe sooner, I do not remember), but I never got into the small web. I was born too late for the golden age of the internet, and just in time for the corporatization of the internet. It's not really feasible to design for something I have never actually interacted with.

#### Colours and fonts

Some pure design-semantic things have changed though. One notable difference from earlier is that [I don't set any fonts](/notes/html/fonts.md), because respecting user choices is good, and fonts are a very notable instance of a user preference that should be respected. If you don't like the font, go to your browser's settings and change the default to whatever you like. If you use Firefox, you can also change a setting that [disables websites' ability to set their own shit fonts](/til/firefox/fonts.html).

The previous version used a pink-on-black theme. This one leans a lot more heavily towards pink and purple. I would still like to get in more colour in a few places, but I'm not sure how to do this without just making everything be coloured. I like pink, but reading everything on a pink background gets annoying.

#### On designing for myself

Most of the time I've designed websites, it has been fairly standard. Not necessarily in terms of the CSS, but the *gestures broadly* everything just feels standard. Having been surrounded by the corporate web for so long means that it feels like there's just certain standards for websites. The indieweb helped me break away from that again.

After redesigning in 2026, I've also tried to force in more things that are just *me*. I mentioned easter eggs earlier, and that is an example of what I mean, but also the general style of content. I have been leaning more into small web-inspired stuff, and writing slightly more unhinged stuff than usual just for fun. I do still lack more pages that are written or made just for the sake of being fun, but that'll come in time.

I don't know how hard the google[^2] algorithm punishes me for having "silly" in the site name, but I also don't care anymore. I want a mix between a personal site and a useful technical site, but holy fuck is it hard to fight like 16+ years of being influenced by the corporate web. There are also several things on the list of more personal stuff that I am excluding for now, but might add if I start embracing the websites-as-socializing-style of content. I know lots of websites have an update log for an instance, but I currently discard it in favour of nothing (and obviously the git commit history, but whatever).

I also have a few more fun issues, like being hyper-aware of how so many sites contain tracking. 32bitcafe has an article about [interacting on the indieweb](https://32bit.cafe/interactingontheweb/) where they link to four comment boxes. All four of them use some form of third party analytics, mostly google, which means they can't really be trusted. Most of the interactivity I'd like ends up being just sneaky analytics, and fuck that. This would be easier if I self-hosted or used some other non-static webhost with a database or whatever, but I don't have access to a non-static webhost, and I do not self-host public services. The things I self-host are either just intended for me, or a very specific select few people, which won't work for general interactivity.

Interactivity would be nice, but it isn't a dealbreaker for me. It means that interaction has to be done outside the website (like in issues or on Discord[^3]), but at least means that there isn't trackers being forcibly embedded on the website, and that there won't be various supply chain risks if I look away for like 3 months or whatever.

Writing this section has re-surfaced a lot of thoughts, but the point is that learning how to design something that actually feels personal is really fucking hard, and for completely different reasons than I thought back when I initially designed this website, and thought "personal design" just implied being designed in a way I liked. To be fair, it does, but in much broader ways than I thought at the time. It's really hard to communicate what exactly I mean because words hard, but like, the indieweb has a lot of sites with a lot of personality in the design (and in the content, which also is a whole thing), and adding that is just really fucking hard. For now, I'm settling on breaking away from things I consider to be standard, and adding more personality later. I also imagine I'll need more image assets to do that properly, which means I have a lot of drawing work to do on top of webdesign. that's still a while out though.

## Indieweb

Most of the design section has already touched on this, but this site has been designed at least partly in the spirit of the indieweb. I'm working on the whole spreading links bit (the outlinks page was added yesterday, at the time I write this), but there's fortunately many flavours to indiewebbing, so there's at least not many ways to do it wrong :p

### Webrings

See [webrings](/index.md#webrings)

[^1]: An unrendered file is a file that hasn't been processed by the templating system, i.e. a file that was copied directly to the output folder.
[^2]: Pro tip: though it is paid, [Kagi](https://kagi.com) (a different search engine) is doing a lot of good work on, among other things, the small web. It has to be mentioned that they endorse AI slop machines, but they have toggles for disabling all of it, and the actual search algorithm isn't designed to force maximum slop. Their philosophy around search arguably makes kagi a lesser evil.

  I also don't know how much their algorithm punishes me for having "silly" in the site name. I'm just bringing them up because switching away from google services is a great way to protest their bullshit and anti-human approach to, well, everything they touch, AI slop machines or otherwise. In non-search engine products, [Proton](https://proton.me) is solid. I use protonmail (and protonvpn and proton pass), and I'm really happy with them.
[^3]: I do appreciate the irony in saying "these comment boxes have analytics" only to then follow up with Discord as an alternative for interaction. Discord is a hellscape in terms of surveillance, especially now that it has ties to some really shady companies, but there are just really few options right now. I do have high hopes for [Fluxer](https://fluxer.app/), though it's still lacking E2EE AFAIK.

  Matrix can go fuck itself.

<script src="{{ site.prefix }}/assets/js/meta.js"></script>
