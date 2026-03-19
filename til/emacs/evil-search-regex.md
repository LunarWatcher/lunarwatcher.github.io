# Vim-compatible regex in evil-search

`evil-search`, by default, does not quite do vim-compatible regex. This largely means disabling the flags that enable non-escaped quotes and stuff like that. For `\v` et. al to work, `(setq evil-ex-search-vim-style-regexp t)` is required. This requires evil-search to be enabled, the method for which is described in [Ctrl-R does not work in evil mode search](ctrl-r-evil-mode.md).
