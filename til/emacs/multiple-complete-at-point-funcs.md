---
{
    "title": "Multiple capfs in emacs",
    "date": "2026-06-24T03:07:41+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": [ "emacs" ]
    }
}
---

TL;DR: you don't. 

Completion in emacs is primarily centered around interfaces that are exclusive. `completion-at-point-functions` is a list,  but eglot overrides it so only eglot is on the list. 

Even if you bypass this to add another provider, most actual frontends for completion assume each backend is exclusive. If a backend returns nothing, another is attempted. This means that the vim-like experience of just adding more stuff to the completion popup and only using one key for like code, snippets, and file paths in a single popup with a single key is, currently, unreachable.

There are attempts to make workarounds for this, including cape, which has `cape-capf-super`, and [the author actively discourages its use](https://github.com/minad/cape/discussions/154#discussioncomment-13365413). Company, another popular completion framework, has a similar setup, but exclusivity is the default, and only a few backends seem to work well together.

I'm not going to pretend to understand _why_ this is the case, but emacs seems to be suffering from years of many ways to do standard things, so convenience features like being able to complete multiple things at once do not appear to be implemented yet.

