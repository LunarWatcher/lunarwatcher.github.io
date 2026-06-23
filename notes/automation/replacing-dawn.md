---
{
    "title": "Replacing dawn: a theoretical inja-based templating system",
    "type": "notes",
    "date": "2026-06-23T03:00:00+02:00",
    "taxonomies": {
        "tags": [ "automation", "cpp", "templating" ]
    }
}
---

> [!info]
>
> For context, [dawn is a vim plugin I wrote that generates project structures](https://codeberg.org/LunarWatcher/dawn). It got axed after Vim decided AI slop was a great idea, and I migrated away from Vim. I'm sure I'll write a rant about that later (if I haven't already)

For a while, I've been trying to decide for or against writing a dawn replacement. TL;DR: I voted against. This still explains the general idea. I may still unabandon it in the future as well. The rest of this page is copied straight from my notes.

---

Dawn had a few major limitations in that its features were implemented as a tiny "templating" language that more closely resembles `envsubst` with extra steps.

The reason I struggle with this now is that the app has expanded into something more for cross-project automation, with an ability to extend existing files, and that's a whole other can of worms. That could just as easily be replaced with a snippet or a snippet reference archive hosted on CB/GH.

If instead of doing that, I use [inja](https://pantor.github.io/inja/), that solves a few initialization problems. Pure copypasta endeavours like setting up CI pipelines, setting up issue templates to make Codeberg the main repo, and other similar actions could be boiled down to a single command

## Implementation details

### Bash?

I think I've opted against bash, on the grounds that it isn't capable enough. `envsubst` is fairly cheap to implement, but the logic required to extend the templates otherwise would be too complicated. 

I also suspect at least some templates are going to have to be copied rather than directly created, notably for pipelines. At that point, it's basically a spicy copy operation.

### Integration location

I'm very undecided here. It is a candidate for inclusion in umbra, but it's also a candidate for a standalone tool, considering the size of the inja stdlib extensions required to make this work. There's also still going to be finite limits to this; a `CONTRIBUTING.md` would likely end up with a `{% include "AI ban.md" %}` or something to that effect, which is going to be a whole thing if multiple template repos are supported (which I think I have a case for). 

> [!info]
> 
> [Umbra](https://codeberg.org/LunarWatcher/umbra) is a utility tool I wrote that has utilities (shock), some automation, and some replacements for other tools that were too much of a pain to use. It's designed to allow single commands that use environment context to reduce the amount of manual input required.
>
> See the docs if you're interested. It only has 4 modules right now, but I use three of those modules regularly, especially at work where one umbra command replaces multiple commands and occasionally manual logins. It's one of my most frequently used self-made projects (disregarding libraries).

### Theoretical interface

```bash
umbra [t|template] "template name"
```
Each template can optionally contain a frontmatter:
```json
---
{
    "k": "v"
}
---
```

The frontmatter would be used for config options rather than data used in the generation. For example:

* Whether or not a template is copied or directly results in a file
* Additional metadata if the file is actually a standin for a project structure. Something like
  ```json
  {
      "template": {
          "directory": "./cpp-cmake/",
          ...
      }
  }
  ```

In theory, we could use a template file as a redirect to a template folder, which that file being excluded from copying.

### Filename translation

Dawn declared filename translations in its config file, because it was convenient to do it like that. I have become aware of a few other ways to do it though, largely thanks to the clusterfuck that is react routers.

Certain react routers use filesystem paths as variables, because idk, fuck you. That's one of the things I explicitly avoided when designing violet, because I didn't want the filesystem paths to convey non-absolute information. It's also something I'll opt out of here.

The main question then becomes, which frontmatter does it live in? For single files, it's obviously 1:1, but in the case of project structures, should the metafile contain the translation, or should each individual file also have a frontmatter that contains that info?

I lean towards every file containing it, since each file likely has to be loaded into memory for manual copying anyway. Though there's no immediate examples of it now, projects could still have template information that's stored per-file, which means every file has to be checked for and stripped of its frontmatter before it's copied. That means manual copying, and that strengthens the case for keeping it in the frontmatter. 

One complication is the parsing of it; should those strings be run through inja as well, or should a lighter version be used? It'll be hard to limit the contents of the strings if the full inja engine is used


## Main challenge: Limited applications

I don't think this is worth spending time on. Though it's really convenient, it's maintenance overhead and lots of problems to solve for a very specific narrow problem that can be solved with a lot of `cp` calls (or maybe `unison`; not `rsync` though, [rsync is AI slop now](https://github.com/RsyncProject/rsync/issues/92)) or otherwise copying files from my other repos. 

Creating files is convenient, especially since I have a lot of files that are or start out fairly standard across multiple projects, but some of them would also benefit from being kept up to date. Keeping the files up-to-date is a whole other problem though, and attempting to implement it would explode the complexity of the project. It's possibly the only way this project has general use. 


## Conclusion

Having a tool like this does not replace the fact that my editor (emacs at the time of writing) supports built-in snippets, which I still need to get around to configuring, and I've never made enough repos to justify the time consumption. These replace a fair bit of the file content bits of templating, which makes the need to support `"copy": true` (or something to that effect) moot. Even before implementation, one of the main use-cases evaporates. Well, kinda - IIRC, the templates in emacs are also fairly weak, but it's much easier to just set up a bunch of them.

It is an interesting application of templating though. If I didn't already have [violet](https://codeberg.org/LunarWatcher/violet), I probably would've jumped on it anyway just for the sake of fucking a round with templates in a real-world project.

Will probably revisit if I find additional applications, or at least something that justifies creating it as a library. At this time, I don't think I will, though. Also doesn't help that I've got better at setting up projects in general, since I kinda vaguely know what I'm doing now :3


