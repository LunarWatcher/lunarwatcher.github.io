---
title: "Vim and tree-sitter: the Neovim detail that makes a patchless Vim implementation viable"
date: 2021-06-26T17:24:41+02:00
tags: ["vim", "neovim", "treesitter"]
---

Tree-sitter, on paper, is fancy. Near universal highlighting in flexible queries that seems to be a lot more fancy than Vim's standard highlighting. Neovim's implementation is even set up in a way that can be customized further by having built-in highlighting definitions, and tree-sitter highlighting. While not always necessary, it provides the option for extending with additional tree-sitter types, all of which can make some colorschemes more vibrant, without actually breaking it.

When I looked into what it was when Neovim got it, I didn't look into all the implementation details - that's what this article is going to cover. It was still mildly disappointing: didn't seem to work, it relied on an external plugin... The entire thing was confusing, to say the least.

Of course, it being confusing is a matter of opinion and background. However, the fact that it is a plugin is how [a Vim implementation is viable][vim-acacia].

There's a short version of this in the documentation of the (at the time of writing, work in progress) plugin, but the fact that Neovim allows a plugin to use tree-sitter is the reason it's possible to do in Vim with a bit of effort.

The detail I mentioned in the title of this article is in how Neovim implemented tree-sitter. In fact, it didn't implement tree-sitter. Neovim itself doesn't use tree-sitter for syntax highlighting. The update that introduced tree-sitter exposed Lua bindings _for_ tree-sitter, meaning the plugin uses the API to access tree-sitter.

The subtle difference here is that the plugin uses [Lua functions for range highlighting](https://github.com/nvim-treesitter/nvim-treesitter/blob/ddc0f1b606472b6a1ab85ee9becfd4877507627d/lua/nvim-treesitter/ts_utils.lua#L164-L167), and that it uses a wrapper built into Neovim around tree-sitter. That's an important detail as well - wrapper around tree-sitter. Their Lua wrapper is just that: a [glorified wrapper][neovim-treesitter-comment] with no impact on the highlight features of treesitter, or any other features of tree-sitter. Additionally, tree-sitter [is open-source][tree-sitter] under a permissive license -- there's nothing preventing another implementation.

This tiny detail means that Neovim's implementation of tree-sitter isn't particularly unique - the only thing a fully external plugin can't do is expose a raw Vimscript API without installing the plugin first. All Neovim did is exposing a Lua API for tree-sitter. This does mean developers can easily use tree-sitter for other plugins, but it also means there's nothing particularly special about Neovim's tree-sitter interface.

In theory, this means that a tiny bit of code should be able to expose the API to a program that handles the queries, and feeds it back to Vim. Using built-in functions and leveraging async behavior on top of this is more than enough to implement tree-sitter in Vim without a single patch to Vim implementing tree-sitter.

And that's the theory behind implementing tree-sitter in a Vim plug -- now it's time to actually do it.

[vim-acacia]: https://github.com/LunarWatcher/Acacia/
[tree-sitter]: https://github.com/tree-sitter/tree-sitter
[neovim-treesitter-comment]: https://github.com/neovim/neovim/blob/master/src/nvim/lua/treesitter.c#L1-L6

