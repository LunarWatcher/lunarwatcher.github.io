---
title: "Moving fzf matches to quickfix"
tags: ["vim", "fzf"]
published_date: 2025-02-23 22:47:24 +0100
---

I used to have a command that let me search my project for `TODO` and `FIXME` comments, and this was set up through fzf. This is not a particularly complex use-case of fzf, and in fact one I've replaced since. All it does is open a search prepopulated with matches for TODO or FIXME, which can then be refined further in an interactive mode. One of my main use-cases for this is to browse through TODOs in my projects. However, I haven't used it much due to one minor annoyance: every time I pick a match, fzf closes. I then have to reopen and scroll manually to the next one, and hope I remember how far up the list I got last time - and that I counted the number of `<up>`s correctly. This is by design, and most of the time, rather useful. When I go to browse for files, I don't need to retain state. If I'm just switching to another file, I probably know what it is, and need to search for it anyway. Fzf is absurdly fast on its own, and my code is usually on an NVMe with read speeds high enough that it'll still put fzf under load. Performance is functionally not a concern here, at least not at the scales I operate with.

It does get a bit more complex when working with multifile operations where the search is by line rather than file, however. For example, when refactoring, I may want to search for all occurrences of a function or variable or whatever across my entire project. For the sake of argument, let's say there are 15 such occurrences, spread across 15 files for added complexity. The trivial (though not "vim-approved" method) is to open each file one at a time, modify what needs to be modified, and move on. However, if you use fzf to identify the affected files, The workflow is:

1. Open fzf
2. Type search query
3. Hit enter
4. Refactor
5. Repeat steps 1-4 another 14 times

Steps 1-3 has to be excessively repeated. Step 4 can in some cases be automated, but this is heavily context-dependent. It's steps 1-3 that's annoying. Let's fix that. But first, a sidebar.

## TL;DR:
```vim
fun! s:Fzf2Quickfix(lines)
    call setqflist(map(copy(a:lines), '{"filename": v:val}'), "r")
    copen
endfun

command! -bang -nargs=* Search call fzf#vim#grep2(
        \ "rg --column --line-number --no-heading --color=always --smart-case -- ", 
        \ <q-args>,
        \ fzf#wrap({
        \   'options': ['--layout=reverse', '--bind=enter:select-all+accept'],
        \   'down': '30%',
        \   'sinklist': function('s:Fzf2Quickfix')
        \ }),
        \ <bang>0
        \ )
```

For usage notes and a few real-world examples, see the rest of the post.

## Why not use `:vimgrep`/`:grep`?

Performance, and perceived ease-of-use with a regex-capable fuzzy finder. Using fzf here just affects how you get things into the quickfix window, so everything else operating on the quickfix window works as it otherwise would. `:cfdo` and [other neat quickfix commands](https://bluz71.github.io/2019/03/11/find-replace-helpers-for-vim.html) are still an option, regardless of the ingest method.

One thing to note as well is just handling of certain regex characters. Consider, for example, the following:
```vim
" Note: Asserts `set grepprg=rg\ --vimgrep\ --smart-case`, but may be reproducible with the default grepprg as well
:grep some|pattern
```

This is incomplete, because Vim interprets it as being functionally equivalent to
```vim
:grep some
:pattern
```

So you escape the pipe:
```vim
:grep some\|pattern
```

But now, the pipe interpretation is moved to the shell, resulting in the following command being invoked:
```bash
rg --vimgrep --smart-case some|pattern
```

This is treated as a pipe, which means the shell will complain about not being able to find a command called `pattern`. If you add a second backslash, it works again. Single slash also works with:
```vim
:grep 'some\|pattern'
```

But this is not particularly intuitive, and makes regex far more clunky. This is true with `grepprg=rg`, and it's true without it. This gets more wonky if you make a wrapper `command` for it, as `<q-args>` causes weird escaping issues, resulting in only half the regex being respected. Just `<args>` acts as a pass-through, and exhibits the same problems seen here.

To be blunt, although fzf isn't strictly speaking needed here, Vim's outright shit handling of pipes in regex, compounded by weird escaping and terminal fuckery makes it orders of magnitude easier to work with fzf. Additionally, fzf has certain advantages for more interactive searches, and with more general setups than the example provided earlier, there's not much of a reason not to.

### When to use `:grep` (in my biased opinion)

Problems with `:grep` aside, most of these present themselves in interactive sessions. In commands, this isn't as much of a concern. If you fuck around sufficiently with a regex until it cooperates, and you know you regularly re-use that exact search string. One example of this is the TODO search command I described from earlier. Although it can be set up as an fzf multiline command, I can also set it up as a `grep` call:

```vim
command! -nargs=0 TODO silent grep '(TODO\|FIXME)(\(.*\))?:?'
```

The string is cursed, but I never have to look at it again, so it does not matter. However, for more interactive use-cases, this level of regex overcomplication is annoying to work with. Fzf does not have this problem, because it bypasses Vim, and sanely handles escapes for the sources. It also has the added benefit of showing real-time results before anything is added to quickfix, which just makes it slightly faster to iterate when working with interactive searches.

## Wrangling fzf

Let's define a generic `:Search` command that uses ripgrep, and that works with regex. This requires [some minor differences](https://github.com/junegunn/fzf.vim/issues/1081#issuecomment-668919785) to allow for real-time regex search, but this is fairly trivially doable. `fzf#vim#grep2` supports this, so that's the function we'll work with:
```vim
command! -bang -nargs=* Search call fzf#vim#grep2(
        \ "rg --column --line-number --no-heading --color=always --smart-case -- ", 
        \ <q-args>,
        \ fzf#wrap({
        \   'options': ['--layout=reverse'],
        \   'down': '30%'
        \ }),
        \ <bang>0
        \ )
```


This does not yet do anything particularly fancy - all it does is open a window with an interactive regex search. The next steps to make with quickfix windows require some additional explanations. If you'd prefer a popup instead of a split buffer, use `'window'` instead of down, and see `:h fzf-starting-fzf-in-a-popup-window`. This is left as an exercise to the reader.

### `--bind`ing keys for selecting entries

If you want to turn a search into a quickfix list, there's two things you need:

1. A way to select the entries you want
2. A way to chuck them into the quickfix list

For our purposes, we'll assume #1 means selecting all the entries, because this more closely matches my use. It's important to note that by using `--multi`, individual lines can be selected, but this selection process is too manual for me to bother.

Selecting entries is fairly easy using `--bind`. There's a special `select-all` event. There's a few ways to do this depending on personal preference:

* Map a separate key to select all
* Map a separate key to select all _and_ automatically submit the completion
* Map `<cr>` to select all and submit 
* Auto-submit without any interactive use (see the next section)

... and more options I can't be bothered listing out.

The generic form of bind you need is `--bind [key or event]:action[+action2[+action3[+...]]]`. Multiple binds in one command are comma-separated, or additional `--bind`s can be added. For example, if the goal is to always move to quickfix in a command, you can use `--bind enter:select-all+accept`. This will automatically select all and submit. The `+accept` here is (as far as I know) required to avoid overriding the default behaviour of `<CR>`. Similarly, if you want a non-CR key that selects all and submits, `--bind ctrl-a:select-all+accept`. If you don't want auto-submission, remove `+accept`. `--bind` is added to `options`


Updating `'options'`, you'll end up with:
```vim
command! -bang -nargs=* Search call fzf#vim#grep2(
        \ "rg --column --line-number --no-heading --color=always --smart-case -- ", 
        \ <q-args>,
        \ fzf#wrap({
        \   'options': ['--layout=reverse', '--bind=enter:select-all+accept'],
        \   'down': '30%'
        \ }),
        \ <bang>0
        \ )
```

Note that `--bind=` was used in this particular form, because using a space works weirdly with the command line options. It's possible that `--bind` would have to be separated from its arguments in the array for it to pass correctly, but I didn't care enough to check, and just slapped an `=` on it. 

Most of the options that can be used for extended scripting stuff are listed in `man fzf`. 


#### Aside: automatically submitting all matches without interaction

An absolute overkill way to go about search with predefined strings is actually to use fzf. By using `--bind=load:select-all+accept`, you can just auto-select everything. Though this is technically doable, as described previously, I would argue this is a better use-case for `:grep`. Given the size of the fzf command shown previously, it's also fairly easy to see that using `:grep` is _significantly_ shorter. I strongly suggest using `:grep` for predefined strings. 

Doing this also means fzf's interactive menu never opens, so no previewing can happen. Some observation suggests that it does allocate a window, then shuts it down immediately after, likely because the window loads before the `load` event is triggered. If this bothers you, `:grep` is your only option. That said, I'll still argue grep is the better option here.

### Adding quickfix entries

Adding quickfix entries is done with `setqflist`:

```vim
fun! s:Fzf2Quickfix(lines)
    call setqflist(map(copy(a:lines), '{"filename": v:val}'), "r")
    copen
endfun
```

This part is fairly straight-forward, especially because fzf's list contains maps that are compatible with `setqflist`'s special dict, and 

My personal assumption from here was that I needed to add a 'sink' parameter, and add a function to it. This is partly wrong. `sink`s are called once per argument, so if you get 100 results, the function is called 100 times. This is not great for performance, and will drastically slow things down.  For bulk work on fzf results, use `sinklist` instead. It's like `sink`, but it takes an array instead of individual matches, which is really useful when operating on things that are going to get turned into lists anyway. Adding the sinklist option, you'll end up with the final and operational

```vim
command! -bang -nargs=* Search call fzf#vim#grep2(
        \ "rg --column --line-number --no-heading --color=always --smart-case -- ", 
        \ <q-args>,
        \ fzf#wrap({
        \   'options': ['--layout=reverse', '--bind=enter:select-all+accept'],
        \   'down': '30%',
        \   'sinklist': function('s:Fzf2Quickfix')
        \ }),
        \ <bang>0
        \ )
```

All results from this query are submitted and added to quickfix, for further manual work, or for further quickfix commands. 

## General (optional/manual) use of quickfix with fzf

Aside default-fill quickfix, there are as demonstrated other ways to go about it. Using `g:fzf_action`, it's possible to apply the quickfix function directly to a keybind that then applies to all fzf windows. Unfortunately, mapping ctrl-a requires `--bind`, so it needs to be set in an environment variable instead:
```vim
let $FZF_DEFAULT_OPTS="--bind ctrl-a:select-all"
let g:fzf_action = {
  \ 'ctrl-f': function('s:Fzf2Quickfix'), " Same function as previously shown
  \ ...
  \ }
```

Now, any window can add entries to quickfix without further changes. I'll argue this is far more useful when the window is an rg/ag window, largely because line entries populate better than file entries, but it's technically possible to add both, but it's still possible. This does also make it possible to do it fully based on built-in fzf-vim commands, but not directly adding to quickfix.

It's important to note that as the function currently stands, `s:Fzf2Quickfix` clears the list before new entries are added. If you want to avoid this, you'll need to reimplement `Fzf2Quickfix` to not create a new list, and rather  just append. This is done by replacing the `r` argument with `a`. This is left as an exercise to the reader. There's a whole bunch of different things that can be done with quickfix as well. It's possible to have several persistent quickfix lists, though most operations modify the currently open one, so it's easy for it to be overwritten. That said, it's a lot of fun to just play around with the function calls, and I do encourage you to mess around with it if you haven't before. If you don't and plan to more actively use quickfix, I suggest adding more utilities around it. It's an absurdly useful feature, but the commands are relatively heavy to work with, without using various utility wrappers.
