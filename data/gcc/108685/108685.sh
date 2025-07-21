#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script was too aggressive because its regex `for` could match
# substrings in other words (e.g., a line starting with `format...`).
# The corrected regex uses `\b` (a word boundary anchor) to ensure it only
# matches the whole word `for`. This prevents it from incorrectly deleting
# lines that are not `for` loops. A word boundary is also added to the
# `#pragma omp for` for the same reason, increasing robustness.
# The `N; P; D;` construct creates a two-line sliding window to correctly
# identify the pattern across adjacent lines.
sed -i -E '
:a
$!N
s/^[[:space:]]*for\b[^\n]*\n([[:space:]]*#pragma omp for\b.*)/\1/
P
D
' "$file"