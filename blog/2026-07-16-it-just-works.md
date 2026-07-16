---
{
    "title": "It just works",
    "date": "2026-07-16T00:56:46+02:00",
    "summary": "Don't you just love it when things just work? A semi-unstructured thing™️ on having lots of fun with stuff I've never done before",
    "type": "blog",
    "taxonomies": {
        "tags": ["personal"]
    }
}
---

Over the last few months, I've picked up a couple projects that I've either started on and procrastinated for ages, or never started because I figured it would be too much effort for too little benefit. There's quite a few projects in the latter category.

I plan to write an extended anti-AI thing (manifesto?) at some point, but I've been actively shedding dependencies that use AI slop. This initially killed this site, because [Hugo (the static site generator) turned to AI slop](https://github.com/gohugoio/hugo/blob/842d8f105256c5656e7895ee61fa5b2dfe90a9e3/AGENTS.md), because of course they did.

After a while of leaving this website as just a text-only repo after trying and failing to migrate to another SSG that also turned out to be AI slop, I decided I would try to write my own. The hard part here was writing the markdown parser, largely because I don't like writing parsers, and I'm not particularly good at it either. In a few weeks of effective work (3 months of calendar time, because I was also doing several other things at the same time), I had a basic site generator going[^1].

I did admittedly avoid writing the templating library, since templating libraries are basically small programming languages, and therefore require a lot more thought and good code than a bare minimum markdown parser, but both the markdown parser and the scaffolding that makes the entire thing actually generate sites was up surprisingly quickly.

In parallel with this, I started working on a socket library[^2], so I could replace asio in my own webserver library[^3]. I have the advantage of primarily working with low-level C++ code, which gives me raw access to operating system APIs whenever I need them, so going lower-level to just rawdog networking doesn't require anything special. I just read the manual, occasionally read some more structured guides or similar instead[^4]. This led me down a tangent where I tried `epoll`, and to my surprise, it just works. Adding SSL support on top of that was trivial, and made my API much cleaner than the clusterfuck asio requires to support SSL.

Again, it just works. Same with the webserver, though that was initially not as low-level. The webserver library was actually spawned because the library I used previously (crow) struggles so much with completely breaking bugs in basic features, and I just got tired of it, and wrote my own. It was initially built on asio, because I wanted to avoid low-level socket stuff, but after it caused memory leaks and other Fun Stuff:tm:, I got rid of it. I have two projects (I believe) that use magpie and runs on my servers. They're not particularly big and the traffic is me and some automation I have set up, but they're incredibly stable servers, and require next to no resources to run. Probably won't scale massively well on account of limited async, but it doesn't really need to - at least not for v1. 

Particularly due to hyperscalers and similar, a lot of standard software has become wildly complicated. To be clear, this is largely out of necessity, since actually maximising performance and stability requires a fair bit more infrastructure. I'm not sure how many lines of code raven is, but it's probably around 2000 _at most_. Something like nginx is around 250000, and that's "just" a reverse proxy.

"It just works" is really just a symptom of how making a working system for at least a few applications is a lot easier than it is - which is the main point with this mostly unplanned blog post. Making something that works and is solid enough to be built upon is pretty easy. It's also a lot of fun learning the basics that ultimately power like every single system.

In parallel with all of the above, I've also been working on and off on a UI library for a couple years (mostly off). One of the explicit goals I had was that I didn't want to do layouts myself; I want to give it approximate sizes and just let the library deal with the resizing. So I implemented the flexbox algorithm based on the actual spec used in HTML. The code is awful, and I've had to work through loads of bugs to add stuff like scrolling, but it works. I did admittedly opt out of the graphics bit - I have tried to write stuff with raw OpenGL before, and the jump from rendering triangles to rendering random text with TTF fonts is _significant_. The library is built on allegro5 to avoid having to implement all those bits too. Plus, I get to learn a fair bit about something vaguely shaped like the layout systems that power the whole internet.

My main takeaway from the past few months of doing this is that there's a lot of projects I haven't really considered that are a lot more doable in practice than in theory when not worrying too much about the large-scale applications for stuff. If I ever come to the point where I need to support more scale or whatever, I do now have the theoretical foundation to build on, but in all likelihood, it will never come up. And I'm fine with that. These are the projects I build for fun anyway, largely with the intent of being useful _to me_ - which I very much have accomplished.

[^1]: [https://codeberg.org/LunarWatcher/violet](https://codeberg.org/LunarWatcher/violet)
[^2]: [https://codeberg.org/LunarWatcher/raven](https://codeberg.org/LunarWatcher/raven)
[^3]: [https://codeberg.org/LunarWatcher/magpie](https://codeberg.org/LunarWatcher/magpie)
[^4]: I wrote this footnote prepared to link to a series of blog posts I used. Unfortunately, the domain is no longer owned by the same person (currently unowned and on auction), and archive.org does not have it either. [This list](https://web.archive.org/web/20241218134045/http://cjdevman.com/) showing its mere existence is the closest I'll get. RIP though, that series was really good and to the point.
