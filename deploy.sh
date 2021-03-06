#!/bin/sh

set -e

printf "\033[0;32mDeploying updates to GitHub...\033[0m\n"

# Build
hugo --minify 

cd public

# Commit
git add .

msg="rebuilding site $(date)"
if [ -n "$*" ]; then
	msg="$*"
fi
git commit -S -m "$msg"

# Push source and build repos.
git push origin master

# Commit the site source
cd ..

git add -A

git commit -S -m "$msg"
git push origin source
