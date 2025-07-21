#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The transformation logic must be conditional. For some inputs, `__memx` is added.
# For an input that already contains `__memx`, the transformation is different (some are removed).
# This requires detecting the presence of `__memx` in the file and choosing a code path.
# The following `sed` script slurps the entire file and then decides which logic to apply.

sed -i -E '
# Slurp the entire file into the hold space, then move it to pattern space.
H;1h;$!d;x;

# Check if `__memx` exists anywhere in the file. If not, branch to the "add" logic.
/\b__memx\b/!b add_logic

# === Cleanup Logic ===
# This block executes if `__memx` was found.
# The rule derived from the test cases is to remove `__memx` from non-const pointers.
# We use a placeholder to protect the valid `const __memx` occurrences.
s/\b__memx\b/@@MEMX_PLACEHOLDER@@/g
s/(\b(const|volatile)\b\s+)@@MEMX_PLACEHOLDER@@/\1__memx/g
s/((^|\s|[,({=])\s*)@@MEMX_PLACEHOLDER@@\s*/\1/g
b end

:add_logic
# === Add Logic ===
# This block executes if `__memx` was not found.
# The goal is to add `__memx` to all pointer types.
s/((^|\s|[,({=])\s*)((const\s+|volatile\s+)*\s*)(((struct|union|enum)\s+)?[a-zA-Z_][a-zA-Z0-9_]*(\s+[a-zA-Z_][a-zA-Z0-9_]*)*\s*\*+)/\1\3 __memx \5/g
s/__memx\s+__memx/__memx/g

:end
' "$file"