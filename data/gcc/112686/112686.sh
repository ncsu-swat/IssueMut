#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# Define the pattern for the attribute for clarity and reuse.
# This pattern is simplistic and does not handle nested parentheses within the attribute.
ATTR_PATTERN="__attribute__[[:space:]]*\(\([^)]*\)\)"

# The script operates in stages on each line:
# 1. First, check if the line consists ONLY of an attribute specifier. If so, delete it.
#    The 'd' command causes sed to stop processing the current line and start the next cycle.
# 2. If the line was not deleted, it means it contains an inline attribute or no attribute.
#    The script then proceeds to the substitution commands for that line.
# 3. Replace the attribute itself with a single space. This prevents words from merging
#    (e.g., "static__attribute__((...))int" becoming "staticint").
# 4. Normalize whitespace by collapsing any sequence of multiple spaces into a single space.
# 5. Trim leading and trailing whitespace from the line.
sed -i -E \
    -e "/^[[:space:]]*${ATTR_PATTERN}[[:space:]]*\$/d" \
    -e "s/${ATTR_PATTERN}/ /g" \
    -e 's/[[:space:]][[:space:]]*/ /g' \
    -e 's/^[[:space:]]*//' \
    -e 's/[[:space:]]*$//' \
    "$file"