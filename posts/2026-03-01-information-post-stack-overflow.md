---
date: 2026-03-01T23:26:05+01:00
---

# Information curation and sharing after Stack Overflow

On 2026-02-24, Stack Overflow put the last nail in their coffin by proposing to remove a lot of curation, while trying to solve the engagement loss they've been suffering from for a good few months by killing curation rather than addressing the real systemic issues in their implementation of the Q&A model, particularly that reputation ended up keeping new curators down, and introducing a perception of toxicity that undermined quite a few of the site's activities as a Q&A site. Now it's enshittifying down to another Reddit clone, presumably to try to keep the company itself afloat, but at the expense of what Stack Overflow was meant to be.

I could write (and have written) tens of thousands of words on the avoidable collapse of SO, but that isn't the main point of this post, so I won't. SO _is_ now collapsing past the point of no return for Q&A quality - unless they turn around before it hits the main site anyway. This means the slow death of 19 years of curated information that was already under pressure from not having enough ways to maintain it, and the SO model actively discouraging such maintenance by other authors. Rather than being collaborative, SO's model forces a certain amount of competitiveness that undermines its ability to sustain itself. 

At the same time, most other sources of information are seeing an influx of AI slop. In February of 2026, two major cheatsheet systems fell to AI slop (tldr-pages and cheat/cheat). These were heavily condensed sources of information that may or may not have been useful. They fell before I had the chance to try them. 

There are no other sites comparable to Stack Overflow. [Codidact exists](https://codidact.com/), and I do have hope they have a chance to gain ground, but as of the time of writing, they have not built the critical mass required. If you're considering an alternative to SO, I strongly recommend trying Codidact. The more people try, the more useful it'll become. 

Stack Overflow's chokehold on its own data dump starting in 2024 was fortunately counteracted by archivists, who provided torrents of all the new data dumps. However, sites with data dumps are becoming an outlier. Many sites simply do not offer any way to export their contents, presumably out of fear it'll be redistributed, but at the expense of data ownership and archival. Granted, there are exceptions. Reddit does not have a data dump, but archivists have created data dumps of at least comments. I haven't looked much at it beyond knowing it exists, but data dumps can be created in most places - but usually with a lot of manual effort. 

Small sites that don't gather anyone interested enough will therefore quietly die, taking the information with them as they do if the death is fast enough. In a world where the behemoth we trusted no longer can be trusted, where do we curate and share information?

I'm not going to touch long on walled gardens and forums. Forums do work for helping individuals, but rarely provide enough canonical value to help many people with related situations. That's assuming the forum gets indexed at all. The major search indices in 2026 have got significantly worse to where even open sites can simply not be indexed. It's indexable, but gets cut for whatever reason. For all intents and purposes, this is semi-walled off. Chat sites, particularly Discord who made an entire channel type dedicated to forums, are not indexed at all, and cannot be indexed by design. They're entirely walled off. 

This puts us back in the world before 2008 - before Stack Overflow - where the easily accessible sources of information are first-party documentation, obscure blogs, and random compilations of information.

Unfortunately, unlike in 2008, we live in the present, where we have AI slop machines that get used for documentation. Rather than having good documentation, we get plausibly nice-looking documentation where the content is garbage, because documentation is seen as a chore rather than information sharing.

Around a year ago, I started compiling this information myself. My poorly maintained TIL section on my blog is just a part of this information. Through bookmarks, markdown-based notes[^1], learning several new techniques for finding information[^2], and directly reading the code to try to figure out what to do based on that, I've slowly been building up an archive that I can use. This system still has several challenges that I'm trying to work out, particularly in making certain bits of information available to myself on other devices I cannot sync to, and making certain bits of information public. TIL was my attempt at the latter, but that did not work out the way I had hoped. 

Codidact is much more open to more guide-like content than Stack Overflow. I have not yet tested the bounds of this, but articles as an easily accessible form of content has been discussed at some point, allegedly. I plan to redirect some of my notes there in time. However, there's still bits of information I need readily available, and I currently do not have anything to help with this. That's part of why cheat/cheat and tldr-pages were called out earlier; cheatsheet systems offer fairly easily accessible ways to acquire condensed sources of information that would meet this need, at least as long as I'm able to add my own cheatsheet pages. Unfortunately, the solutions available have been abandoned, or enshittified and sloppified. 

I do fear for the future of information sharing at this point. All we have left is small communities and connections made along the way, as well as sources of information that are under heavy pressure to enshittify and sloppify as well.  

I started writing this post with a plan to segue into distributing information in more readily accessible formats that can be read by arbitrary systems, but I don't have a segue. The state of information work is depressing enough that I'm not sure what I'm planning to do is worth it. In optimal information sharing conditions, we wouldn't need to worry about finding ways to ensure information exists in compiled formats at least _somewhere_ accessible to the general public. Especially when combined with the state of search engines, this really is the darkest timeline. 

Though I do believe Codidact could drag us out of the worst of the immediate problem in terms of high-quality content, anything that involves search engines is inadequate for condensed, aggregate information. Cheatsheets are useful here as long as they can be distributed, but cheatsheets aren't the only option. They are the option that has been developed for so far, with lots of distributed cheatsheets existing, but many of the systems meant to access them are failing in the search area.

I do not believe this problem can be solved in a decentralised way, at least not on discoverability of high-quality sources of information. I do still think I want to try. At the time of writing, I don't yet know what this means. I may end up giving up and just piggybacking off Vim's help files, I may end up making some shit that allows for a distributed standard of cheat sheets and semi-structured, condensed unofficial documentation. 

What I do know is that laying down and accepting the end of structured information is not an option, so it's time to write more stuff that's unlikely to ever be read.

[^1]: I use Obsidian. It's decent, but the developer experience for it is utter dogshit. If you plan to make a plugin, it would probably be easier to make your own editor first than trying to get it into obsidian's plugin repo.
[^2]: GitHub's search, much like obsidian's developer experience, is utter dogshit, but you can find plenty of real-world usage examples of things this way. Very useful if you're stuck with something that simply doesn't have documentation, or where the documentation is fucking worthless.
