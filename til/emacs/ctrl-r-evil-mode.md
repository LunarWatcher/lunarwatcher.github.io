---
{
    "title": "Ctrl-R does not work in evil-mode search",
    "date": "2026-06-25T06:13:28+02:00",
    "type": "blog"
}
---

The default search for `/` is not `evil-search`, but isearch, which has a whole other set of keybinds. It also does not work great with regex in the same way vim does, but that's a separate entry ([Evil-search regex](evil-search-regex.md)). `evil-search` is functionally required for search to be vim-compatible, including how text is pasted. Evil-search is enabled with 

```lisp
(use-package evil
  ;; ...
  :config
  (evil-select-search-module 'evil-search-module 'evil-search)
  ;; ...
)
```
