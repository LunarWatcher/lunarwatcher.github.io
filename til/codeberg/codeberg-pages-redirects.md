---
{
    "title": "Redirects on Codeberg Pages",
    "date": "2026-07-23T20:34:21+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["codeberg-pages"]
    }
}
---

Codeberg pages supports a special `_redirects` file compatible with netlify syntax that does (shock) redirects. This appears to be somewhat poorly documented, or at least I failed to find any mention of it on the corresponding doc page. It gets a [brief mention in the README](https://codeberg.org/git-pages/git-pages#features), but that's about it.

The syntax is at least fairly simple:
```
/source    /target
/source-2  https://target.example.com
```

... and `#` for comments.

Netlify's full syntax [supports a fair bit of stuff](https://docs.netlify.com/manage/routing/redirects/redirect-options/), and git-pages' README explicitly states that there are a few things it doesn't support. Placeholders is a bit of a loss for weirder generic redirects, but it isn't the worst loss. The rest of the unsupported features don't really appear to be that useful?

