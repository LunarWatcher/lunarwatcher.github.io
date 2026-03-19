# Listing keybinds, variables, keys, etc.

Emacs has a disgusting (/pos) amount of facilities for infodumping the value of things, and the current state of things. Just a few include:

* `M-x describe-mode` (`<C-h>m`): prints all the modes in the buffers, and the keys associated with them
* `M-x describe-key` (`<C-h>k`): prints what's bound to a key, and documentation and other information about it. Note that in evil mode, this is dependent on the actual mode, so insert and normal can give two different results for the same key. Switching to normal mode before running the command can give different outputs than running it in insert mode. `M-x` instead of evil mode facilities, or using `<C-h>k` directly are decent options
* `M-x describe-variable` (`<C-h>v`): opens a search where all defined variables can be shown, with documentation if available. Really useful for debugging which fucking `*-indent-offset` a given mode does or doesn't use
* `M-x describe-command` (`<C-h>x`[^1]): dumps all the commands, including the keys they're bound to. Not actually sure if this is built-in, or if this is a vertico/consult/marginalia addition. Really hard to tell what's built-in.

There's several more that can be listed with `M-x describe-<tab>`

[^1]: Everything else is nice. Mode is `<C-h>m`, key is k, variable is v, but `:describe-key-briefly` took `<C-h>c`, so command got dumped to `x` for some reason 
