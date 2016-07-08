#!/bin/sh
# npm_post.sh

# This script finds any .info files in the node_modules directory and renames them so they don't
# conflict with drush. package.json runs this on completion of npm install.
# These files, if any are not actually needed to run grunt and compile LIbSass
# See this issue for more info: https://www.drupal.org/node/2329453

# One caveat here is that you may run into an error that the script won't run.
# To solve this you can either run
# sudo npm install --unsafe-perm
# or alternatively create an .npmrc file with the code:
# unsafe-perm = true

find -L ./node_modules -type f -name "*.info" -print0 | while IFS= read -r -d '' FNAME; do
    mv -- "$FNAME" "${FNAME%.info}.inf0"
done