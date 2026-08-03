---
{
    "title": "The great font rant",
    "date": "2026-07-22T17:30:34+02:00",
    "summary": "Most websites pick shit fonts and I hate it",
    "type": "notes",
    "taxonomies": {
        "tags": ["html", "web-design", "fonts"]
    }
}
---

Earlier this year, I made the move to [disallow websites from setting fonts in Firefox](/til/firefox/fonts.md) (through changing the setting in firefox, I had nothing do do with its development, for the record). This was after stumbling into the option by accident - I've never seen it before, and I'm pretty sure it's new, but can't really guarantee that. Most websites force a default font, so I never bothered setting my own fonts. It's a fantastic toggle, and I will die on this hill, because most websites choose _awful_ fonts.

I have never had a particularly large investment in fonts. If a font is readable, it's good enough. I do still have fonts I prefer, and over time, these have become:

* Ubuntu (the font, not the OS; the OS is on the enshittification track, but that's a whole other aside)
* Source Code Pro/Sauce Code Pro (modified version of Source Code Pro with more icons for terminal use)

These are the fonts I set in most of my desktop operating systems. In editors, I only use the latter of the two, but still, these fonts get set as my defaults. This includes in Firefox and in my operating system settings. I landed on these fonts because they're readable to me. Ubuntu in particular also solves the problem of l and I being identical. If you struggle to tell which is the lower-case L and which is the upper-case i, your default font probably sucks.

The default fonts in firefox are what's used when no other fonts on a hard-coded font spec is available, if no fonts are specified, or of course if you disallow websites from specifying their own fonts. This website does not specify fonts. Most of the web does, and shouldn't be doing so.

I do not have a relation to a font being particularly pretty. I do have a relation to fonts being bad, and that's largely if I struggle to read them. This makes for a fun existence in a world where 99% of the web seems to have decided to fuck user choice in favour of using their particular flavour of preferred font. Fonts being used basically as another part of usually corporate identity rather than prioritising whether or not the fuck everyone can actually read your fucking font is why I made the move to flip the switch that prevents websites from using their own fonts. Far too many websites pick dogshit fonts because "it looks pretty" or whatever, while completely ignoring that I and l are fucking identical.

This, usually, is not a problem. lf I start a sentence with "If", it's probably an i and not an l. In the case of the previous sentence, it was an l. If you have one of the aforementioned dogshit fonts and you guessed upper-case i, you'll almost certainly struggle with this problem from time to time. This makes for a lot of fun with names. For literally fucking years, I misread someone's username as starting with an I, when it actually was a lower-case L. Or the other way around - I don't remember which way I fucked up anymore. The site in question (Stack Overflow) used one of the aforementioned dogshit fonts where I == l. At the time, I just gave up and used a userstyle to force a sane font selection.

Fonts being subjective, i.e. the design value they provide to the website, is one thing; the readability of said font is another. My recurring problem with I and l in dogshit fonts will not be universal, and it will not be the biggest font-related issue in existence either. Aside having -2.25 and -2.75 correction, my eyesight is fairly good, and I do not have dyslexia or similar. I don't think there exists any single font that actually takes every possible problem into account. That's why taking away the user agency to pick their own fonts that they know they don't struggle with is an outright evil.

In the defense of setting fonts, there are a few cases where it can be useful, though this is largely for non-text content. In this case, I count symbols and emoji as non-text content. [Nerd Fonts](https://github.com/ryanoasis/nerd-fonts) adds a whole bunch of symbols as something that's *technically* text from the perspective of the font, but for the sake of this discussion, it functionally isn't text. If you want to provide a more stable experience across operating systems for non-text content without requiring users to have specific fonts or fonts with specific capabilities (like the nerd font icon set), that's more justifiable. However, non-text content is also not read in the same way that text content is, so the legibility of the font doesn't come into as much play. Ugly or broken non-text characters shouldn't outright break readability. It might break how pretty the text looks, but that should always be secondary.

But even then, WebAIM has an article where [ambiguous fonts are discouraged](https://webaim.org/techniques/fonts/). They also mention I, l, and 1, because some fonts make all three virtually fucking identical unless you do pixel-level analysis. This is still broadly ignored in favour of whatever the fuck the font is supposed to communicate other than being readable. As far as I can tell, WCAG 2 doesn't bring up font faces, but WCAG 3 looks like it might. It at least has a mention of "font face" in a currently unused definition. Fingers crossed I guess.

In either case, forcing specific fonts on users is an awful practice that needs to fucking die in a fire.
