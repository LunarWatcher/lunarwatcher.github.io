---
{
    "title": "Using CMake with FetchContent in a git hook",
    "date": "2026-11-04T22:57:12+01:00",
    "type": "til",
    "taxonomies": {
        "tags": ["cmake", "git"]
    }
}
---
It turns out that in a git hook, some extra variables are set. At the time of writing, the ones I found from `env` are:

```
GIT_AUTHOR_DATE=@1793829328 +0100
GIT_AUTHOR_EMAIL=
GIT_AUTHOR_NAME=Olivia
GIT_EDITOR=:
GIT_EXEC_PATH=/usr/lib/git-core
GIT_INDEX_FILE=/home/olivia/programming/cpp/violet/.git/index.lock
GIT_PREFIX=build/
```

As it turns out, at least one of these bastards fuck with `FetchContent`. When letting this hook run on a clean directory, this results in one of the most incomprehensible cmake errors I have ever seen:

```
Doing clean build
-- Building with preview server
-- Violet build configuration:
--      - Sanitising: ON
--      - Coverage: OFF
--      - Linting (clang-tidy): ON
--      - Server: ON
[ 11%] Performing download step (git clone) for 'cli12-populate'
Cloning into 'cli12-src'...
error: Your local changes to the following files would be overwritten by checkout:
        .github/CONTRIBUTING.md
        .github/ISSUE_TEMPLATE/config.yml
        .github/workflows/build.yml
        .github/workflows/docs.yml
        .github/workflows/fuzz.yml
        .github/workflows/tests.yml
        README.md
Please commit your changes or stash them before you switch branches.
Aborting
CMake Error at cli12-subbuild/cli12-populate-prefix/tmp/cli12-populate-gitclone.cmake:66 (message):
  Failed to checkout tag: 'v3.1.0'


make[2]: *** [CMakeFiles/cli12-populate.dir/build.make:102: cli12-populate-prefix/src/cli12-populate-stamp/cli12-populate-download] Error 1
make[1]: *** [CMakeFiles/Makefile2:87: CMakeFiles/cli12-populate.dir/all] Error 2
make: *** [Makefile:91: all] Error 2

CMake Error at /usr/share/cmake/Modules/FetchContent.cmake:1933 (message):
  Build step for cli12 failed: 2
Call Stack (most recent call first):
  /usr/share/cmake/Modules/FetchContent.cmake:1622 (__FetchContent_populateSubbuild)
  /usr/share/cmake/Modules/FetchContent.cmake:2160:EVAL:2 (__FetchContent_doPopulation)
  /usr/share/cmake/Modules/FetchContent.cmake:2160 (cmake_language)
  /usr/share/cmake/Modules/FetchContent.cmake:2401 (__FetchContent_Populate)
  CMakeLists.txt:85 (FetchContent_MakeAvailable)
```

For context, this is just on a plain `FetchContent` declaration:
```cmake
FetchContent_Declare(cli12
    GIT_REPOSITORY https://codeberg.org/LunarWatcher/CLI12
    GIT_TAG v3.1.0
)
```

It makes no use of patch functionality in a way that would allow for conflicts to occur, and the conflicts happen on a clean clone. Another variant of the errors I got was claiming that this and a couple other packages installed the same way did not exist.

## Debugging

This was not a particularly fun one to debug.

The actual cause of the errors in CMake is fairly easy to identify. After cloning, the entire cloned folder is empty, but all the history is imported. Git thinks it's done, CMake thinks it's done, CMake goes through its checks and explodes because the folder is empty.

I first blamed CMake, but ruled that out when a clean build worked from zsh. After further digging, I wondered if the command was being interfered with somehow in the script. This was ruled out pretty quickly with a good 'ol `set -x`. Then I blamed CMake again and assumed FetchContent had changed, and it hadn't[^1]. Downgrading to 4.4.4 (because that's the version `pip` has) did nothing to fix the problem, so if something did change, it's unlikely to have been introduced in 4.4.5 in particular. If FetchContent had changed in a breaking way, this should've triggered build errors outside the hook.

I then wondered if bash was doing something weird with the environment, which it wasn't. Running the command interactively in the folder from both zsh and bash from a clear state worked fine. I fucking lost it when running the offending script interactively in both zsh and bash worked. An `env | sort` later found extra git variables not present in the interactive shell - the 7 env variables shown in the first code block on this page. Unsetting them out of spite and then rerunning the commit inexplicably worked.

I don't understand the mechanism by which this fucks with `FetchContent`'s use of git (or git itself for that matter), especially since the result of the problem is the cloned repo being wiped clean.

This is the dumbest thing I've had the misfortune of needing to debug in a good while. It had not occurred to me that I could get build errors because of env variables introduced by git while running a git hook.

## Unfucking `FetchContent` in a git hook

Unset all the offending variables before the CMake command:

```bash
unset GIT_DIR GIT_INDEX_FILE GIT_PREFIX GIT_EXEC_PATH GIT_EDITOR GIT_AUTHOR_NAME GIT_AUTHOR_EMAIL GIT_AUTHOR_DATE
if ! cmake .. -DCMAKE_BUILD_TYPE=Debug -DVIOLET_SANITISE=ON -DVIOLET_WARNINGS_ARE_ERRORS=ON -DVIOLET_CLANG_TIDY=ON; then
    echo "Failed to run CMake setup!"
    exit 1
fi
```

I don't know which of these variables are considered bare minimum, because I don't care enough to figure out. They're all irrelevant for my use anyway, so I can just nuke the lot.

[^1]: I did do an update prior to this, bumping it from ??? to 4.4.5. This hasn't, to my knowledge, been a problem before this upgrade, but I can't rule it out without a downgrade, and that's too much effort.
