#!/bin/sh

set -e

printf "\033[0;32mDeploying updates to GitHub...\033[0m\n"

# Build
hugo 

cd public

# Commit
git add .

msg="rebuilding site $(date)"
if [ -n "$*" ]; then
	msg="$*"
fi
git commit -m "$msg"

# Push source and build repos.
git push origin master

# Commit the site source
cd ..

git add -A

git commit -m "$msg"
git push origin source
