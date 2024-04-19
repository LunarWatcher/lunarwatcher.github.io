---
title: "How to fix Stack Overflow - and why it's probably not going to happen"
tags: ["stackoverflow"]
date: 2024-04-19T22:46:29+02:00
toc: true
---

For those out of the loop, [shit hit the fan last year](https://meta.stackexchange.com/q/389811/332043) after Stack Overflow, Inc. (hereby referred to as "the company") decided to overrule a community consensus regarding AI-generated content. Following the initial event, a long series of poorly thought-through features and changes (both related and unrelated to AI) have been announced by the company. Meanwhile, the community has been asking for the same things we have for longer than I've been a member. Let's talk about some of those things, as well as my last take on the problem.

As a disclaimer, I'm one of the currently [27 elected moderators](https://stackoverflow.com/users?tab=moderators) on Stack Overflow. This perspective is therefore a combination of experiences on both sides of moderation. If you're looking for more confirmation that mods on SO are evil, this is not the post for you.

## What is a moderator?

Before getting into the rest of this post, there's one important clarification I need to make. Whenever there's complaints about moderation on Stack Overflow, it's usually "the moderators" that get the blame. However, quite often, actual moderators have no involvement in a post. We deep enough in the site draw a distinction between curators and moderators - both do moderation, but only moderators[^1] have access to unilaterally use most tools[^2]. Additionally, only moderators can warn and suspend users.

On most other sites on the internet, anyone who can do moderation is a moderator, but  this isn't the case on Stack Overflow. Anyone with enough reputation can contribute to moderation of the site. Some tools, such as editing, is granted without any rep requirements, but requires approval from other users before taking effect[^3].


## Perceived hostility, the welcoming wagon, and onboarding

One of the most common ways to describe Stack Overflow, aside the description of the Q&A bit, is that it's toxic, hostile, elitist, etc. This perception was acknowledged by the company as part of the [welcome wagon](https://stackoverflow.blog/2018/12/04/welcome-wagon-community-and-comments-on-stack-overflow/) back in 2018. 

The welcome wagon was intended as a way to change this perception. It's been around 5-6 years, and this perception hasn't gone away.

### The initiative cycle

Before we can understand why the welcoming wagon failed, we need to look at how development has been done at the company for the past few years. I have a longer version of this explanation [here](https://meta.stackexchange.com/a/396939/332043), but here's a summary:

It starts when the company announces some initiative - this can be anything, ranging from the welcoming wagon to the more recent staging ground and outdated answer projects. They make a _huge_ deal out of it, announcing it to everyone able, possibly unwillingly, to listen. 

They follow up this with research. This comes in one of two forms; either as pure research, or as research on a feature they're rolling out. If it's pure research, a feature follows sooner or later anyway. 

The result of this initial feature, assuming it graduates, then gets released, often with many of the bugs found in the testing phase still present. This cycle may repeat up to two more times (but occasionally more), after which, the project is quietly abandoned. Resources are shifted away, and no one hears anything more ever again. 

One uncontroversial example of this is the [outdated answers project](https://meta.stackoverflow.com/q/405302/6296561). As the title indicates, the goal was to deal with the poorly aging parts of the Q&A, to make sure content stays up-to-date. This is an actual problem, and one that really needed to be addressed.

This initiative spawned a flagging exercise, where answers could be flagged as outdated. This was used for research purposes, and resulted in the two changes from the outdated answers initiative:

1. Accepted answers were unpinned
2. A new sorting option ("trending") was added

In other words, nothing done to address outdated content was done. There's no version labelling or other way to actually indicate if an answer is outdated. Unpinning the accepted answer kind of helped, but not a whole lot. There are plenty of non-accepted outdated answers on the site. 

So, simplified, the cycle is:

1. Hype the hell out of A Thing
2. Do a couple things under the initiative
3. Quietly abandon it. Very, very rarely, there may be a public acknowledgement that the thing has been axed.

I'm also leaving out some parts regarding how they do their announcements, because this isn't relevant to this discussion.

### Why the welcome wagon failed

The welcome wagon failed for the exact reason I mentioned in the previous section. They announced it and hyped it up, they did a couple minor changes, and then abandoned it. None of the features they created have been touched since.

One of their flagship products, the unfriendly robot, still exists. However, due to changes in comment patterns, it has around a 95% false positive rate by the time it reaches moderators. It adds a lot of work, without actually being the thing it set out to be. 

For the record, when I say it flags badly, I mean it flags _really_ badly. Here's the contents of a couple of the worst flags I've seen:

> best answer ever

> Merry Christmas - Good luck 

> you deserve a hug !

Again, as a reminder, the unfriendly robot flagged these comments as rude. Under Stack Overflow's commenting rules, they are noise and would be deleted, but they're by no stretch of the imagination rude. To be clear, the unfriendly robot's flags are not binding. All three flags were correctly declined by mods.

Personally, I've ended up calling the unfriendly robot decline target practice. The three examples above are far from the only bad flags the bot has raised - again, I estimate around 95% of the flags that reach mods are invalid. 
This is a shame, though, as the idea itself is good. A lot of users don't know when to flag, so too many rude comments go under the radar. The unfriendly robot was meant to bridge this gap. It's possible it did at some point, but it was introduced years before I was elected. Since then, it has aged like a fine bottle of open milk in direct sunlight, and no longer achieves this goal. All it does is add unnecessary work for moderators, without catching much other users don't catch anyway. There are several user-created bots that monitor comments, including unfriendly comments, and do so better than the company's attempt at such a bot.

Combined with the initiative receiving no further attention, the initiative died, and nothing else was done to address the problem. Many of the problems identified in the process remain to this day as a result.

### My theory on the cause of perceived hostility

I've said multiple times that I don't believe Stack Overflow is toxic - at least not in a systemic way. Any community has toxic users, yes, but the mod team does manage these users when we find them. However, a lot of the perceived toxicity doesn't come from direct user interactions, but rather from seeing moderation actions. Downvoting and question closure gets perceived as hostile and unfriendly by users. This is, objectively, a problem. But why does this happen?

Over the past year or so, I've been repeatedly mentioning onboarding to the company. In the past few months, I've theorised that the lack of onboarding is the root of not just perceived hostility, but multiple of the other problems.

The objective take on closure and downvoting is that low-quality questions, or questions that don't meet Stack Overflow's rules, should be managed. If you think about it, this makes sense. As an extreme example, if you're looking for questions to a Python problem and go to Stack Overflow and google it, and get a Stack Overflow link, you expect a solution. You don't expect to find someone with a question about their pet snake. 

You find topic and quality scoping everywhere - including on Reddit, which is often cited as being "much more friendly than Stack Overflow". Yet, if you look at some of the programming subreddits, they do have rules similar to Stack Overflow. They have rules, and some subreddits delete content that doesn't meet their quality thresholds. Why then, is it that when this happens on Stack Overflow, it's unexpected, rude, and toxic? 

The problem is that Stack Overflow, through both official and unofficial channels, advertises itself as a site where you can ask about anything related to software development. This is _technically_ true, but not in practice. Stack Overflow is a Q&A, but its advertising is closer to that of a forum. The first impression users get of Stack Overflow is that anything is fine. I've personally had university lecturers that, misguidedly, recommended directing many technical questions to Stack Overflow. Some of those people were then surprised when they posted bad, off-topic, or duplicate questions, and it was handled, because they were never introduced to this part of the site. 

What happened here is, in practice, part of the onboarding system. And it's failing miserably. Through poor explanations of what the site is for, people come to the site with a different picture in their minds of what the site is. When it then turns out not to be that, negative reactions occur. The problem isn't with the description of the site they were given - it's with "the moderators" on it. 

Downvoting isn't presented as a quality control measure, like it's supposed to be. Instead, it's seen as public humiliation or abuse from, again, "the moderators". This is further reinforced by how Stack Overflow is presented among current and former users who haven't gone deep enough down the rabbithole to understand the rules and systems of the site. 

My theory is that the lack of onboarding is the reason Stack Overflow is seen as toxic. Users come to the site expecting one thing, and when they get something completely different, the immediate reaction is often to blame toxic users. This is, in part, because how any site is talked about in the media and elsewhere _becomes_ part of its onboarding. When people come to the site expecting to ask anything they want, but have also heard bad things about Stack Overflow, this is a setup that guarantees failure.

"Look for evil and you shall find it" - even if it isn't actually evil. Or toxic, in this case. Expectation management is an incredibly powerful tool, and one that's part of any good onboarding strategy. If you disappoint users in the onboarding process, you often don't get a second chance. This is one of the critical ways the company has failed the site over the past decade. 

## The current onboarding system

We already know public perception becomes part of any onboarding system - whether it's desirable or not. But let's talk about what other systems Stack Overflow has for onboarding:

1. [The tour](//stackoverflow.com/tour)

The end. 

No, really. If you have no clue how to do anything on the site, the tour is all the information you get. The tour has also aged like a fine bottle of open milk. It has proven inadequate

In more recent times, there's also the addition of "the wizard", which is just a guided question experience. If you've ever used GitHub in a repository where there's different fields to put information in, the wizard is that, but significantly worse. It also has a number of bugs (that were ignored, see the section on Stack's development cycle for why). The current revision of the wizard does little to nothing to aid onboarding, and does not make the list.

A currently unpublished contribution to onboarding is the staging ground. However, because the staging  ground is reviewed by users, and there aren't [anywhere near enough users](https://meta.stackoverflow.com/a/429612/6296561), many users will go through the staging ground without getting any help. In addition to being unpublished and therefore not publicly available yet, this problem causes it to not make the list. 

Simply put, the current onboarding system is nearly non-existent. Most of the onboarding system exists in the form of informative documents scattered in multiple places. If you want to learn how something works, you may find a question in one of three places (or a combination of the three, or none at all):

1. The help center
2. [Meta Stack Overflow](//meta.stackoverflow.com)
3. [Meta Stack Exchange](//meta.stackexchange.com)

This also assumes you manage to find the thing you're looking for, and because search is garbage, this isn't a guarantee either. Any new user with no experience on the site therefore gets:

1. The tour
2. Informational posts and articles scattered in an illogical way

Many people therefore end up doing trial and error to figure out what is and isn't allowed. I don't think it needs to be said that this is bad - especially for the users trying to figure out how to correctly use Stack Overflow.

## Why the one-rep voting initiative would've failed

Shortly after the strike in June 2023, Stack Overflow announced that they were going to drop the rep requirement to vote to 1 rep. This was axed after negative feedback. It was revived in April 2024. In the process, they also steamrolled a promise to allow sites to volunteer, and dropped the experiment on Stack Overflow. A few days later, [it was fortunately axed again](https://meta.stackoverflow.com/q/429739/6296561).

There's going to be some people who read this and fail to see why it's a bad thing. Here's a few of the reasons, all of which have been mentioned in the initial announcement:

1. Drastic increase in vote fraud - upvotes, yes, but also in downvote fraud
2. Drastic increase in moderator workload as a result of #1
3. The experiment never had a way to measure vote fraud, thereby invalidating any way to measure the underlying research hypothesis
4. By far the most important reason: one-rep voting is a band-aid around the actual problem; decreasing engagement, and the feeling that Stack Overflow is toxic. 

There's a lot I can say about the fourth point, but this post is already getting long. Summarised, following the release of ChatGPT, Stack Overflow's traffic dropped around 30-50%, depending on what metric you use as an estimate. In addition, changes made to the rate limit system has made it harder to provide many answers in a short-ish period of time. This was done to reduce the influx of ChatGPT, but had the unexpected result of contributing to the drop in answerer retention. Rather than reverting this change, the company decided to blame literally anything else they could find as an excuse[^4]. This became one of the major reasons the 1-rep voting initiative happened.

As a result, the initiative was destined to fail even if it was released. Allowing everyone to vote won't fix the underlying onboarding problem - it'll only push it down the line, to when one-rep voting isn't new and fancy anymore. 

## The solution

### Onboarding, onboarding, onboarding

At the time of writing, the company has [promised a focus on onboarding](https://meta.stackexchange.com/q/398734/332043). They have not yet announced any details regarding what this means in practice. I'm not optimistic, given their track record (see, again, the initiative cycle section for why), but this may turn out to become a solved problem in the near future.

But as the system currently stands, it's clear something needs to be done. The single most impactful way to fix the problems with Stack Overflow is onboarding. Even if nothing else is done, a proper onboarding system to all parts of the site can have an impact higher than any other single area. It can be used to introduce users to correctly using the site, thereby decreasing the negative experiences and decreasing perceived toxicity. This also helps improve post quality, which helps the goal of SO being a Q&A. Combined with some automated systems that double as onboarding systems (for example automatically detecting certain comment categories and suggesting to vote instead), reductions to the mod workload can be accompanied by increased engagement and improved user experience for everyone involved.

Wikipedia has an extensive onboarding system that includes [an interactive editing guide](https://en.m.wikipedia.org/wiki/Wikipedia:The_Wikipedia_Adventure), and [lots of structured information](https://en.wikipedia.org/wiki/Help:Getting_started). There's guided modules, long-form content, short-form content, and other various guides. There's onboarding systems for pretty much every style of learning. Yet, Stack Overflow, which is far more user-centric[^5], doesn't. I've already covered the consequences of this, and particularly that I believe this is the cause of the negative perception of the Stack Overflow community.

I imagine that, at some point, someone who disagrees is going to read the article, and I encourage you to think about it. Would your experience have been different if you had a clear idea of both what's expected of you, and if you were given much more clear instructions on how to ask a good question? From the people I've talked to, the answer has so far only been yes. Granted, I don't have a large sample size, but having a guide to a new thing does help - even a non-human guide in the form of structured information and guided tours can be an incredible help if done correctly. 


### Removing reputation

No, really. 

To be clear, when I say remove reputation, I don't mean "remove votes". Upvotes and downvotes are meant to be a rough indicator of question or answer quality or correctness, and this is still useful. This would also allow votes to be used as a way to make new information more visible. One of the current barriers for up- and downvoting as an indicator of outdated content is that most users can't access voting tools. 

That aside, the current reputation model has proven itself woefully inadequate. It worked at a point, but it has scaled horribly. It's a huge barrier to entry for anyone interested in the curation aspects of the site, and the gamification aspect strengthens negative and positive feelings related to voting. Many of the negative reactions I've seen to downvoting in my time as a moderator have been related to reputation. Downvoting without giving a reason is seen as unfair, not because of the downvote itself, but because of the effects on the user's reputation. This, however, is a rabbithole onto itself, and one I won't be diving into today.

To address the elephant in the room, you obviously just can't remove reputation and call it a day. Moderators are still needed, and so is handling spam and rude content. One of the systems I've been advocating for is a system similar to that of Wikipedia. Rather than having a really bad measurement of trust (reputation), trust should be gained through actions, and reflected by granting more privileges. Some of them are automatic, some of them are not. If you do good, you unlock more privileges in the categories you've done well in. Otherwise, you don't. As a result, you also don't unlock any privileges for stuff you don't really care about, so you can focus on the areas you want. This can be one of many categories of curation, providing content, or possibly other categories of actions that don't currently exist.

This is also useful from a moderation perspective. It would, for example, enable moderators to remove the commenting privilege from users who keep abusing it. It also means that moderation tools are unlocked after the user has demonstrated some proficiency with the tools, rather than throwing them into it without any onboarding there either (which is what the current review system is today). It would also open for a decentralised moderator structure, where there's "mini-moderators" in different areas of the site, with elected moderators serving at an equivalent capacity to today's system.

Additionally, removing reputation could be accompanied with allowing everyone to vote. Without reputation, there's no risk of fraud, and as long as it's combined with onboarding systems, it's no longer used as a band-aid, but as a full and intentional feature. I'm increasingly convinced allowing everyone to vote is the way forward - but not as the system currently stands.

### Why it's (probably) not going to happen

Some of what I've mentioned here isn't new. Some of it is, but that doesn't matter. The ideas for onboarding and other improvements to the site have existed for over a decade. The majority of them haven't even been acknowledged by the company, even after receiving significant support from the community.

Combined with the previously mentioned initiative cycle, I consider it highly unlikely that the company will ever be able to focus on onboarding long enough to make a significant improvement to the site. 

It is possible that they manage to get their priorities straight for long enough to make a dent at some point in the future, but I strongly doubt it. At the time of writing, many of their ongoing initiatives and priorities are aimed at attempting to mitigate the symptoms without addressing the real causes of the various problems with the site. 

There are definitely other causes of the problems than onboarding, notably in tooling, but these aren't a priority either. Pretty much everything community-oriented has been deprioritised and axed at some point. The previously mentioned staging ground was, for a while, axed, following [the 2023 layoffs](https://meta.stackexchange.com/q/393791/332043), while the company was busy chasing the hype rather than addressing any of the many real problems. It's disappointing to say this, but there are many good solutions on the table, and the company seems to be ignoring these in favour of band-aids they can use as a hype generating tool. As long as the current management prioritises hype over users, Stack Overflow will remain broken.

[^1]: Duplicate closure can be unilaterally performed by anyone with a gold badge in one of the tags, but this is an exception to the rule.
[^2]: Certain mod tools (particularly redacting edits) requires two moderators.
[^3]: For edits in particular, you need 2000 reputation to make edits without the edit going through review. At 15 rep, you unlock flagging, which is effectively uncounted close votes with a review process (on questions anyway). 
[^4]: To be clear, reducing the rate limit back to its pre-increase levels (or somewhere in-between) won't magically recover all the traffic, but it would  help regain some answerers - which is a contribution even if it isn't a fix.
[^5]: By "user-centric", I mean there's much more user-driven content. Many, of not most people who read Wikipedia don't edit anything, and don't think about the large regulatory framework behind the site. Yet, Wikipedia's moderation, privilege, and onboarding system wipes the floor with the system (to the degree it can even be called that) Stack Overflow has.
