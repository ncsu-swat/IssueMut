#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script finds single-parameter C macros whose body is a simple token-pasting
# expression and rewrites them to expand to the parameter directly.
# It handles prefixes, suffixes, or both (e.g., p##x, x##s, p##x##s).
#
# The regex is designed to be robust:
# - It anchors to the start (^) and end ($) of the line to avoid partial matches
#   in more complex macros.
# - It correctly captures the macro signature (group 1) and parameter name (group 2)
#   for reuse in the replacement.
# - It uses a robust pattern for the macro body that covers all three token-pasting
#   scenarios involving a single parameter. The alternation handles cases where the
#   parameter is prefixed `(prefix##param...` or not `...|param##suffix)`.
# - It handles optional leading/trailing whitespace (`\s*`), including potential
#   carriage returns from DOS/Windows line endings, which was a likely cause of
#   the original script's failure.

sed -i -E 's/^(\s*#define\s+[a-zA-Z0-9_]+\(\s*([a-zA-Z0-9_]+)\s*\))\s+([a-zA-Z0-9_]+##\2(##[a-zA-Z0-9_]+)?|\2##[a-zA-Z0-9_]+)\s*$/\1 \2/' "$file"