---
{
    "title": "Refsheet"
}
---

This page mostly exists for my own reference whenever I draw my character, since I otherwise end up going back to my last cannon piece and colourpick from it[^palettes]. It works, but it's tedious.

No proper ref sheet exists at this time either, and I'd imagine that would mostly be useful in communicating to other people, which is a need I usually don't have.

Is this list too hard to read? Try:

* [Without colours](refsheet.md?nocolour)
* [With colours](refsheet.md)

## Main colours

* Fur
  * Red fur: <span class="colour">#d52728</span>
  * Grey fur: <span class="colour">#818181</span>
  * Black fur accents: <span class="colour">#282828</span>
  * White fur accents: <span class="colour">#ffffff</span>
* Eye colour: <span class="colour">#ff8afc</span>
  * Eye ring (specifically used in my own style[^eyes]): <span class="colour">#c948c6</span>
* Hair
  * Hair colour: <span class="colour">#fde176</span>
  * Hair highlights: <span class="colour">#d16bfe</span>

## Standard accessory colours

* Porple: <span class="colour">#8700ff</span> (hair clips, bows)
* Black: <span class="colour">#2e2e2e</span>
* Dark porple: <span class="colour">#4e0094</span>
* Any of these main colours when matching makes sense:
  * Eye colour: <span class="colour">#ff8afc</span>
  * Hair highlights: <span class="colour">#d16bfe</span>

<script>
    if (new URLSearchParams(window.location.search).get("nocolour") == null) {
        const els = document.getElementsByClassName("colour");
        for (const el of els) {
            const colour = el.innerText;
            // Lots of magic math for the simple evaluation of whether a colour is dark or not.
            // I could specify which colour to use in the tag, but I don't want to and this is good enough
            let colourValue = colour.substring(1, 7);
            let r = parseInt(colourValue.substring(0, 2), 16);
            let g = parseInt(colourValue.substring(2, 4), 16);
            let b = parseInt(colourValue.substring(4, 6), 16);
            const whiteText = ((r * 0.299) + (g * 0.587) + (b * 0.114)) <= 186;
            el.style = `background-color: ${colour}; color: ${whiteText ? "white" : "black"}`;
        }
    }
</script>

[^palettes]: Palettes do also work, but I have a habit of not backing up my palette, so I make it, don't use it, and then time passes and something happens that makes me lose my palette. A list is nice as a backup anyway.
[^eyes]: While drawing #97 (current profile pic at the time of writing), I found out that eyes kinda work better if the outline matches the eye itself. Purely personal preference though, and I pasted the hex code here because I do plan to use it again
