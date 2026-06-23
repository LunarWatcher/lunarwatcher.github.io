---
{
    "title": "Automation",
    "type": "notes"
}
---

Automation is a really interesting field, and one I spend a fair bit of time on. At this time, my two biggest automation projects are:

1. [My dotfiles](https://codeberg.org/LunarWatcher/dotfiles), which contain a massive makefile setup that lets me bootstrap several kinds of environments with my setup, including both desktop and server applications.

  In addition, the dotfiles themselves contain other automation, like shell aliases and what'll eventually be a longer list of emacs snippets.
2. [Umbra](https://codeberg.org/LunarWatcher/umbra), a shell utility and path wrangling tool that's designed to avoid unnecessarily verbose commands when things can be inferred from context

I also have a few other minor utilities that automate stuff for me (including installing stuff).


I do not use slop machines for automation. Aside the fact that slop machines are shit at their jobs, they consume ridiculous quantities of water and power, and make society as a whole worse. It's also far more interesting to find smarter solutions to most of my automation problems that work deterministically (or approximately deterministically), and require little to no input. For example, Umbra's `devenv` and `zellij` modules save me ridiculous amounts of typing/copypasta on project setup at work, and it does so in milliseconds with nearly no compute.

