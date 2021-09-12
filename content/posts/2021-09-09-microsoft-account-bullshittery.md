---
title: "Microsoft account bullshittery"
date: 2021-09-09T22:32:39+02:00
tags: ["microsoft", "microshit", "minecraft"]
nocomments: true
---

I some times play Minecraft.

Exclusively on a private, and usually modded server with one other person. I randomly found out today, from a third party source that didn't even have the account migration as the core focus, that Minecraft is migrating to Microsoft accounts.

To say that I don't like Microsoft is an understatement. I'll spare you the details, but that fact is part of the underlying theme. As a consequence, I'd rather not have a Microsoft account. I have one for uni, and I'm sure I have an old one lying around somewhere, but having one I need for non-Microsoft products is not something I want.

Of course, calling Minecraft a non-Microsoft product is a stretch. Mojang is unfortunately owned by Microsoft, along with several other companies I really wish they hadn't bought.

It's not like Mojang accounts are better. I had to reset my (in)security questions, because I have no clue what I wrote last time I reset them. Clearly wasn't what I thought, and I didn't save them. After that, which involved getting an email, I had to re-verify my account to migrate. After that, I had to create an account, landing at a total of four emails just to migrate to an inferior system. As far as SSOs go, Microsoft is arguably the worst.

My uni recently forced 2FA, and login is through a different SSO that, for whatever reason, also loops in Microsoft in the auth process, in spite of not having anything to do with Microsoft. When I tried setting up 2FA through Microsoft Doesnt-Want-To-Authenticator, I followed the instructions _exactly_ two times, and the app failed to register the 2FA code generator both times. The third time, I went with a different authenticator - Google Authenticator, the one I wanted to use in the first place, but that didn't seem like an option. Worked on the first try. I'm not a fan of Google either, but if I need stuff that works, Microsoft isn't my go-to.

I'd also like to take a moment to appreciate the irony of Microsoft products not working with Microsoft products, but mysteriously working with generic products from other companies.

Okay, sure, but what does this have to do with Minecraft?

Well, just having a Microsoft account isn't enough. I had to set up an Xbox account. After doing that, I saw my username was postfixed with the discriminator, but without the `#`. Gave off a real "user374198743892"-vibe, even though the UI _clearly_ showed that it was a discriminator. I tried to rename myself because I thought they had appended a bunch of numbers without making it clear. And that's where I saw (paraphrased and translated, because Microsoft forces me to use Norwegian):

> \[Username\]\[Discriminator\] is for xbox games that don't support the new gamer tag system, and all Xbox 360 experiences

`[Username]#[Discriminator]` was listed as being for "Xbox One-console and Xbox apps". In summary, Microsoft's own website **doesn't support their own systems**.

{{< youtube ahrBOvz1jzA >}}

I genuinely cannot comprehend how they're able to make a breaking change, but not bring their core systems up to date. On the other hand, that's exactly what Microsoft is known for.

---

I initially started writing this 3 days ago, but today (12.09.21), Microsoft had the brillaint idea of blocking my account for a "possible violation of our Terms of Use". It's a brand new account that I've done nothing on but migrate Minecraft. The last login was a few days ago, all of it was from the same IP and same device, but it was still somehow detected as abusive. [Here we go again](https://www.youtube.com/watch?v=ahrBOvz1jzA).

They demanded phone verification to unblock it. So, to sum up the entire clusterfuck:

1. No real advance notice for avid third party client-users and inactive users (would it kill you to send an email?<sup>a</sup>)
2. Had to recover my original Minecraft account
3. I had to make a Microsoft account
4. I had to migrate
5. I had to give in to Microsoft holding my account hostage for no reason what so ever a couple days later

<sup>a: This has apparently been known for over a year. In that time period, I haven't once looked at Minecraft's YouTube channel, gotten an email, or seen a single message in my regular circles that it was happening. Googling now, there's indicators going back to October 2020, but again, third party launchers and inactivity. Still haven't gotten an email about it.</sup>

And what do I get in return?

Absolutely nothing but less privacy. [Read the FAQ](https://help.minecraft.net/hc/en-us/articles/360050865492-Minecraft-Java-Edition-Account-Migration-FAQ): you're forced to use a Microsoft account and get little to nothing in return.

They promise to add new safety features, but in all honesty, they could've done this with the existing account system. There are a countless number of sites with non-SSO login who have 2FA, the feature they seem to flex to defend the decision. They're also allegedly building an account reporting system. If it's anything like Xbox used to be a few years ago, it'll be completely ineffective at taking out people, but exposes a brand new attack vector for persistent trolls if the link between MC accounts and Xbox accounts is easily accessible. 

Of course, a lot of the details are vague at this point in time, because Microsoft is as transparent as the layer between you and the core of the earth (read: not even remotely). Microsoft accounts linked to Minecraft, however, only has downsides so far, and any new features that could be added could've been added _without a second migration_ in under 10 years. Companies with substantially fewer developers [have done this better than Microsoft](https://among-us.fandom.com/wiki/Report_(account)). Astonishing, isn't it?

I'm an avid Linux user, and I'm extremely happy I get to dodge Windows 11, which more or less requires a Microsoft account. SSO [has some central security problems](https://security.stackexchange.com/a/20600/234774), and personally not trusting Microsoft, or Microsoft accounts in the wake of their new MS account push makes the situation seem a lot worse than it might be. Or I'm just mildly pissed about needing to tell Microsoft I don't want to use password-less login by downloading an app every time I log in. :rolling_eyes:

Now I just need to hope they don't decide to start migrating GitHub accounts to Microshit accounts.
