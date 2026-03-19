# Loading emacs themes or plugins from version control

With emacs 30, `use-package` got an extension that allows for the use of version control:
```lisp
(use-package catgirl-theme
  :vc (:url "https://codeberg.org/LunarWatcher/catgirl.el.git"
            :rev :newest)
  :ensure t
)
```

Not sure if these can be upgraded with the same command as everything else, but there is `M-x package-vc-*` variants of the upgrade commands (`M-x package-vc-upgrade-all`) that do bump them as expected.

Note that the name passed to `use-package` matters a fair bit, as it's reused by `use-package` to determine which file is loaded. In this case, if `catgirl` was used as the package name, the theme would fail to load because the name of the file is `catgirl-theme.el`. 

