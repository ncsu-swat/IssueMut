#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"
tmpfile=$(mktemp)

trap 'rm -f "$tmpfile"' EXIT

# The script logic is as follows:
# 1. Add guards to skip lines that should not be modified:
#    - Lines that already contain "volatile long" (for idempotency).
#    - Lines with "extern" declarations.
#    - Lines that are function prototypes (heuristic: no '=' and ends with '(..);').
#    - Lines that are function definitions (heuristic: 'long func(...' pattern).
# 2. For the remaining lines, perform the substitution using a placeholder technique
#    to correctly handle 'long long' and multiple 'long' declarations on one line.
#    - Replace 'long long' with a temporary, unique placeholder.
#    - Replace all remaining instances of 'long' with 'volatile long'.
#    - Replace the placeholder with 'volatile long long' to complete the transformation.
# This layered approach is more robust than a single complex regex.

sed -E '
# 1. Guards to skip modification

# Idempotency: if already volatile, skip the line
/\bvolatile\s+long\b/b

# Skip extern declarations
/^\s*extern\b/b

# Skip function prototypes (heuristic: no "=" and ends with "(...);")
/=/!{
  /\(.*\);\s*$/b
}

# Skip function definitions to avoid changing the return type
/\blong\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(/b

# 2. Main substitution logic

# Use a placeholder (\x01) to correctly handle "long long"
s/\blong\s+long\b/\x01/g
# Add volatile to all other `long` declarations
s/\blong\b/volatile long/g
# Restore the placeholder, adding volatile to it
s/\x01/volatile long long/g
' "$file" > "$tmpfile" && mv "$tmpfile" "$file"