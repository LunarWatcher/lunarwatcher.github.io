---
{
    "title": "HTML popovers are really cool",
    "date": "2026-08-04T01:35:10+02:00",
    "type": "notes",
    "taxonomies": {
        "tags": ["html", "webdev"]
    }
}
---

Over time, HTML and CSS has become increasingly powerful, but mostly the former. It used to be that you need all kinds of `<div>` nesting, but now, you can do it in precisely two lines of HTML:

```html
<button popovertarget="use-html-popover-demo">Text</button>
<span id="use-html-popover-demo" popover>boo!</span>
```

> <button popovertarget="use-html-popover-demo">Click me!</button>
> <span id="use-html-popover-demo" popover>boo!</span>

Want to have it show up near where you clicked? One line of CSS:

```html
<button popovertarget="use-html-popover-demo-position">Text</button>
<span id="use-html-popover-demo-position" style="position-area: bottom" popover>boo!</span>
```

> <button popovertarget="use-html-popover-demo-position">Click me!</button>
> <span id="use-html-popover-demo-position" style="position-area: bottom" popover>boo!</span>

... Well, technically 3 if you do proper CSS. `[popover]` with a class, then the line to set position-area, and a bracket line, but still one line of functional CSS.

With a bit more code, you can do fancy things <button class="text" popovertarget="inline-demo">inside text</button> without requiring a single but of JS, nor a single redundant `<div>`[^1] with `position: absolute` or whatever webdevs were stuck doing before the popover API.

<div id="inline-demo" class="bottom" popover>

Most of my use for the inline variant in particular is essentially `<abbr>` but mobile friendly. Technically, `<abbr>` would be mildly abused the way I've occasionally used it, so will need to go back and revisit at some point.

(I would normally use footnotes here, which violet generates markup for, but this is a sneaky demo, so deal with it :p)

</div>

The minimal code required for a variant of this:
```html
<style>
button.text {
    background: none;
    border: none;
    padding: 0px;
    text-decoration: underline dotted;
    user-select: text;
    font-size: 1rem;
}

button.text:hover {
    color: black;
    font-weight: bold;
}

[popover].bottom {
    position-area: bottom;
}
</style>

<p>Text <button class="text" popovertarget="inline-demo">button inside text</button> more text</p>

<p id="inline-demo" class="bottom" popover>Text omitted for brevity</p>
```


[^1]: There's technically one div that could be argued to be redundant in this case, since I didn't want to use `<code>` manually with violet to write `<abbr>`. The div lets violet render the contents of the popover, while still being a trivial popover, so it's technically not redundant. 
