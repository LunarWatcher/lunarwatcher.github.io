---
title: "Long-standing WSL bug megathread"
date: 2025-06-28T23:26:27+02:00
toc: true
tags:
- wsl
---

I'm normally a regular Linux girl, but the rest of the world unfortunately runs on forced Windows where WSL is the only way to work properly. 

* Keyboard translation doesn't work for custom layouts
    * https://github.com/microsoft/wslg/issues/173 [2021]- initial report
        * Also https://github.com/microsoft/wslg/issues/1184
    * https://github.com/microsoft/wslg/pull/1046 - attempt to fix, never followed up on by Microsoft
* Windows interop functionally does not work due to severe performance problems on `/mnt`
    * https://github.com/microsoft/WSL/issues/4197 [2019]
        * This problem works in both directions, so everything either needs to be in WSL, or everything needs to be in windows. You cannot mix environments due to how fucking absurd the performance drops are 
* 100% CPU while idle
    * https://github.com/microsoft/WSL/issues/5285 [2020]
        * There's another one somewhere that I believe predates this, that was much bigger. Haven't looked at that bug in ages though, so I never stored it anywhere[^1]


[^1]: I desperately need to get better at bookmarking things
