#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This regex is designed to find a pointer declaration that is initialized
# with a hardcoded memory address. It is made robust by:
# - Group 1: ^([[:space:]]*) captures optional leading whitespace (indentation).
# - Group 2: (.+[^[:space:]]) captures the variable's type. This is greedy but
#   the `[^[:space:]]` ensures it correctly stops before the asterisk even with
#   varied spacing.
# - Group 3: ([a-zA-Z_][a-zA-Z0-9_]*) captures the variable name.
# - The initialization match `=[^;]*;` is used instead of a greedy `.*` to
#   prevent bugs where multiple variables are declared on the same line.
decl_regex='^([[:space:]]*)(.+[^[:space:]])[[:space:]]*\*[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*=[^;]*0x[0-9a-fA-F]+[^;]*;[[:space:]]*$'

# Extract the variable name (group 3) from the first line that matches the pattern.
# The sed command quits after the first match to only process one variable.
var_name=$(sed -n -E "s|${decl_regex}|\3|p; T; q" "$file")

# If a variable name was found, proceed with the transformations.
if [ -n "$var_name" ]; then
    # Combine both transformations into a single sed invocation for efficiency.
    # The file is read and written only once.
    # 1. Replace the declaration. We use group 2 (type) and 3 (name) but discard
    #    group 1 (original indentation) to ensure the `extern` line is not indented,
    #    matching the desired output format.
    # 2. Replace member access from `->` to `.` for the specific variable, using
    #    word boundaries (\b) to prevent partial matches.
    sed -i -E \
        -e "s|${decl_regex}|extern \2 \3;|" \
        -e "s|\b${var_name}\b[[:space:]]*->|${var_name}.|g" \
        "$file"
fi