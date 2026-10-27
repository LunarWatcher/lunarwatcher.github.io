---
{
    "title": "Half a year of violet",
    "date": "2026-10-27T00:27:09+01:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["violet-ssg", "cpp", "silly-girl-doing-silly-things"]
    },
    "summary": "The SSG I hacked together is unironically not entirely trash??"
}
---

Half a year is technically inaccurate; I only ported my sites in june, though development did start in march, which is nearly 7 months and not 6, but let's not be too pedantic :P

That and I forgor last month.

Anyway, [violet](https://codeberg.org/LunarWatcher/violet) is approximately half a year old, and I am very happy with how things have gone so far. To my knowledge, it's in use by 4 people who aren't me, most of whom have started using it in the last 20 *days*.

I've found violet on at least 2 different list sites that list anti-AI projects, which is fun. They seem to kinda build based on each other though, so I imagine one copied the other. There's also a few posts on mastodon about violet, also in the last ~20 days. _And_ one of my TILs on this here violet-based website unfortunately made it to hackernews and got regurgitated into oblivion by all the slop machines within the last 20 days (11th place on 2026-10-12). Thanks, hackernews. I've found ~120-240 regurgigations. It's a bit hard to count properly now that google has decided not to do its one job by not indexing the internet anymore, but there's a _lot_ of people with slop machine "summarizers" pointed at hackernews.

I am positively surprised by the non-slop responses (read: hackernews) though. Actually having people use violet is fun :3 I do have a lot of open-source repos, but most of them don't end up being used. I believe I have only had like 3 or 4 repos that see any form of documentable use, one of which was a vim plugin that's now archived.

## TL;DR: on violet

Violet is a static site generator. I wrote it because there are basically no SSGs with strict anti-AI guarantees that are also in ecosystems that aren't *gestures broadly* utter shit because of dependency hellscapes. Violet was therefore written from scratch in my language of choice with a lot of internal decisions meant to absolutely minimize the number of dependencies. You are now mostly caught up.

## Technical stuff

A few days prior to posting this, I did one of the biggest changes I expect to ever have to do with violet: I forked [inja](https://github.com/pantor/inja), which is currently falling to AI slop (because of course it is), and did a bunch of rewrites to it.

[Iris](https://codeberg.org/LunarWatcher/iris), the fork of inja, has already had its entire expression parser mostly rewritten. It no longer depends on nlohmann/json (also AI slop now D: ), and now directly parses the expressions. This means that it supports functions and variables in objects, which has annoyed me for around 6 months. Mostly the variables anyway.

I have found several other missing parts of the language that I plan to implement in the coming months (see future tense section), but that's foreshadowing. If you consider saying it directly foreshadowing. The most annoying part about the migration was the loss of the test suite The files have a copyright header that doesn't mention any open-source licenses. I am not a lawyer, but I interpret that as enough ambiguity that I just didn't want to touch it.

The entire thing got discarded. The benefit with this is that I could shed the two separate test frameworks (one of which appears to be a discontinued benchmark framework) and replace it with catch2, which I use for basically all my projects, and do this without much of a rewriting effort. The disadvantage is that I've probably lost some obscure test case that checks some obscure bug. But I've fixed several in the parser, so I think we're well past those anyway.

The rewritten test suite does 169 (nice) assertions over 24 test cases, mostly targeting the parts that I have changed.

---

Most of the QoL improvements to violet have been in the last ~20 days, mostly because I've deprioritized QoL while it was just me and one other person using it. Error handling has been getting some significant upgrades, though mostly for markdown parsing. Template errors are still a bit away, because iris doesn't expose enough information to do proper contextual error highlighting.

The markdown errors now actually show the context of the error directly in the terminal. It's not complicated code, but it's really cool that I'm just able to do that.

The changes to iris that allowed expressions in objects also fixed a nasty series of errors where invalid literals caused dogshit errors. I don't think I have handled all the error paths there properly, but it is better than it was before I started.

### Writing a generic container

The big complicated part with the iris changes were writing a generic container.

Because nlohmann/json was dropped outright, a type was needed to replace `nlohmann::json`, which gave us `iris::DataObject`. There's a lot of quirks with this type, notably in its inability to handle object initialization without explicitly using the `iris::Object` type (an alias for a specific `std::unordered_map` specialization), and this is where thet loss of the tests was the most annoying.

Reimplementing a better object than `nlohmann::json` without breaking the language at the same time is difficult without a test suite that validates intended behaviour. I did therefore have to write a few more general tests, as well as some tests that were written alongside some of the more destructive parts of the migration. There were things that were torn out entirely and then replaced later, because it was a big change. 

### Dogfooding :3

Pretty much all my open-source projects are meant to be things I do use, and violet isn't an exception to that. I exclusively do this because I broadly don't care about money from open-source, so I prioritize my interests. It also makes it much easier to develop, because I'm both a developer and a user of the system, and it makes it easier to test because I run into bugs naturally.

In addition to iris' new test suite, and the 444 assertions in 44 test cases[^1] in violet, I have both doc sites using the default theme and my own website (this here website) that I can run tests on. This only found one bug, but that's one bug that didn't have test cases in iris.

That bug came from one of the aforementioned behavioural breaking changes in the generic container. `exists` in inja used JSON pointers, which wasn't migrated to DataPointers because of some intermediate steps.

But honestly, for a rewrite that big in a codebase I just jumped into, not that bad. I am happy with this :3

<p><sub>Then again, poking my paw into the core of a system I don't have experience with to get experience and make actually good changes to it is currently what I do for a living.</sub></p>

### Misc cool things that I like

I specifically have two things I really like. 

The first is how RSS/ATOM feeds are handled. They're templated, but they're not auto-generated. A properly defined base template can allow the implementations to just be frontmatter with extra non-standard data, but there has to be a `feed.atom` somewhere to represent a specific feed. This solves one major problem I had with hugo, which was it putting RSS feeds in fuck knows where, which means that when I go reference it, I cannot for the life of me find it.

I have spent far more time than I would've liked trying to debug feeds in hugo, and now, I don't have to. This blog has four `.atom` files, and four feeds. The file location in the source code is identical to where it goes in the render. I *love* how simple that makes stuff. It does massively complicate taxonomy implementations, but let's not talk about that right now :p

The other is `.in` files. Lots of SSGs support rendering non-standard files, but violet requires the extra `.in` extension to support non-standard, non-resource files. This mostly saves having to parse files and avoids needing to care about whether a file is binary or not. You opt in in the filesystem with an extension. The [violet webring](https://lunarwatcher.codeberg.page/violet-webring) takes advantage of this on [the `_redirects` file](https://codeberg.org/LunarWatcher/violet-webring/src/branch/master/_redirects.in) to allow it to be auto-generated from a `.json` file.

## Technical stuff but in the future tense

I'm omitting a fair few smaller things here, as well as some things that I don't know if I'll have the chance to get to.

I have some markdown additions I'd like to do, which is not hard in terms of code, but harder in terms of concepts. I also still need to implement taxonomy handling, but that is difficult.

Taxonomy handling is hard because taxonomies as a whole rely on being a bit more generic than I'd like violet to be. Taxonomies and similar are why other SSGs have lookup tables that require a decoding table next to it to understand what the fuck it's actually doing. Explicit behaviour here is an interesting issue, because there's lots of different taxonomies. Some, like tags, are more global, while series are one-off. Violet also doesn't require any specific types to allow for flexibility, but this means that the list pages for the taxonomies are a whole can of worms. 

Something Smart&trade; is required to solve this particular problem, and I have not had the big smart moment yet. I will get to it at some point, I just don't have a timeline for it right now.

That said, in terms of core features, a lot is already in place at this point. It's fully possible to write decent blogs and doc sites using it, which is a lot further than I thought I'd get a few of the times I've thought about writing an SSG and not gone through with it.

### Error handling

Error handling is certainly the big one for QoL. Template error handling is the obvious one, but this requires further changes to iris.

Currently, iris exceptions don't actually expose which file an exception happened in. Violet can only tell the user what top-level markdown file was being rendered once the error happened, but due to `include` and `extends` statements, violet cannot see what file actually caused the exception. I don't know if I want to implement higher-level errors in iris proper, either by default or an optional module, or leave that as application logic. But in either case, exposing which file the exception happened in is required to enable anything on either side of the fence. 

### Packaging

C++23 is still fairly bleeding edge, which means that it currently excludes some of the LTS distros. Violet doesn't compile on mint for example (I use arch btw, but I still have mint on my craptop that I use like once a quarter at most), which is an ubuntu 24.04 derivative IIRC.

Violet won't run on these distros either way, but I can at least make it slightly easier to get. Binary distributions are on the list, but I don't know where to start. Non-binary distribution was solved on the same day as this post was made with a curlable `install.sh` script and a `PKGBUILD` for arch that I can't distribute on AUR because [AUR is having a moment](https://lists.archlinux.org/archives/list/aur-general@lists.archlinux.org/thread/L7FYPMAMJOWCMXCCPHUFVQDJQT7TZX67/). 

Credit where credit is due, `PKGBUILD` is one of the better packaging formats I've used. Compared to making a `.deb`, much less distributing it on a PPA, `PKGBUILD` is a "hello world" program. I imagine the AUR distribution would've been trivial if I could make an account, but we'll have to wait for AUR to unlock to see.

Binary distributions are trickier, because distributing it via codeberg is difficult. Storage limit and limited compute availability means it'd be better to distribute it via other platforms, likely closer to package managers and similar, but package managers are a hellscape.

### URI and path parsing (ugh)

URI and path handling is fairly primitive right now. It works, but it has lots of problems and possibly path traversal as well. It's very low risk since it's all on static files that require very specific inputs in the static files, but I'd like to get those closed up.

Another related thing I'd like to do is handle absolute paths better. I want an `abs()` function (probably named better to avoid confusion with the mathematical `abs()` function) that does what manually inserting `{{ site.prefix }}` currently does. Lots of internal URLs should probably also be prefixed by default rather than requiring it be specified. I have run into bugs by not specifying it when I should've before.

Anyway, the URI and path parsing bits suck to do because URIs and paths suck, but I have to do it. I imagine they'll be part of stc when I get to it. This is not the first time I've needed these two.

### More dependency shedding

nlohmann/json is the last AI slop dependency. It's version pinned to before the AI slop contributions took off, so there's no immediate risk, but I still want to get rid of it.

I was planning to wait until C++26 so I could use reflection with a yyjson fork (yyjson also has AI slop in it), but it's small and simple enough that it should be fairly easy to maintain. Well, simple is relative, it's ~20000 lines of code, but it is also the type of code that won't need to be maintained as much. JSON is a stable format, JSON parsers really shouldn't need to be updated as much as they are.

As a tangent to formats, yyjson also allows for more lenient JSON parsing, which I think is going to be better to write. Could probably make some extensions to drop the root object or something as well, but whatever. Lots of other SSGs use YAML instead of JSON, while violet was designed to use JSON because it was the only ([non-XML](https://github.com/gnome/libxml2)) format that had a slop-free parser. Then nlohmann/json fell, and yyjson fell, so the path  forward at this point is fork the thing that gives the least amount of maintenance required, and prep it for C++26 reflection when the time is right. Raw yyjson isn't _too_ bad tbf. 

Plus, iris having a generic data object is perfect for a generic conversion. Splitting out the object could potentially allow the JSON parser to directly work with iris' data objects again, like it did under nlohmann/json. The language itself should not have a JSON parser in it, but its internals does have something analogue to JSON. 

### Personal plans

At some point, I'll want to make my own doc theme. I mean, yes, I could alter the default theme, but I want the default theme to mostly not be actively objectionable. The doc theme could and probably should match my proper website. I don't think I want shared CSS between the two, I mean more thematically. I do want the doc sites to be noticeably different from my actual website, but still recognizable as the same style. Also means I have an excuse to add a theme to the brand new [theme list](https://lunarwatcher.codeberg.page/violet/themes/third-party-themes.html) that currently contains no themes.

I am very happy with the theme of my website though. The buttons could use some work, but overall pretty decent. (For complaints about the font selection, [you only have yourself to blame](/notes/webdev/fonts.md)).

---

I do also wonder what more I could use iris for. I have a couple other automation projects in the works, but none that need templating in a way that isn't covered by emacs snippets. We'll see :3 


[^1]: Admittedly, most of these are not render-related, but markdown parser tests. The markdown parser was also written from scratch, so it has a lot of test cases. Adding to it is the closest I've ever got to doing TDD, which I still fucking hate.
