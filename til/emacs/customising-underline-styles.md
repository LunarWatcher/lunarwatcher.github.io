---
{
    "title": "Customising underline styles in an emacs theme",
    "date": "2026-06-25T06:13:28+02:00",
    "type": "blog"
}
---
The underline property can also be a list that takes a `:style`:
```lisp
:underline (:style wave :color ,catgirl-yellow-highlight) 
```

Using `:underline t` would create a standard underline, the list variant allows customising both the type of underline and the colour, and probably more.
