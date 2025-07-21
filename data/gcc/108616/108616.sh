#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Process only lines containing `alloca` and `sizeof`
/alloca/!b
/sizeof/!b

# Use a loop with a label to handle multiple `alloca` calls on the same line.
:mutate

# Case 1: `number * sizeof(type)` becomes `number`
# Example: alloca(10 * sizeof(int)) -> alloca(10)
# The `t mutate` command branches to the :mutate label if a substitution was made.
s/(alloca\s*\([^)]*)\b([0-9]+)\b\s*\*\s*sizeof\s*\([^)]*\)/\1\2/
t mutate

# Case 2: `sizeof(type) * number` becomes `number`
# Example: alloca(sizeof(int) * 10) -> alloca(10)
s/(alloca\s*\([^)]*)sizeof\s*\([^)]*\)\s*\*\s*\b([0-9]+)\b/\1\2/
t mutate

# Case 3: General case `...sizeof(type)...` becomes `...2...`
# This handles variable expressions.
# Example: alloca(count * sizeof(double)) -> alloca(count * 2)
# This substitution is carefully constructed to replace only `sizeof(...)` with `2`,
# preserving the surrounding expression.
s/(alloca\s*.*)sizeof\s*\([^)]*\)(.*\))/\12\2/
t mutate
' "$file"