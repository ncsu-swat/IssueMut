#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Address only lines that are statements (heuristically, those ending in a semicolon)
# and contain a compound literal. This avoids matching on function definitions.
# The initializer match `\{[^{}]*\}` is used to avoid greedily matching
# entire code blocks if they contain nested braces.
/\(([^()]+)\)\s*\{[^{}]*\}.*;/ {
    # Save the original line.
    h

    # In the pattern space, substitute the *last* compound literal with the variable name.
    # The `(.*)` at the start is greedy, ensuring we operate on the last match on the line.
    s/(.*)\(([^()]+)\)\s*(\{[^{}]*\})(.*)/\1mutated_var\4/

    # Swap the modified line into the hold space and bring the original line back.
    x

    # From the original line, construct the new variable declaration.
    # The `.*` after the indent is greedy to find the *last* literal, consistent with the above.
    # \1 = indentation, \2 = type, \3 = initializer.
    s/^(\s*).*\(([^()]+)\)\s*(\{[^{}]*\}).*/\1\2 mutated_var = \3;/

    # Append the modified line (the function call) from the hold space.
    G
}' "$file"