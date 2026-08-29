---
{
    "title": "Test output is hard",
    "date": "2026-08-29T21:13:08+02:00",
    "type": "notes",
    "taxonomies": {
        "tags": ["tests"]
    }
}
---

Back in february, I [write my own test reporter for catch2](https://github.com/LunarWatcher/stc/commit/d2ff2243e9e086f9408311a2843605bb42d18161) after the non-verbosity of the default reporter got annoying. The idea was to explicitly see where one test started and one test ended - and this is still useful (to me). But it got a bit more involved once magpie got an HTTP/1.1 implementation.

To support reusing tests, I did some cursed macro shit to make the entire existing integration test suite run on both HTTP/1.1 and HTTP/2, which meant a functional doubling in the amount of tests ran, but also the output. While debugging issues with my HTTP/1.1 parser that caused some of these tests to fail, I ran into the fantastic problem of having too much output.

## Tentative conclusions from the custom test reporter

The test reporter itself is a success in the sense that all the goals I wanted to achieve were achieved.

It shows the precise transitions between tests, and makes it easy to see what's running, and whether anything has stalled. One of the notable problems I wanted to solve was the inability to see which test resulted in execution hanging, which was a huge problem I had while testing [magpie](https://codeberg.org/LunarWatcher/magpie)[^2]. Basically, errors in the framework caused the HTTP client to hang, because the server thought the client was done, and the client disagreed. It was really difficult to see which exact test caused this, because I wasn't sure which test was running.

I did solve this, and at the time, it was solved well. The solution simply did not scale well with an increased number of tests, and those tests having significant amounts of output. Tests that fail, and do so early, get buried under all the tests that passed after the early tests failed.

In parallel, I've had a similar issue at work: the test suite is so fucking big that if many or all of them have to execute[^3], and produce so much output it causes problems *with the scrollback history of the terminal*. I have it set to the default of 10k lines, and if a test fails early, good fucking luck, it's gone.

My tentative conclusion is that the (non-TUI) terminal is unsuited for test reporting in interactive environments, because it puts errors far outside reach, or potentially makes it outright unavailable.

## To GUI or not to GUI

A large part of the reason I'm writing this is because I've hit a wall on how far I can go with a non-TUI terminal. I could write a TUI reporter, but unfortunately, the TUI library I used to use has turned to AI slop.

This would be an interesting solution to be fair, but also a mildly annoying one. I have used not strictly test tools, but multi-workspace tools that just default-apply a TUI to lots of commands. It's so much worse to interact with for most normal use, since it spawns a TUI that you have to explicitly tell to fuck off before you can rerun stuff. This could be solved my making it easy to rerun from the TUI, but now you go from having a test reporting system to a whole test framework or test executor, depending on the setup.

The other obvious alternative is to use the GUI library that's available on basically every modern system: the humble browser. In the case of catch2, using the JSON reporter (possibly with modifications to deal with `printf` use) would allow an entire report to be assembled to be viewed on-demand. I do find this approach useful - it's a strategy gradle implements, but it's a feature I almost never use[^1].

TUIs in general are really nice when you find a TUI implementation that works really well, combined with a terminal emulator that's good both in general, and with the specific implementation. But the amount of limitations and quirks of a TUI means GUIs are generally better. Implementing a full GUI is absolutely overkill for this problem, especially since it's so data-driven. It _would_ allow for fairly easy file watching though, so the GUI can refresh as the tests run. I have already experimented with a variant of this with [umbra](https://codeberg.org/LunarWatcher/umbra), where I have `umbra w` run `make test` for me. A simple poll-based read of the last modified date should be enough to implement updates.

I do like the principle with TUIs though, because it centralizes the command execution and command display. I use the terminal for an awful lot of things, and it is really nice to just be able to work with it directly. I also often end up with single tabs or similar dedicated to running one command, so locking a tab isn't per se a problem, as long as it offers an easy way to rerun things.

## All paths lead to command orchestration

The system I just described ends up being one flavour of command orchestration with output parsing. This really is a tangent, but I do find it fascinating how many problems I've had that boil down to command orchestration and automation.

Command pipelines is a problem that has already been solved fairly well by `make` et. al, but _long-running_ command pipelines, and command pipelines that require parsing, is still an unsolved problem. As far as I know anyway.

I did stumble into [zellij](https://github.com/zellij-org/zellij) earlier this year, a terminal multiplexer that I mostly use for its ability to write layouts. The layouts can be used to spawn parallel pipelines, though sequential pipelines is planned and not implemented at the time of writing. Being able to spawn commands only when required does alleviate this problem, but it does this by dumping the check onto the user. It technically works, but could be better.

I feel like this is going to be a slippery slope into implementing my own terminal multiplexer/terminal pipeline/command executor and parser system[^4]. A fork of ftxui would put me in a position to do this, in theory.

[^1]: To be clear, I don't mean the strategy itself, I mean the feature in gradle. The test reports are fine, I guess, but they're also per gradle module. This wouldn't be an issue for my monolith use in C++. 
[^2]: I'm not sure if magpie was _the_ library that caused the test reporter
[^3]: The tests are cached at a module level, so if a module isn't directly or indirectly affected by any given update, the tests may not necessarily have to run again. That said, the tests are run with gradle, and gradle's cache is absolutely fucking atrocious, so it often decides to run them anyway even though it doesn't need to.
[^4]: I could technically implement this as a zellij plugin, but rust fucking sucks to work with. The borrow checker in particular can go fuck itself with a cactus
