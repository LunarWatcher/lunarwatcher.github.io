---
{
    "title": "\"Security is more important than ever\"",
    "date": "2026-11-21T01:07:05+01:00",
    "summary": "Folfgirl complains about a currently commonly said phrase, because.",
    "type": "blog",
    "taxonomies": {
        "tags": ["security"]
    }
}
---

October and november sure have been some fun months /despair

I have been considering whether or not I want to write this blog post for a good while, largely because security is hard, at least when you start getting complex logic involved. I have both written and failed to spot vulnerabilities, though I have avoided more than I have written (I hope). The main upside is that I don't have hyperscale production-oriented software, so the consequence are much smaller.

Security is, and likely always will be, a moving target. Especially post-LLMs (though fuck LLMs with a cactus)

Over the last ~6 months or so, I have heard "security is more important than ever", and variants thereof, and it has now sufficiently annoyed me. Security isn't more important than ever - it's just much easier for consequences to manifest now.

## None of this is new

None of the current problems are new; that's why OWASP can exist. The propagation method for vulnerabilities has changed over the years, but in the grand scheme of things, the propagation methods are not important. Before sloperating with LLMs became wide-spread, Stack Overflow was a great source of a fair few vulnerabilities that became used in large amounts of projects[^stack-overflow-security-android][^stack-overflow-security-c++]. If it was on Stack Overflow, surely, it must surely be secure! (spoiler alert: it wasn't)

Now, LLMs are having a field day, not because the vulnerabilities they find necessarily are complicated[^complicated], but because lots of smol errors compound over time, and we have lots of monolithic codebases that are hard to properly check.

## Securityn't by design

A survey done by Secure Code Warrior in 2022 found that [86% of developers don't view security as a priority](https://www.securecodewarrior.com/news-articles/secure-code-warrior-survey-finds-86-of-developers-do-not-view-application-security-as-a-top-priority). If no one cares, are we really surprised?

As much as I loathe LLMs, they have enabled a lot of interest in at minimum performative security. I say performative, because although a lot of vulnerabilities are being surfaced by LLMs, they're still perfectly capable of producing vulnerability rates in excess of 50%[^ai-security-2026][^ai-security-2024].

Plenty of research has already showed that learning rate suffers while using LLMs, and that LLM use has long-term consequences for precisely learning and understanding[^ai-learning-1][^ai-learning-2]. Especially now that various standardized tests are showing decline in children's abilities, there's a _lot_ of research being poured into this in particular.

AI has become the new Stack Overflow in terms of producing insecure code, except at an unprecedented scale and no one can audit it because the history is thrown away immediately.

Among the developers that do care about security, research (though with a low sample size) found that pressure to ship features prevented a proper focus on security[^not-enough-time]. A corporate study with a larger (but still far from big) sample size found that a significant percentage of webapps were too big to properly test[^state-of-security-testing-2024].

If a majority of developers don't care, and a chunk of the rest are pressured out of properly securing applications to prioritize features, can we really be surprised that the internet is crumbling the second you get distributed scrutiny of the infrastructure that runs the entire internet? The only thing that changed before and after LLMs is that there's attackers with functionally unlimited patience and enough hallucinations that some of them are bound to hit something. Blindly launch infinite darts at a target with an unknown, but static and existing position, and some of them are bound to hit. Or a lot, in this case.

"Security is more important than ever" because there are a lot of threat actors that don't mind failing, and have been given a lot more capacity to run different probing attacks in parallel against a much greater number of  targets. The consequences haven't changed, and the importance hasn't changed, but ignoring it because that one feature needs to get out by XX.YY date or the shareholders will be pissed is now much more likely to be hit by one of many agents that are sent at the system. The consequences for people who potentially have their data compromised in these attacks haven't changed either.

There were such attackers before, but nowhere near as many, and certainly nowhere near as many operations that were able to keep a consistent probing volume going 24/7. Or said much less charitably, the only thing that has changed is that the attack likelyhood has gone up enough that it's the shareholders' problem, so now, security important.

I'll happily argue that what we're seeing is decades worth of tech debt being punished hard. With the exception of [emudhra](https://emudhra.we-have-a-problem.com/) who somehow fumbled certificate generation, a lot of the ongoing incidents are caused by tech debt that hasn't been given enough resources or interest to be looked at. Had the same amount of time and interest (and time allowance in the case of the for-profit industry) gone into letting people re-review, rewrite, and improve code, the exact same flood of vulnerabilities would be happening. The reason LLMs are considered the cause of the current wave of vulnerability reporting isn't because the LLM itself is special - it's because security is a field that doesn't get enough investment, and devs broadly don't want to or aren't given time to properly address tech debt and security issues.

I am several tangents deep at this point, but this really is a matter of dependency cultures as well; back in the good 'ol days of "audit everything", you might've had more consumers actually take a look at what it is they're changing. Unfortunately, this has been considered gruntwork, and was automated away by dependabot in the hellscape that is the modern dependency system. Auditing is easier when you have one reverse proxy, one or a couple operating systems to support both deployments and dev machines, and a handful of specific libraries. When you have 2000 npm dependencies, half of them update weekly, and a bunch of them have breaking changes every year, I agree that auditing becomes unachievable.

We have systematically built ecosystems built on dependency setups that are theoretically auditable, but functionally cannot be and in practice aren't as a result. LLMs aside, this day (or time period, rather) was bound to come sooner or later. The "theoretically auditable" comes from a chain of arguments about open-source; it's open-source, therefore, anyone can read the code, and therefore, it's constantly audited and more secure. This may be true of parts of open-source, especially new additions, but older legacy parts of systems that haven't been touched [since like 2002](https://github.com/php/php-src/blob/0f65280cb5118d8c1a85db6626f7be365f3d1b26/ext/standard/http_fopen_wrapper.c#L94)? I do find it hard to believe that lots of auditing of that code has happened, and no one looked at the char comparison as a red flag. Auditable in theory, but it's always someone else doing the auditing, to the point where the someone else becomes hypothetical.

The true shame here is that with this newfound interest in security, it's being outsourced to slop machines rather than sourcing in a large(r) number of people who could learn from these vulnerabilities, and who could've built a future for software development that's actually built on an increased awareness of security, and increased corporate willingness to spend time on security. Actual potential for learning is being wasted on the "novelty" of a slop machine doing the work.

"Security is more important than ever", as long as the whole not caring bit doesn't actually change. AI is the new Stack Overflow for false appeal to autority on whether or not code is secure, and I'm sure the companies who knowingly or unknowingly gamble on this will learn the hard way why that was a bad idea some day. When that does happen some day (assuming ClosedAI doesn't give the nuclear launch codes to its psychotic LLM and gets us all killed first), it's not the companies we should be sympathizing with; it's the users who have their data leaked who will be the victims of the ongoing sloppification of software security. "Security is more important than ever" if you don't care about the consequences for the people affected by a breach. It's as important as it always has been otherwise.

[^complicated]: Some of them are complicated, but most of them aren't. The [ssh vulnerability in musl without PAM](https://sshhole.com/) that resulted in the password being ignored could've been caught by testing one more sufficiently long string.

[^stack-overflow-security-android]: F. Fischer et al., "Stack Overflow Considered Harmful? The Impact of Copy&Paste on Android Application Security," 2017 IEEE Symposium on Security and Privacy (SP), San Jose, CA, USA, 2017, pp. 121-136. doi: <https://doi.org/10.1109/SP.2017.31>
[^stack-overflow-security-c++]: M. Verdi, A. Sami, J. Akhondali, F. Khomh, G. Uddin, and A. K. Motlagh, "An Empirical Study of C++ Vulnerabilities in Crowd-Sourced Code Examples", 2019, arXiv. doi: <https://doi.org/10.48550/ARXIV.1910.01321>
[^ai-security-2026]: S. G. Morkonda, M. Selim, and H. Assal, "Security of LLM-generated Code: A Comparative Analysis", 2026, arXiv. doi: <https://doi.org/10.48550/ARXIV.2605.23091>
[^ai-security-2024]: N. Tihanyi, T. Bisztray, M. A. Ferrag, R. Jain, and L. C. Cordeiro, "How secure is AI-generated code: a large-scale comparison of large language models", Empir Software Eng, vol. 30, no. 2, Dec. 2024, doi: <https://doi.org/10.1007/s10664-024-10590-1>

[^ai-learning-1]: N. Kosmyna et al., "Your Brain on ChatGPT: Accumulation of Cognitive Debt when Using an AI Assistant for Essay Writing Task", 2025, arXiv. doi: <https://doi.org/10.48550/ARXIV.2506.08872>
[^ai-learning-2]: M. Caosun and S. Aral, "The Augmentation Trap: AI Productivity and the Cost of Cognitive Offloading", 2026, arXiv. doi: <https://doi.org/10.48550/ARXIV.2604.03501>

[^not-enough-time]: R. Sammak, A. L. Rotthaler, H. S. Ramulu, D. Wermke, and Y. Acar, "Developers' Approaches to Software Supply Chain Security: An Interview Study", Proceedings of the 2024 Workshop on Software Supply Chain Offensive Research and Ecosystem Defenses. ACM, pp. 56–66, Nov. 19, 2023. doi: <https://doi.org/10.1145/3689944.3696160>

[^state-of-security-testing-2024]: <https://www.cycognito.com/documents/reports/CyCognito-State-of-Web-Application-Seucirty-Testing-2024.pdf>
