---
{
    "title": "Setting indent width \"portably\" in emacs",
    "date": "2026-07-27T23:49:47+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["emacs"]
    }
}
---

I have come to rather like emacs, but my single biggest frustration is setting indent widths. Every single mode does things slightly differently and has slightly different names for everything, because fuck you.

This means that if you want to set the indent width "portably" in emacs, you need to... set all of them. In my case, that means
```elisp
(defun livi-indent-width(size)
  "Utility for setting the indent width.
This function wraps all the portable options for standard emacs and evil mode,
and additionally sets the indent spec for every single language I use.
This will likely waste a few bytes of RAM per buffer, but it makes
my life a lot easier.

This function could be avoided if there just was a single fucking setting for
defining the indent width rather than like 8001"
  (setq-local tab-width size)
  (setq-local evil-shift-width size)

  (setq-local c-basic-offset size)
  (setq-local c-indent-level size)
  (setq-local cmake-tab-width size)
  (setq-local js-indent-level size)
  (setq-local lua-indent-level size)
  (setq-local python-indent-offset size)
  (setq-local typescript-indent-level size)
  (setq-local yaml-indent-offset size)
)
```

Everything is set locally and hardcoded to specific buffers. I do this for one very specific reason: at the cost of hooks, my interface to indent levels is static.

This approach is not mutually exclusive with setting global defaults without using a hook, but this only makes sense if every size is indentical. If you, for example, default all the indents to 4, but have `(setq-default typescript-indent-level 2)`, the tab width and evil-shift-width will differ.

For any buffer, there's at least 2 variables that need to be set (3 with evil mode): `tab-width` to control what `<Tab>` does, `evil-shift-width` to control the `<` and `>` operators, and some variable for the language. This means that having differing indent sizes necessitates a hook to set all three for any languages that differ from the defaults. In my experience, though some of these should derive from the `tab-width`, it seems like by the time the hooks run, those variables have been resolved. I may be doing something wrong here, but most of the solutions I find are "use the specific variables", because everything is a fucking soup.

The above function is also really nice for making a command that emulates `set sw=<size>` in vim without caring about the context.
```elisp
(evil-define-command livi-evil-shiftwidth(width)
    (interactive "<a>")
    (let (
          (target-indent (string-to-number width))
    )
      (if target-indent
          (livi-indent-width target-indent)
        (error "You must provide a number")
        )
      )
  )

(evil-ex-define-cmd "shiftwidth" #'livi-evil-shiftwidth)
```

I'm using `evil-define-command`, but non-evil users can replace that with `defun` and use another `interactive` arg for mostly the same functionality. This particular setup lets me use the shorthand `:shiftwidth 2` and just ✨ have it happen ✨ in all the files I have set up, which is fantastic.

Well, relatively speaking, needing to hard-code every single mode's indent variable in a function is disgusting and I hate it, but it work shaped.
