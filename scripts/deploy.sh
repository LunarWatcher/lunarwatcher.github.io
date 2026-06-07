#!/usr/bin/bash

VIOLET_EXE=${VIOLET_EXE:-violet}

echo "Using $VIOLET_EXE"

git_root=$(git rev-parse --show-toplevel)
cd "$git_root"

rm -rf pages
time "$VIOLET_EXE" generate

if [[ $? != 0 ]]; then
    echo "Generation failed!"
    exit 1
fi

cd pages
git init
git checkout -b pages
git remote add cb git@codeberg.org:LunarWatcher/pages
git remote add gh git@github.com:LunarWatcher/lunarwatcher.github.io

git add -A
git commit -m "Generate page"

git push -f cb pages
git push -f gh pages
