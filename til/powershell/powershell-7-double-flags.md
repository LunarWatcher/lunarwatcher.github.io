---
{
    "title": "Powershell 7 fails to parse flags with a double-shaped value",
    "type": "blog",
    "taxonomies": {
        "tags": [ "powershell", "microslop" ]
    },
    "date": "2026-06-26T05:05:59+02:00"
}
---
Microslop's steaming pile of shit shell, also known as Powershell, has introduced a very fun bug where specifically flags with a value assigned to a number fails to be identified as part of the flag it's actually part of. I checked this against 7.4.2, which is the version I can currently get my paws on with docker, because I'm not installing Microslop's malware on any of my linux boxes. The GitHub Actions runner where this failed originally runs 7.6.2, according to [the image software list](https://github.com/actions/runner-images/blob/e3d5c1312473fcb22b11bbb4926cd976044f27bc/images/windows/Windows2025-Readme.md?plain=1#L476). 

The consequence of this bug is that
```
-DCMAKE_POLICY_VERSION_MINIMUM=3.5
```

Is actually parsed as the TWO arguments, `["-DCMAKE_POLICY_VERSION_MINIMUM=3", ".5"]`, which broke my CMake build, since 3 is an illegal minimum policy version, and .5 is just trailing and a tiny warning at the start of a 1.1k line logfile. Full repro that this is, in fact, powershell's fault:

```powershell
PS /> function x($arg) { Write-Host "$arg" }
PS /> x -- -DCMAKE_POLICY_VERSION_MINIMUM=3.5
-DCMAKE_POLICY_VERSION_MINIMUM=3
```

This goes away with quoting:
```powershell
PS /> x -- -DCMAKE_POLICY_VERSION_MINIMUM="3.5"
-DCMAKE_POLICY_VERSION_MINIMUM=3.5
PS /> x -- "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
-DCMAKE_POLICY_VERSION_MINIMUM=3.5
```

In case it isn't obvious, the expected result *gestures broadly* everywhere fucking else for several fucking decades is for it to be parsed as one item; `["-DCMAKE_POLICY_VERSION_MINIMUM=3.5"]`

Lesson learned:

* Avoid powershell at all cost. Cmd should still handle this use-case fine
* If avoiding powershell is not an option, all non-string types must be quoted in every argument

Microslop strikes again
