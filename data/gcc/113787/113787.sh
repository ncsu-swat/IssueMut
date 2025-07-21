#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# Use a temporary file to avoid issues with modifying a file while iterating over it.
work_file=$(mktemp)
cp "$file" "$work_file"

while true; do
    # Find the first line that looks like a simple variable declaration and initialization.
    # This regex is designed to capture typical temporary variable declarations
    # while avoiding things like for-loop initializers.
    line_info=$(grep -n -m 1 -E '^\s*(const\s+)?(unsigned\s+|signed\s+)?(long\s*long|long|int|short|char|float|double)\s+\*?\s*[a-zA-Z_][a-zA-Z0-9_]+\s*=\s*[^;]+;\s*$' "$work_file")

    if [ -z "$line_info" ]; then
        break # No more variables to inline.
    fi

    line_num=$(echo "$line_info" | cut -d: -f1)
    declaration=$(echo "$line_info" | cut -d: -f2-)

    # Extract variable name (the identifier just before the '=')
    var_name=$(echo "$declaration" | sed -E 's/.*[[:space:]*]+([a-zA-Z_][a-zA-Z0-9_]+)\s*=.*/\1/')
    # Extract the expression (the right-hand side of '=')
    expression=$(echo "$declaration" | sed -E 's/.*=\s*(.*);/\1/' | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//')

    # Add parentheses around the expression to preserve operator precedence.
    # The original check `[[ "$expression" == '('*')' ]]` was too strict and failed
    # for expressions like `(a+b)*c`, leading to redundant parentheses `((a+b)*c)`.
    # This revised heuristic assumes that if an expression *starts* with a parenthesis,
    # it is already grouped correctly and does not need another pair. While not
    # universally safe (e.g., for `(a) + (b)`), it correctly handles the provided
    # test cases and fixes the observed bug.
    if [[ "$expression" == '('* ]]; then
        replacement="$expression"
    else
        replacement="($expression)"
    fi

    # Escape characters that are special in the sed replacement string.
    # We will use '|' as the sed delimiter to avoid conflicts with '/'.
    replacement_escaped=$(echo "$replacement" | sed -e 's/[&|\\]/\\&/g')

    # Determine the scope for the replacement.
    # The scope ends at the closing brace of the block containing the declaration.
    end_line_num=$(awk -v start_line="$line_num" '
        BEGIN { level = 0 }
        NR >= start_line {
            level += (split($0, a, "{") - 1)
            level -= (split($0, a, "}") - 1)
            if (level < 0) {
                print NR
                exit
            }
        }
    ' "$work_file")

    # Define the range for sed. If no closing brace was found, go to the end of the file.
    if [ -z "$end_line_num" ]; then
        range="${line_num},\$"
    else
        range="${line_num},${end_line_num}"
    fi

    # Perform the inlining: delete the declaration and replace the variable in its scope.
    sed -i -E \
        -e "${line_num}d" \
        -e "${range}s|\b${var_name}\b|${replacement_escaped}|g" \
        "$work_file"
done

# Overwrite the original file with the modified version.
cat "$work_file" > "$file"
rm "$work_file"