---
{
    "title": "Defining custom commands in emacs",
    "date": "2026-06-25T06:13:28+02:00",
    "type": "blog"
}
---

Emacs commands are `(interactive)` functions:
```lisp
(defun some-command()
  (interactive)
)
```

Note that interactive can also take optional arguments for inputs: https://www.gnu.org/software/emacs/manual/html_node/elisp/Interactive-Codes.html

Might make a shorthand TIL in the future for these, but haven't needed them yet. 
