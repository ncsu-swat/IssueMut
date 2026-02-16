#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script's use of a greedy `(.*)` to capture the "false"
# expression was flawed. It could incorrectly match across multiple statements
# on a single line (e.g., over a semicolon).
#
# This revised script fixes the issue by replacing the greedy `(.*)` with a
# more specific `([^;]*)`. This non-greedy pattern captures the "false"
# expression by matching any sequence of characters that does not include a
# semicolon. This prevents the regex from overrunning its intended scope on
# lines with multiple statements.
#
# A terminator group `([;,)})])` is still used to correctly handle expressions
# that end in a character other than a semicolon, such as a parenthesis or comma.
#
# The `->` operator is also temporarily replaced with a placeholder character
# to prevent the `>` within it from being misinterpreted as a comparison operator.

sed -i -E '
s/->/\x01/g;
s/\(([^>]*)\s*>\s*([^)]*)\)\s*\?\s*([^:]*)\s*:\s*([^;]*)([;,)})])/\(\1 <= \2\) ? \4 : \3\5/g;
s/\x01/->/g;
' "$file"