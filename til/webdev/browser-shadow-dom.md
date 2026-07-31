---
{
    "title": "Inspecting the browser shadow DOM (browser-specific HTML element internals)",
    "date": "2026-07-31T23:50:26+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["html", "firefox", "chrome"]
    }
}
---

Under the devtool settings, click:
* Chrome: "Show user agent shadow DOM"
* Firefox: "Show browser shadow DOM"

 The shadow DOM is used for the browser-native/default styles, and is for some reason hidden by default in the devtools. Enabling the setting that shows them is really useful. This can be used to derive pseudoelements, since the shadow DOM includes the definitions for the pseudoelements.

If you ever wonder where the `-moz-*` and `-webkit-*` pseudo-elements are defined, that's in the shadow DOM. These can also be used to customize at least a few built-in elements that otherwise don't appear to expose much customization in CSS. My use-case for this was styling a `<progress>` element, since styling them is not cross-browser. <abbr title="Using Kagi">Googling</abbr> the progress element pseudo-elements does work with a fair bit of effort, but finding it for all the browsers is a pain in the ass. Inspecting the shadow DOM manually in various browsers is a fair bit easier, at least for me.
