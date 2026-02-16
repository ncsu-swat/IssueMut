#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script's regex `([^<]*)` was too greedy. In a line like
# `printf("...", (expr < 0))`, it would incorrectly start matching from the
# `printf(` call, because the pattern between the first `(` and the `<`
# character includes a comma and another parenthesis.
#
# The corrected regex `([^<,(]*)` is more restrictive. It captures an
# expression that does not contain a `<`, a `,`, or an opening `(`.
# - Excluding `<` is fundamental to isolating the left-hand side of the comparison.
# - Excluding `,` prevents the regex from matching across function arguments,
#   which fixes the primary bug seen in the `printf` example.
# - Excluding `(` prevents the regex from incorrectly parsing nested
#   parenthetical expressions. By stopping at the next `(`, it allows sed to
#   correctly find and transform the innermost expression first, such as in `((x < 0))`.
#
# This approach correctly handles all provided test cases and is more robust
# against nested expressions. It does not use the problematic `(^|[^(])` prefix
# from the original script, which failed on valid nested parentheses. The trade-off
# is that it won't match expressions that themselves contain a function call
# with arguments, but this is a reasonable limitation for a sed-based solution
# and is more robust than the original script.
sed -i -E 's/\(([^<,(]*) *< *0(\.0f?)?\)/__builtin_signbit(\1)/g' "$file"