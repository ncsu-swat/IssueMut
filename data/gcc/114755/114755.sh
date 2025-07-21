#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"
marker="__SED_MODULO_DECREMENT_PROTECTION_MARKER__"

sed -i -E "
# Protect the pre-decrement operator '--' when it follows a modulo operator context.
# The context is '%', followed by any mix of whitespace and opening parentheses.
s/(%[[:space:]\(]*)--/\1$marker/g

# Create a loop to handle multiple unary minuses, e.g., 'x % - - y'.
:loop
    # Remove a single unary minus and any following whitespace that is in a modulo context.
    # The 'g' flag handles multiple occurrences on one line, e.g., 'a % -b; c % -d;'.
    s/(%[[:space:]\(]*)-[[:space:]]*/\1/g
    # If a substitution occurred, branch back to the loop label to re-process the line.
    t loop

# Restore the protected pre-decrement operators.
s/$marker/--/g
" "$file"