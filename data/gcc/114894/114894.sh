#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script failed due to non-portable GNU sed extensions in the regex.
# This version uses POSIX ERE features for better compatibility.
# 1. Replaced non-standard `\s` with POSIX character class `[[:space:]]`.
# 2. Replaced non-standard `\t` with `[ \t]`.
# 3. Replaced non-standard non-capturing groups `(?:...)` with standard capturing groups `(...)`.
#    This required re-calculating the back-reference indices (e.g., `\3` became `\5`).
# 4. Replaced `\?` with the more portable `[?]` to match a literal question mark.
# 5. Removed comments from within the sed script string, as this is not portable.
# 6. Separated sed commands by newlines for clarity and compatibility.
sed -i -E '
:a; N; $!ba

s/((^|\n)[ \t]*)if[[:space:]]*\([a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*!=[[:space:]]*0(\.0f?)?\)[[:space:]]*[{]?[[:space:]]*(\n[[:space:]]*)?return[[:space:]]+([^;]+);[[:space:]]*(\n[[:space:]]*)?[}]?[[:space:]]*(\n[[:space:]]*)?(else[[:space:]]*(\n[[:space:]]*)?)?return[[:space:]]+0(\.0f?)?;/\1return \5;/g

s/((^|\n)[ \t]*)return[[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*!=[[:space:]]*0(\.0f?)?[[:space:]]*[?][[:space:]]*([^:]+)[[:space:]]*:[[:space:]]*0(\.0f?)?[[:space:]]*;/\1return \4;/g
' "$file"