---
title: The essential skill of debugging
layout: post
date: 19.02.20
---

I spend a lot of time on Stack Overflow, and every single day there's a lot of unresearched questions being posted. Research and basic debugging appears to be a skill that's undervalued, or for that matter, not used properly. Using a search engine and manual debugging efforts might even get you solutions faster than asking someone else.

Obviously, there are legitimate reasons *to ask* as well. But don't get me wrong; the point of this post isn't saying "don't ask other people, it's bad". 

This is also not limited specifically to Stack Overflow, or programming in general for that matter: if there is an error, you can likely debug it. Errors usually don't exist to confuse users. Note that this is usually: there are some extremely vague error descriptions in some cases. 

To start off, here are a couple base principles: 

1. You're most likely not the first one to encounter a specific issue.

    Even if it's not the exact answer to your issue, being able to apply generalized problems to your current problem is **essential** in programming. If you can't generalize problem solving, you're going to have a hard time when you start coding actual stuff.
    
2. "But that doesn't answer my problem exactly!" is usually false.

    Programming-related solutions are usually relative to a specific source, but your source isn't the same. The cause can be identical (example: NullPointerException. Something is null, but where it happens in your code isn't identical to where in the code of a different project). Like I said in the first point, applying this is key.
    
    Outside programming, it's usually tricker. Error messages are vaguer (I.e. "Oops, something went wrong"), and the only thing you have is that message in some cases. Other times, you also have an error code. What you have available also defines how you research, which I'll get back to later.
    
3. There are unsolvable problems - but there are usually workarounds

    Not every problem has a solution, and some times you might need to abandon something because of it. If there are no workarounds and the only way to fix it is depending on a 3rd party patch, you can't fix it. Then you either have to go for an alternative. If there are no alternatives, no workarounds, no access to the problematic source, and/or no easy way to fix it, then there's obviously no to fix it.
    
4. The environment matters

    Versions of stuff used (i.e. browsers, language standards, plugins, runtimes, operating systems, tools, libraries, program version, you name it!), along with the existance of non-standard features (i.e. a browser plugin if it's a website issue) matters and can affect results. A browser plugin could theoretically create problems *for you* that no one else has if it's a web issue.
    
    You could also be using incompatible versions of a library with the version of a programming language or operating system, or use an OS or something else that's entirely incompatible with a third party tool or library.
    
---

With that in mind, let's move on to the next part: the actual problem solving.

Generally, there are steps:

1. Find the error message

    For an instance, this can be your program crashing, a visible error message, or something else. **Note that these may some times contain codes**. An example of this is if Windows crashes: it usually contains a code or some other way. If it's a compiler error, you'll also find the exact cause a lot easier. 
    
    How you get it varies a lot, depending on what you're doing.
    
    If the issue is related to programming, you'll find the error in the console. Otherwise, you'll likely see it directly.
    If you're coding on a platform such as Android, note that the "Unfortunately, <app name> has stopped" **is not** the error message you're looking for. Look in the console: with coding you're looking for stacktraces and other debugging hints. 
    
    Some programming languages are harder to debug than others, and C++ is, in my opinion, one of them. There are, for an instance, no stacktraces by default. Other languages, like Java, have these built in by default and you will have a stacktrace without much extra effort.
    
    How much effort this step will take depends a lot on what language you're using, or alternatively where you're seeing the error message.
    
2. Reproduction (some times optional)
    You know what, now find where: check what's affected. Use a different OS, a different browser, a different version of the language or a different compiler version. Basically, try different environments and see if it's an issue because of the environment, or if it's a possibly global issue. 
    
    
    If it's an environment issue, that also narrows it down. You'll also be able to tell what is affected. Depending on what it is, if using a different environment fixed it, you don't need to go any further, but this is mainly if you're a user and not a developer. If you're a developer, there are more steps.
    
    This is also useful to find what specifically triggers it, which is especially useful if you have any kind of input to process. But depending on what the issue is, reproducing it may not be something you need to invest time in, especially if this is during development and you have a concrete issue. 
    
3. Research

    You have what and where; now you need why. From here, you can do one of two things. If you know what the error is, no problem! Fix it, use a workaround, whatever you feel like. 
    
    Otherwise, you have to do research to find it.
    
    First of all, and I cannot stress this enough, **do not use Bing**. It doesn't produce nearly as good results on even a basic error message as Google or DuckDuckGo. Even a basic error such as a cryptic signup error on Spotify gave 4 irrelevant hits on Bing (I used Edge to see if it was a browser issue, not relevant), and a ton of relevant hits on Google. I generally use DuckDuckGo first, and fall back to Google/Startpage if I can't find anything there. TL;DR: search engines matter.

    It's quite simple from here: search for the biggest text you can without adding case-specific issues. If you have a stacktrace, copy-pasting the exception name, along with the message usually helps. 
    
    i. [Rubber duck debugging](https://en.wikipedia.org/wiki/Rubber_duck_debugging)

        This is mainly useful for coders. Read through the code, and say what each line of code does out loud. 
        
        Something I personally do is actually opening the question box on SO, mainly because it's somewhere to type. I find the minimal code necessary to reproduce it, along with explaining what the code does in the question. Surprisingly often, that makes me see what I did wrong, and I can easily patch it from there. 
        
        There are a ton of ways to do rubber duck debugging. There are also tools for it if you want to type it. I also have to mention Emacs and the psychotherapist here, which can be used as a form of rubber duck debugger. I bet there's plugins for other IDE's or tools as well that provide similar functionality. 
        
4. The next step(s)

    From the previous steps, you've gotten what the error is, along with what affects it and where it happens. Step three should give you the why, and through that the ability to fix, bypass, or otherwise solve the issue. If, however, it doesn't, you're at the "when all else fails" point. 
    
    I personally can spend a couple days on research and even research more while writing a question on Stack Overflow (or somewhere else in the Stack Exchange network if it's not programming-related, or for that matter in chat). Some times you do miss stuff, but as you learn how to debug more and more, you reduce that significantly. But generally, if you find anything similar to your issue, try it. 
    
    The time it takes to actually find the stuff you need varies a lot. Some times it can take 10 minutes, other times it can take 10 hours. 

---

# Applying general answers

Something I've noticed a lot with duplicates is the OP arguing with "but that doesn't look anything like my question". The same exceptions usually have the same cause, which makes them duplicates. There are some exceptions to this, and this mainly applies where you throw in libraries that're the cause instead. But duplicates aren't really the point.

General answers, whether it's on SO, SE, or anywhere else, shows you *why*. Using a NullPointerException as an example: the general answer says you're trying to do something with a null instance (although this is specifically Java, you'll hopefully still get the point). *Where* in the code is a separate question, but from step 1 you have the stacktrace pointing to the issue. Now that you know both what the cause is and where it is, you can take steps to patch your code and fix it.


# General note

While this is mainly targeted at programming, this can generally be applied to a lot more. And while I do mention SO and SE a lot, you obviously don't need to have anything to do with either. If you eventually get stuck and end up on step 4 without an answer, which site you ask on, or whether you ask in real life or online, is completely irrelevant. 

# Coding: Grabbing stacktraces or other debugging info

This is far too broad for me to cover accurately, as there are a ton of languages and a ton of unique ways to do this. Fortunately, there's a bunch of resources out there for various languages that can help if you don't know how to get the info you need. There's also the option of using a debugger rather than stacktraces, etc. 

**TL;DR:** Find whatever debugging info system your language uses for step one.

# Try everything

If you can't find a solution that works, try different solutions. There's a lot of answers for a lot of different stuff around the internet, and if you know how to use it, you're technically able to fix anything. Some solutions work, others don't. And there's only one way to find out what does.
