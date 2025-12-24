---
title: How Stack Exchange, Inc. killed the comment archive on SE chat - a post-mortem
published_date: 2024-09-12 22:21:22 +0200
tags: ["stackoverflow", "post-mortem"]
---

As an obligatory disclaimer, there are a lot of details that remain unclear. This is due to the Stack Exchange network and CloudFlare both being closed-source, and there's only so much I can do without access to debugging details directly from CloudFlare, which I obviously don't have access to. Aside being a user and a volunteer moderator, I have no affiliation with Stack Exchange, Inc. - I just maintain a bot that happened to use Stack Exchange Chat for output.

For context for anyone not familiar, [Boson](https://github.com/LunarWatcher/boson-light.cpp) is a chatbot that runs comment archives for [Meta Stack Overflow](https://chat.stackoverflow.com/rooms/197298/meta-stack-overflow-comment-archive) and [Meta Stack Exchange](https://chat.meta.stackexchange.com/rooms/1702/meta-stack-exchange-comment-archive) (both of which have nothing to do with the company behind Facebook). It's one of the more commonly used bots among meta users, and needs to be reliable to provide value. 

## Timeline

Note that all timestamps and dates are in UTC+2.

* 2024-08-30: [CF JavaScript detections](https://developers.cloudflare.com/bots/reference/javascript-detections/) (hereby referred to as "bot detection", because that's what it is and it's a few characters shorter) was enabled. The date is based on digging around the internet archive and looking for requests to `/cdn-cgi/challenge-platform/`. 
* **2024-09-06** 20:10:18: First round of downtime. Boson goes down for 30 minutes after running into CloudFlare.
* 2024-09-06 23:11:05: CloudFlare's JavaScript detections kills the comment archive for 60 minutes following an attempt to forcibly reproduce the error.
* 2024-09-07 00:34:53: A workaround attempt runs into a CloudFlare block (HTTP 429) when sending a chat message, exhausting the last workaround.
* 2024-09-07 [00:00-03:00]: Debugging shows no workarounds exist, and the comment archive was moved to the [unofficial meta Discord](https://discord.gg/pcBMbMqA79) following a two-hour rewrite of Boson's source code. Boson has remained more stable there than it ever was on SE chat since that rewrite.
* 2024-09-07 15:40: SE is informed.
* 2024-09-11: SE responds, and was given ray IDs and debugging details directly, after the debugging details had been mentioned internally in a few places already, ending a nearly three-week streak of my posts being ignored by employees.
* 2024-09-11: Further investigation showed the bot detection is far more aggressive on 404 pages. Some initial reproduction steps stop working. 
* 2024-09-12: Many more pages the bot detection is aggressive on were identified as part of writing this very blog post

SE has partly labelled this as a bug in the discussions on 2024-09-11 - however, at the time Boson went down, it looked like something else. Specifically, it looked like [a change to the bot rate limiting system](https://meta.stackexchange.com/a/403004/332043), and following debugging not finding a rate limit, it looked like a partial rollout of the rate limit. At the time, this was only announced internally, and the real culprit just happened to become a problem in the time range the rate limiting was expected to be rolled out. The rate limit was quietly delayed, which wasn't mentioned until several days had passed. This assumption resulted in me trying to chase down several causes that turned out to be irrelevant - including attempts to trigger the rate limit, and trying to loadshed to see if that helped. These were dead ends because, as I later found out, it hadn't been rolled out yet. Instead, the real cause turned out to be an unannounced bot prevention change, likely in the form of CloudFlare rule changes. However, because I obviously don't have access to Stack Exchange, Inc.'s CloudFlare config, I cannot identify the exact cause.

## Starting event: Boson goes down 

on 2024-09-06, Boson went down, and was blocked from logging in for 30 minutes. In addition to Boson being killed, all other attempts to access the site (outside browsers) were killed as well. `curl https://stackoverflow.com` ran into the same block. I've run into CloudFlare blocks a few times, but this particular block is new. Unlike some of the other CloudFlare and SE-builtin blocks I've run into (primarily IP-based rate limiting and suspicious activity from CloudFlare), the block did not take effect in the browser. Unlike recaptcha blocks that I've run into many times before, there was also no way to work around it by opening a browser and solving a captcha manually - this was an unbypassable 30 minute block that only affected non-browser environments.

Also interesting, unlike other forms of blocks, this does not affect anything but automated environments making requests to the site itself - the API remained operational even after being blocked, which is arguably a very strange block, but that's a tangent.

Following more debugging, this was narrowed down to CloudFlare JavaScript detections, which is aimed at blocking bots. The exact mechanic of how this works is dark magic hidden in CloudFlare. Aside being dark CloudFlare magic, JS detections are [only a component](https://developers.cloudflare.com/bots/reference/javascript-detections/#enforcing-execution-of-javascript-detections) that can be used in other rules. This means that the exact triggering rules depend on Stack Exchange, Inc.'s own configuration - a configuration that has been observed to be wildly problematic.

The number of reports on MSO and MSE about CloudFlare problems has gone up as of late, with normal end-users being blocked. This is likely due to unnecessarily aggressive configuration on Stack Exchange, Inc.'s side, and not (exclusively) due to CloudFlare itself. Personally, I use many other services that (unfortunately) use CloudFlare, but they don't have nearly as aggressive blocking as Stack Exchange, Inc. has introduced.

### Digging down the CloudFlare rabbithole

Following identifying what, my debugging attempts shifted to identifying why. Unfortunately, I still don't have a clear answer to this.

Anywhere from 3 to 15-20 requests triggered the block during the initial debugging attempts. This included requests to questions on the main site, a reproduction step that has not worked since 2024-09-07. Since the initial downtime, it's far more sensitive to requests to specifically 404 pages. `curl https://stackoverflow.com/a` four times, at the time of writing, is still enough to trigger the block for automated software not using the API on my network. 

It seems like a sufficient number of requests, though it's unclear what that means, to the site results in a block. For reasons I don't understand, however, 404 pages are more prone to triggering this block. For implementation reasons, Boson's underlying chat library [relies on a 404 page](https://github.com/LunarWatcher/stackchat.cpp/blob/master/src/stackchat/StackChat.cpp#L115) to extract the user ID for chat without having to dig into more breakage-prone regexes. This is because the user ID may differ from the main site user ID, because chat has been in beta for, what, 12 years or so, so everything is jank. This was identified on 2024-09-11, well after migrating away from Stack Exchange chat. 

on 2024-09-12, a few more pages were identified. `curl https://stackoverflow.com/search?q=%5BREPLACE_WITH_TAG%5D+closed%3Ano`, for example, is insta-blocked. `https://stackoverflow.com/questions`, like 404 pages, also triggers after 3 requests, resulting in the fourth request being blocked.
Like `/questions`, you can currently access one single question in an automated way more or less an unlimited number of times, but if you access three different questions, that results in the fourth unique question being blocked. This block is identical to the 404 and `/questions` pages - all subsequent requests are blocked.

Interestingly, the block from searching does not spread anywhere else. `curl https://stackoverflow.com` immediately after `curl`ing the search page and being blocked from search does not result in a 429. `curl`ing `/questions` or a 404 page does result in a global CloudFlare block, however.

### Workaround attempts

Before digging into the code part of blocked requests, I figured I would try to emulate a browser request. Surely, if it works in a browser, it should work there too, right?

Unfortunately, no. The JS detections are, as the name suggests, JS-based, and getting around the blocks are not as easy as pretending to be a browser. The system is incredibly light-weight, so you don't really notice the requests happening when it validates browser use. There's one weird detail here, though; loading a fully unverified session in my browser still returns the full site, and not the 429 response I see in the terminal. There _is_ a browser component to this, but I've been unable to determine what that component is. This is likely some weird CloudFlare internals that I don't have a chance to figure out without significantly more work, and I've put enough time into this already.

The only way to work around this would be to set up a full browser environment, and somehow do everything in there. Unfortunately, Boson runs on a headless server. More unfortunately, it's C++-based, so getting a full browser environment there is a significant challenge. 

### Abandoning ship and switching chat services

On 2024-09-07 at early O'clock, Boson was rewritten to add Discord as an alternative chat service. This is not  optimal by any stretch of the imagination, but it's the only fallback option I had available.

Even if a vague workaround was found, this bug introduces a significant instability to Boson - if on-site problems or problems on my end happen in a short enough period of time, Boson cannot recover because it'll be slapped by CloudFlare and go down for 30+ minutes. 

## Current instability and remaining mysteries

I previously mentioned that 404 pages are more prone to breaking - yet, they're still used in the source code for the underlying chat library. At the time 404 pages in particular were identified as a problem, Boson had already been rewritten to add Discord support, so fixing it isn't critical anymore. More importantly, there are other ways to get 404s during the login process, and many more ways to run into other sites that may turn out to have limits.

Like I previously mentioned, I've identified a few pages that cause blocks. More importantly, if _any_ of the ones that result in a site-wide block are triggered _by anything_, Boson dies. Boson is self-hosted on my own network, so any actions I take can also theoretically break boson by accident, especially if it's triggered by a userscript. As part of the fallout, I've disabled all my userscripts, but there are a few that make automatic requests to main to provide extra moderator-specific information in the UI that isn't available by any other means. If I reenable any of those at some point, there's a good chance those requests get my IP restricted, and kills Boson. 

In addition, the limits are low, and the system is extremely aggressive - even if I removed the 404 page trick used to connect to chat, there's parts of Boson, and parts completely unrelated to Boson that can still get it blocked. Continuing to operate on SE chat is not currently viable. 

There's also a few other problems I've yet to identify. I previously mentioned that one of the bypass steps resulted in a 429 when trying to send a message in chat - this has _never_ happened before. Sending messages in chat, shy of chat going down entirely, has never broken. There are built-in rate limits in chat, for example, and those are handled in the chat library. There are a few other specific and weird error scenarios as well, but a 429 rate limit for one singular message has never been one of them. Funnily enough, the error handling in the chat library for sending messages is intentionally broad on HTTP status codes, so in spite of never having happened before, it didn't kill the bot.

Annoyingly, I've been unable to reproduce this. I still don't know why this happened, I don't know what triggers it, and I don't know if I'd ever see it again if Boson continued operating on SE chat. 

## Why do these blocks exist?

It's no secret that Stack Exchange, Inc. has been trying to squeeze money out of AI companies, without really caring about how it affects end-users. They've made several fully unannounced changes with the goal of preventing various bots. For example, if you aren't logged in and make a search, you only get 500 results. While they might make a "search resource intensive"-argument, it only happened after genAI became a fact. Most likely, the bot detection system is part of that same push, though this cannot be confirmed. Its rollout was not announced, so all the information I have is the information I've acquired through hours of debugging.

But even then, the pages affected are oddly specific. 404 pages result in a block, and `/questions` does too, but if you access a specific question multiple times, nothing. But if you access 4 unique questions, you're out. If you want to search, you get blocked instantly without any results, but that block does not spread site-wide.

It's clear from some of the pages that result in the block that it's about protecting content, but that affecting 404 pages (that aren't 404 pages for a question) is a very, very odd decision that doesn't line up with the anti-genAI-scraping effort SE has been on.

### A tangent on blocking scrapers

While I'm all for blocking AI scrapers, Stack Exchange, Inc. runs a couple hundred sites with tens of millions of combined users, many of which have built tools to work around Stack Exchange, Inc. not prioritising community-oriented tooling. The way the blocks are currently implemented also affects a lot of community tooling - based on my extended investigation, I'm aware of several important userscripts that aren't going to work (reliably) anymore due to the changes here. 

Among all bots, Boson happened to pick a losing strategy this time - but with the exception of [SmokeDetector](https://github.com/Charcoal-SE/SmokeDetector/), the site isn't forgiving to bots that have real value for the site. Unless a bot is critical infrastructure, and is considered critical infrastructure by the comapny too, there's no cooperation to try to keep the bot or tool or whatever running. There's no APIs for chat, and there's no way to get support from SE to get an exception to various on-site restrictions. There's a lot of things not covered by the API, so breaking access to workaround features is a problem. 

Also, as a weak example, when I ran into a CloudFlare IP block a while back, I contacted Stack Exchange, Inc.'s user support, and they said there was nothing they could do about it. I don't know what this means for bots and ✨ special rate limits ✨ and more lax access restrictions, and I no longer care enough to find out.

TL;DR: blocking scrapers good, doing so in a way that kills community tooling bad. 

But ultimately, this is how Stack Exchange, Inc. killed the on-site comment archive - by making the path to connecting to chat significantly less stable than it used to be, all in pursuit of a goal that completely ignores the community they [claim to care about](https://meta.stackexchange.com/q/401499/332043), with all their actions increasingly indicating otherwise. This round of bot prevention killed several tools and at least one bot. Many bots and tools survived, but they might not survive the next round. Or the round after that. Or the round after that. At some point, something more critical for community tooling than 404, search, and question pages are likely going to be affected. Nothing like this has been announced at the time of writing, but if you take a look at all current bot blocking systems and how they affect community tooling, it's clear that it will come eventually.

Also unfortunate, Stack Exchange, Inc.'s approach to dealing with unnecessarily aggressive blocking is [push first and debug later](https://meta.stackexchange.com/questions/403002/preventing-unauthorized-automated-access-to-the-network/403004?noredirect=1#comment1344248_403004) - when the potentially significant[^1] damage has already been done. This might be a viable approach for an understaffed startup with extremely limited resources, but not for a billion-dollar (?) company with tens of millions of users.

On the bright side, as long as that breakage doesn't involve killing the API, Boson will continue to operate with higher stability and reliability by using Discord than it ever experienced running on SE chat. Long live the comment archive.

[^1]: The more of these changes are rolled out, the higher the damage potential. When you block real users, they may not know they can report it as a bug. Personally, when I run into a CloudFlare block, I assume I did something dumb - not that the service fucked around with its configuration and expect end-users to report when they're blocked. I find it hilarious that we live in a world where websites optimise for milliseconds to prevent users from leaving before the page loads, but Stack Exchange, Inc. expects users to stop whatever they're doing and take (realistically) several minutes to submit a bug report through a site they may not be able to access at all. 

    It's a fantastic way to get users to leave and never come back, which is a net negative for the community for reasons that I cannot explain briefly enough to fit in a footnote.
