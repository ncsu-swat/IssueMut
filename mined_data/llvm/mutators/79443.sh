#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script's failure was in its deletion logic. It used a line range
# `/start/,/end/d` where the 'end' pattern was too generic (`/}/`), causing it
# to match the closing brace of a subsequent function and delete too much code.
#
# This corrected script uses a robust sed loop for deletion:
# 1. It finds the specific function signature.
# 2. It enters a loop, appending lines to the pattern space (`N`).
# 3. It continues looping until a line containing a closing brace `}` is found.
#    This is safe because the target function is simple with no nested blocks.
# 4. Once the end of the function is found, the entire accumulated block is deleted.
#
# This approach correctly handles both single-line and multi-line function
# definitions without affecting other code. The replacement logic from the
# original script was correct and is retained. Both operations are combined
# into a single `sed` call for efficiency.

sed -i -E \
  -e 's/(cleanup\s*\(\s*)cleanup_free(\s*\))/\1free\2/g' \
  -e '
/^\s*void\s+cleanup_free\s*\(\s*void\s*\*\*\s*p\s*\)/ {
    :a
    /}/ {
        d
        b
    }
    N
    ba
}' "$file"