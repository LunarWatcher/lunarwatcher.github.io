---
title: "The dark side of Hacktoberfest"
date: 2021-10-03T14:40:56+02:00
tags: ["hacktoberfest"]
---

I decided to participate in hacktoberfest this year, which I haven't done since 2017 for various reasons completely unrelated to what I mention in this article.

Disregarding bad, trivial PRs doing idiotic things just to bump numbers, there are tens of thousands of repositories designed purely to grind out pull requests. Pull requests are much more managable this time around; slapping a PR like that with an `invalid` or `spam` label contributes to banning the individual from Hacktoberfest. There's still a common criticism here, that has a root in how some repos use the invalid tag a lot more casually, without the PR necessarily being bad enough to warrant banning someone from Hacktoberfest. I'm not here to discuss this, though, in part because handling spam to a repo is managable; handling the consequences of tons of spam elsewhere is another can of worms that I'll be opening because the situation pisses me off.

The repositories in question are the type that don't really have a purpose. They exist to cheat through hacktoberfest with low-quality, 0-effort pull requests that don't bring any overall value to the open-source community. To quote [Luke](https://github.com/lukeocodes) in [a message](https://discord.com/channels/720788516837261322/735506302784110652/893475002920361994) on [the Discord server](//discord.gg/hacktoberfest),

> Contribute. To. Opensource. Not. Your. Wardrobe.

This year, Hacktoberfest explicitly tried to highlight its purpose -- contributing to open-source -- by using the phrase "quality over quantity". A few of the shit repos in question then decided to copy-paste this phrase in an attempt to make the repo seem good (spoiler alert; it's still garbage).

## "Motivations"

The reason people set up these repositories vary, but it's mostly any combination of any of the following:

1. Wanting a repo with lots of stars to inflate the perceived value of their contributions to open-source
2. Wanting an easy way to get lots of maintainer points (because this year, maintainers are in a separate category and can earn swag by reviewing pull requests, and not making them)
3. Offering an easy way for people to get pull requests

Here's a real example of the first point in practice:

![Screenshot showing a semi-anonymous user with 5 pinned repos; 4 of them have near no stars, and none of them have forks. The 5th is a hacktoberfest data structure and algorithms repo, or in this context, a star grinding repo](/img/hacktoberfest_inflation_example.png)

<sub>The user is semi-anonymized to reduce the meta effect</sub>

Most of the repos in question center around easy actions that Hacktoberfest has explicitly said no to, but that still keep appearing because some people just suck; data structures and algorithms, adding names to a file, adding links to a file, adding quotes to a file, etc. There's a long list of repo types that are against Hacktoberfest's values; [this isn't news](https://hacktoberfest.digitalocean.com/resources). Some people just chose to ignore it and contribute to spam instead of contributing to open-source.

Many repos like that this year require "staring this repo" as a step to get a contribution approved. You don't have to look far to find it; search for `label:hacktoberfest language:your-favorite-language`, and you'll probably find a shit repo faster than you can find a good repo.

Disregarding all the people who feel like cheating for a t-shirt (or a tree) aside, though, this has some pretty big consequences for those of us who want to contribute to legitimate repositories. In case the last line didn't give away why, how do you find good issues in good repos when the search is flooded with bad issues in trash repos?

As I'll mention in a bit, the core of the community, as well as the organizers have provided spaces to find these repos, but they're unfortunately not getting anywhere near enough attention to be useful to everyone. Most of the repos that appear tend to be in "mainstream" technologies. There's a lot of Android, and various JavaScript stacks, along with Python, Rust, Go, and a couple others. There's a lot of stuff in a mobile- or web context, though, meaning it's a pain in the ass for desktop devs to find anything useful from these channels.

This means there's a paradox. The only way to find relevant repos is search. Search is flooded by trash repos as mentioned above - have fun finding relevant repos to contribute to!

Hacktoberfest does encourage contributing to other repos and not your own, but they don't disallow it. Fortunately. As someone who does a lot of niche shit, this makes the maintainer approach unsustainable. People who decide to participate in Hacktoberfest as maintainers probably struggle with this, at least in smaller repositories. Search being flooded means fewer people find your repo through search, and less traffic from searches means smaller repos risk getting 0 PRs (which I'm no stranger to, even on my biggest project with at least a couple hundred users).

## Finding good repos is hard.

It's a bit of a hopeless situation like that.

Whether you participate as a contributor or a maintainer, small projects are gonna get drowned out by spam repos.

ALl this said, though, not everyone who contributes to these shit repos are bad. I've personally met a few people who didn't know it was bad to contribute to repos like that. At the same time, it's not exactly an excuse considering there's resources telling people not to contribute to those repositories.

It's worse for beginners, though, especially the ones who don't read the resources and don't know they're meant to primarily contribute to legitimate repos; searches are flooded with spam repos, so the beginners think these repos are legit, and consequently are fine. Hacktoberfest's ban system only makes contributions not count towards hacktoberfest progression; it doesn't remove the GitHub repo, for obvious reasons.

This means that the people who create spam repos, and the people who use spam repos as a way to easily grind pull requests, actively make it harder for everyone, and especially beginners, to find things to contribute to.

People really suck some times... 🙄

## The community

Hacktoberfest has set up a [report page](https://hacktoberfest.digitalocean.com/report) for reporting these, but compared to moderating on Stack Exchange, it's substantially harder. There's a one minute rate limit on reports, and it doesn't help that new repositories keep popping up constantly.

On the bright side, though, there's the community; on the Hacktoberfest discord, there are actually a lot of really nice people. The organizers and helpers also pull an insane load with server- and event management, having banned over 200 repos in the first day (with over 4000 reports pending as of yesterday). The organizers are getting better at shutting down the type of repos mentioned here, but it unfortunately doesn't make finding projects any easier. The Discord has a moderated chanenl for sharing projects that are generally legit, but a few still sneak through. A [community-led repo](https://github.com/TheLastProject/Hacktoberfest-2021-legit) also exists for listing repos, but with only 23 commits after a day, it's currently of somewhat little use.

Of course, it's still early in the event, and a lot of the early spammers in previous years have been shut down before the end of the event. I hope they manage to turn things around.
