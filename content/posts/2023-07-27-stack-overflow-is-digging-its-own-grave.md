---
date: 2023-07-27T23:57:57+02:00
tags: ["stackoverflow"]
title: "Stack Overflow's management is digging the Stack Exchange network's grave"
---

We're currently entering the 8th week [of the moderation strike](https://openletter.mousetail.nl/) on Stack Overflow. The TL;DR: on the strike is that Stack Overflow, Inc. ("the company") forced a rule change effectively unbanning content, and [preventing moderators from using anything but explicit admission as proof of GPT](https://meta.stackexchange.com/q/391626/332043). Why this is bad has been covered in the strike letter, and extensively elsewhere, and I don't feel like repeating it. 

At the time of writing, there are currently 17000 flags pending on Stack Overflow alone. I do not have access to stats for the rest of the network, but as the biggest site in the network, it naturally has the most amount of flags. 

This has a severe impact on the community. Spam sticks around longer, if it gets detected at all, rude comments are left in limbo, and urgent problems are left to have the consequences -- that could've been avoided if moderation took place -- play out. 

Some of the keywords for the strike goals are transparency and communication[^1], ensuring the API and data dumps remain freely available, and the reversal of the GPT unban, among other things.

A second change, still mostly private at the time of writing, also served as the foundation for the strike. At the time the strike started, these were the main points that were focused on. However, during the strike, the company decided to do more idiotic stuff:

* They axed the data dumps, which they undid when the decision was caught, and [a former employee](https://meta.stackexchange.com/a/390023/332043) (thank you, AMtwo) confirmed that it had been axed quietly by management
    * They later made a public announcement [committing to maintaining SEDE, the API, and the data dump](https://meta.stackexchange.com/q/391634/332043), but it has several problems, and continues in the chain of announcements where the company demonstrate that they don't care if they lie.[^2]
* They announced more AI tools that undermine the existing GPT ban, without notifying moderators in advance to let us decide what to do to [avoid conflicting information](https://meta.stackoverflow.com/a/425779/6296561)
* They also announced a tool that apparently seeks to [dump both AI-generated answers and questions to the site](https://meta.stackoverflow.com/q/425787/6296561), again contradicting the current ban and also without at least a heads-up
* [Lied to the media](https://meta.stackexchange.com/q/389824/332043) - numerous times.
* [Misrepresented how mods detect GPT content](https://meta.stackexchange.com/q/389828/332043)
* ... etc. There's far more than this, but finding links for everything is slow. 

As a shock to likely no one, this is a problem. Why is more interesting. 

As [Jon Ericson](https://jlericson.com/2023/07/26/not_understanding.html) so elegantly put it, Stack Overflow's CEO doesn't understand Stack Overflow. They fail to understand the real pain points with the site.[^3]

![A meme of the current situation as a modified version of the "Phoebe teaching Joey" meme. Phoebe (left columns) spells out "Address our outstanding feature requests", and "Joey" (where Joey is replaced by a picture of the CEO, Prashanth Chandrasekar) repeats all but "feature requests", instead saying "add AI to Stack Overflow!"](https://cdn.discordapp.com/attachments/676029765987336192/1134197511670734939/7ty0r1.jpg)

It's also no secret at this point that genAI has tanked SO's traffic, because other options appear far more convenient. There are a large number of reasons for this (including SO's less than stellar public image), but instead of dealing with this, the company responds by blaming its moderators' GPT moderation and pointing to [fundamentally flawed data](https://meta.stackexchange.com/a/389940/332043). Rather than noticing this, taking a step back, and reconsidering their approach, discussing it with mods, jumping on a few calls where mods demonstrate how they detect GPT content, and collecting these heuristics right off the bat, they decide this is yet another hill to die on.

This is how the company is digging its own grave. It's currently stuck in a vicious cycle where they make mistakes or roll something out, and opt to die on the hill, even when alternatives are presented.

Even in the first few responses to the GPT ban, alternative solutions were presented; not banning on the first offense (which employees initially recommended - and they recommended 30 days, and were talked down to 7 by mods), re-decreasing the rate limit between answers from 30 minutes to 3, etc. This is a recurring theme; problems are pointed out, and alternatives are offered, but SE still decide that their way is the only way.

The rate limit itself is also a very interesting case. On December 8th or so (I don't remember the exact date), a change was made to the answer rate limit. Before this change, new users could post an answer every 3 minutes. It was bumped to 30 minutes to combat users dumping 20-30+ GPT-generated posts in a very short period of time.

After the traffic decline started becoming a fact, another mod looked into it, and noticed that the inflection point for the decline in answers lined up precisely with the change to the rate limit. SE dismissed this as "unlikely", because it doesn't account for all the decline. Again, this is SE dismissing a change that could be part of an overall solution, because it in isolation isn't good enough.

The list of these events also keeps going. I don't have a complete overview of them either, because it's an extensive list and spreads across many, many conversations with many different people, in many different places, including places I do not have access to. Alternatives are presented, SE ignores them, and the site continues to decline. 

As a response, the CEO decides to embrace generative AI, instead of addressing the problems that led us here with non-genAI solutions that would perform better, and provide an overall better UX[^4], to leverage the hype train to recover some traffic, rather than addressing the many problems with the site. 

Adding question and answer generation isn't going to help users feeling lost on the site, who get caught in search being horrible, or who stumble into actually hostile users responding to their question, and don't understand how to report it.  It might help people write good questions, but proper onboarding and beefing up the ask question wizard achieves that without risking the AI writing a bad question that omits key details, yielding an arguably worse UX than the baseline. 

This isn't speculation. Thanks to MDN, [we've already seen a variant of exactly this](https://github.com/mdn/yari/issues/9208#issuecomment-1615200919), and why it was problematic. From a quick conversation I had with one of Stack Overflow, Inc.'s developers, it's pretty clear that they're not prepared for the many ways their tool can work against the best interest of its users.

Unfortunately, trying to convey ideas like these to the company are currently pointless. With the CEO only prioritising AI, and effectively ignoring all other problems, the company is busy digging its own hole even deeper[^5], a fact that's exacerbated by its [increasing financial losses](https://jlericson.com/2023/05/17/so_business.html). Unless the company is able to turn around and focus on the _real_ needs of the millions of users, that hole is only going to get deeper. Especially while they actively lie and gaslight to put their mistakes in a better light. I don't want to hypothesise what that might mean for the public Q&A, but I don't see it going anywhere increasingly positive if nothing happens. And I suspect that to get there, new leadership is required.

## Footnotes

[^1]: Transparency has been a recurring theme since the [2019 events](https://meta.stackexchange.com/q/333965/332043) that was a couple days from becoming a full strike. Communication is key to the survival of a for-profit community-driven platform. Without effective communication, the site devolves into "us vs. them", a negative for absolutely all parties involved.
[^2]: See particularly the first paragraph; "many words have been written around the company's commitment to the ongoing existence of [...]. Much of that  text can be confusing or conflicting" is extremely problematic. They try to lie by dismissing completely correct statements about the events surrounding the data dump being killed as "confusing or conflicting". See, again, AMtwo confirming the events that took place: these aren't misunderstandings, this shit actually happened, and Philippe (along with the rest of management) seem to want to bury this fact.

    The entire paragraph only serves to dismiss the concern as unfounded, when there's quite a lot of foundation for it, rooted in events that took place.

[^3]: For context, the major ones concerning all users are onboarding. SO has always had an onboarding problem, resulting in a perceived harsher culture than the site actually has. If Stack Overflow had a proper onboarding system that helped users understand when to use the site, how to ask, how to answer, and how to appropriately deal with rude content (i.e. flag), UX wouldn't be as bad as it currently is. A significant number of Stack's image problems are down to its non-existent onboarding.
    
    There's also smaller changes that really need to be made, but that never happen. One example of this is improving search. To their credit, improvements are allegedly coming to search, but you don't need genAI to improve Stack Overflow's on-site search. Their search is notoriously bad, to the point where its use is discouraged by regulars of the site. Real search engines will almost always be better, but Stack's on-site search is barely usable, a far cry from the standards the major search engines have set.
[^4]: To be abundantly clear, I'm not opposed to generative AI, or AI at large for that matter, but like everything else, genAI has its uses, and it has stuff it cannot (or should not) be used for. A summary tool is one thing, but auto-generating questions and answers [is prone to severe problems](https://meta.stackoverflow.com/a/425167/6296561) caused by genAI hallucinations, many of which will not be caught. While that is a more extreme example, not all users are fluent in English, or sufficiently skilled in the tech they're interested in to notice when the genAI is hallucinating.

    [This](https://meta.stackoverflow.com/a/425176/6296561) demonstrates an example where it's edited drastically. A user new to programming with poor English might not be able to understand that critical information has been removed and replaced with garbage. This isn't a hypothetical: this is a thing that can happen, and in the context of Stack Overflow, this should never happen.
[^5]: I'm sure there are some people that would love to see SO crash and burn in favour of their favourite AI tool, but don't forget that the training data has to come from somewhere, and if it's based on AI-generated content, [your favourite AI tool will slowly turn to shit.][model-collapse]

[model-collapse]: https://venturebeat.com/ai/the-ai-feedback-loop-researchers-warn-of-model-collapse-as-ai-trains-on-ai-generated-content/
