---
{
    "title": "Opening a commit message in an editor after writing a partial commit message with -m",
    "date": "2026-07-10T03:17:30+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["git"]
    }
}
---

If you ever write `git commit -m "..."` only to then realize you actually have enough to write that you should open it in an editor, but don't want to discard anything you've already written, use `-e`:
```bash
git commit -m "some message" -m "Some extra message if applicable" -e
```

This opens the editor, but with the contents of all the `-m`s pre-added to the temporary file the editor is opened on. 

