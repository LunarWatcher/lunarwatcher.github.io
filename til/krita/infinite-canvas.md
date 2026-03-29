# Pseudo-infinite canvas in krita

When panning sufficiently far in any direction, a button appears on the corresponding border. Pressing this button extends the canvas in that direction. The button seems to appear when you cannot scroll further in that direction. This makes it much easier to expand canvases to fit whatever I'm working on, which is largely important to be able to use krita for notes.

Though it isn't quite a truly infinite canvas, it's probably as close as it gets without using slopware. Most of the open-source canvas applications I've found that do have infinite canvases are AI slop. Excalidraw, tldraw, and draw.io are [all AI slop](https://codeberg.org/small-hack/open-slopware#image-manipulation) at the time of writing.

A 18k\*13k canvas uses about a gig of RAM. Doubling to 33k\*13k only adds about 600MB, and there's a lot of writing and sketching that can be done in 421 million pixels. Does make saving real slow though. Not got a whole lot going on in the test canvas though (only about 4800x3344 px used), so can't currently test how adding layers with lots of content affects the RAM use.

Pretty convenient that krita comes in handy here too. Storing `.kra` files isn't as great though, but I have not yet made up my mind on if it makes sense to just export it as a .png and get it over with.

The test document is support for research into linux sockets and a supporting async architecture for a socket server ([raven](https://codeberg.org/LunarWatcher/raven/)), which unlike actual sketches would be nice to store in my obsidian vault. I do still store the files there, but obsidian won't be able to render them anywhere. I'm fine using an external tool to edit, but would be nice to quickly check something without needing an external tool.

That said, it wouldn't surprise me if obsidian failed to render it. 400 million pixels is a lot of content. 
