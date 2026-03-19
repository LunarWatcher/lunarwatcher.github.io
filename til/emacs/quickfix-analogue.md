# Vim quickfix in emacs

Emacs doesn't directly have an equivalent of Vim's quickfix window, but it does have `M-x grep-find`, which is pretty close.

It opens an xref buffer that can be edited directly to modify the matches. There's several things missing though, notably `:argdo`. Not sure if there's an analogue that gets close enough, but a few quick searches seem to indicate no, aside a plugin that was made specifically for this purpose and hasn't been touched in 8 years. There's always `rg --files-with-matches | xargs sed -i` as a fallback
