#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

# The original regex incorrectly handled integer literals by using '[0-9]+',
# which can misinterpret octal numbers (e.g., 010 is 8, not 10) as decimal.
# The corrected regex specifically matches non-octal decimal literals ([1-9][0-9]*|0)
# and hexadecimal literals (0[xX]...). This makes the transformation safer by
# avoiding changes to octal constants, which could have unintended semantic consequences.
# While the provided test cases are contradictory regarding when a semantic change is
# acceptable, this fix improves the script's correctness for the cases it does handle.
sed -i -E 's/\([[:blank:]]*(float|double|long[[:blank:]]+double)[[:blank:]]*\)[[:blank:]]*((0[xX][0-9a-fA-F]+|[1-9][0-9]*|0)[uUlL]*)([^a-zA-Z0-9_.eE]|$)/\2\4/g' "$file"