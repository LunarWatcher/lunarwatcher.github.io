# Defining custom commands in emacs

Emacs commands are `(interactive)` functions:
```
(defun some-command()
  (interactive)
)
```

Note that interactive can also take optional arguments for inputs: https://www.gnu.org/software/emacs/manual/html_node/elisp/Interactive-Codes.html

Might make a shorthand TIL in the future for these, but haven't needed them yet. 
