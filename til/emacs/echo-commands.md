# Echo commands in emacs

There's (at least[^1]) two separate commands analogous to `:echo` in vim in emacs.

## Built-in

The built-in option is `(message)`:
```lisp
(message "some message")
```

For arguments or string formatting, use `format`
```lisp
(message (format "%s" "arg"))
```

> [!note]
> This also appends to the `*Messages*` buffer, which may or may not be desirable. Might be better if you want to copy out the command afterwards.

## Evil mode

Evil mode has `evil-echo` that acts as `(message (format))`:
```lisp
(evil-echo "%s" "arg")
```

[^1]: There's probably more. `evil-echo` prints to the echo area but not to the `*Messages*` buffer, but at least for my use, these two are good enough.
