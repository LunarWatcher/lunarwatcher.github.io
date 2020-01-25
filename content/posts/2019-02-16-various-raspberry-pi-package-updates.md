---
date: "2019-02-16T00:00:00Z"
title: "Specific package updates on Raspberry Pi/Raspbian"
slug: specific-package-updates-on-raspberry-pi-raspbian
tags: ["raspberry pi", "raspbian"]
---

The Raspbian package repos are, in my experience, extremely slow with updates. Ninja pre-dates version one, Python3 is still stuck on 3.5.2, and a lot of other packages are outdated. Installing from source isn't always easy, because they get new dependencies, and suddenly you have accidentally missing packages and compiling fails. So here's a list of some install guides for various tools.

## Note

This is currently targeting a version of Raspbian that doesn't support 64 bit. When I get the updates that add support for 64 bit, I will be updating with 64 bit, and that'll likely be the only variant that gets updates. Especially for cases where specific binaries are necessary (for an instance with Clang), this will mean 32 bit won't be maintained by me.

## Disclaimer

These worked for me when I used them. These may be outdated, broken on other versions of Raspbian, or dependent on a lot of local config. This also assumes you have the essential build packages and a compiler of your choice linked to your system, along with git.

And make sure you type the commands; copy-pasting may lead to issues, and as usual, use common sense when running stuff. I will also not add the cleanup parts, but it's pretty easy: it's usually easy to just `rm -rf` the downloaded files or for that matter the entire build directory if you install multiple at once.

## Repeated calls

There is one thing you'll be seeing a lot in this:

```bash
cd ~
mkdir -p build
cd build
```

This is to get into a folder to keep builds in one place. It also makes it incredibly easy to `rm -r build` to clean up any mess. You can pick any folder you want for this. 

If you're not sure what this does, the first and last line is self-explanatory: it cd's you into the home dir and the build dir respectively. `mkdir -p` creates a directory if it doesn't exist. 

## Python 3

Specifically, this was done with 3.7.2. The first time I tried this, it failed to build one of the modules, and I couldn't install because of it. For newer versions, there's an extra library needed, but it fortunately works with the version in the package repo. 

```bash
# Necessary package for the build
sudo apt-get install libffi-dev
# See repeated calls
cd ~
mkdir -p build
cd build
# End repeated calls
# Grab the source. 3.7.2 can be replaced (but in both locations) for different versions.
wget https://www.python.org/ftp/python/3.7.2/Python-3.7.2.tar.xz
tar xf Python-3.7.2.tar.xz
cd Python-3.7.2
# Configure & make - the standard stuff
configure 
make
sudo make install 
# Verify
python3 --version
# This should say 3.7.2 (alternatively something else if you chose a different version)
```

## [Ninja](https://ninja-build.org)

**WARNING:** This requires several projects to build properly, and building is unnecessarily complicated. 

```
# required tools
sudo apt-get install bison autotools-dev
cd ~ && mkdir -p build && cd build
git clone https://github.com/skvadrik/re2c.git && cd re2c
# This is the current version: this might update later
git checkout 1.1.1 
cd re2c 
# re2c needs this first
./autogen.sh
# Regular boilerplate stuff
./configure && make && sudo make install
cd ../.. 
# Now that we have the dependency, let's install Ninja.
# Ninja is also Git-based, so grab that
git clone https://github.com/ninja-build/ninja.git && cd ninja
# Checkout the latest version. **This is important!** You can here replace it with whatever version is newer, if there is one.
git checkout v1.8.2
# Building in a separate dir is a good idea, and some places required. re2c is an exception to that, ninja is not.
mkdir build && cd build
# Ninja is written in itself. Bootstrapping helps avoid some issues, especially if you have pre-1.0.0 versions installed.
# Not entirely sure when you need this in terms of versions installed, but you do need it if you don't have ninja at all.
./../configure.py --bootstrap
# This produces a binary, which is then copied into /usr/bin for direct command line access.
# You can skip this step if you want to, but you need to move the binary if you want to use it. 
sudo cp ninja /usr/bin/ninja
# Verify:
cd ..
ninja --version
```

# Clang 7

This is a specifically tricky one, because compiling it from source is not possible. The RPi's limited resources compared to the extreme requirements of compiling the stuff that compiles your code makes building on a Pi absolutely horrible. The same applies to GCC.

Both Clang and GCC are outdated, but I'll be focusing on Clang as that's my compiler of choice. Fortunately, there are pre-compiled binaries, but they're not available from the package repo, which requires a couple extra steps.

```
# Boilerplate
mkdir -p ~/build && cd ~/build
# Grab the tar
wget http://releases.llvm.org/7.0.0/clang+llvm-7.0.0-armv7a-linux-gnueabihf.tar.xz
# Unpack
tar -xf clang+llvm-7.0.0-armv7a-linux-gnueabihf.tar.xz
# Rename 
mv clang+llvm-7.0.0-armv7a-linux-gnueabihf clang_7.0.0
# Move to the source
sudo mv clang_7.0.0 /usr/local
```

Now, Clang isn't as straight forward as the rest: you also need to add stuff to the PATH. `vim ~/.bashrc`, `nano ~/.bashrc`, or otherwise open an editor and open `.bashrc` - as long as it lets you edit, it doesn't matter which. There are a bunch of ways to do this, but I made sure it's flexible for changes, in addition to making the default compiler clang. For those of you who don't know how this works, CC and CXX affects which compiler is used, which means that needs to be `export`ed as well.

Here's the exports I use:

```
# Define CLANG_HOME - this also makes updates easier, by only making one change required
export CLANG_HOME=/usr/local/clang_7.0.0
# Add clang to the path
export PATH=$CLANG_HOME/bin:$PATH
# and the library headers to the library path
export LD_LIBRARY_PATH=$CLANG_HOME/lib:$LD_LIBRARY_PATH

# And finally, like I mentioned earlier, export CC and CXX to clang and clang++ respectively
export CXX=clang++
export CC=clang
```

Now, either reboot the terminal, or `source ~/.bashrc` (that reloads the config used), then verify with `clang++ --version` and/or `clang --version`. This should show 7.0.0
