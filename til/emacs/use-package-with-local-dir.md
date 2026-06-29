---
{
    "title": "use-package from a local directory with a normally vc-loaded plugin",
    "date": "2026-06-29T00:13:57+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["emacs"]
    }
}
---

Use `:load-path` with the folder:
```lisp
(use-package nyaatree
  :vc (:url "https://codeberg.org/LunarWatcher/emacs-nyaatree.git"
            :rev :newest)
  :ensure t
  :load-path "/home/olivia/programming/emacs/emacs-nyaatree/"
  :config
  ;; as usual
)
```

Somewhat interestingly, this takes priority over `:vc`. `:ensure t` seems to still load the plugin from vc, but it still compiles and runs the local variant when `load-path` is present. This means that commenting out `:vc` but leaving `:ensure t` breaks in this particular case, since `nyaatree` isn't on melpa.

This also takes (in this case) nyaatree out of the `package-vc-upgrade` list. For my use, this means I'll just comment and uncomment a single `load-path` statement when I switch a VC package to a local package for development. I used to use `load-file` on a couple other plugins, and it worked fine with those because it didn't have any config, so I could just comment out the whole `use-package` without issues. That's not really an option here, because I have a lot of nyaatree config. ✨ The more you know ✨
