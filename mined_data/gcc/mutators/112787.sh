#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# First, handle the special case for `vec` functions.
# If a function definition involves `vec`, remove the attribute if it exists.
# Then, do no more processing on this line.
/\<vec\>.*\)[^;]*\{/ {
  s/__attribute__\s*\(\s*\(\s*target\s*\("no-sve"\)\s*\)\s*\)\s*//
  b
}

# If a line already has the attribute, skip it.
/__attribute__\s*\(\s*\(\s*target\s*\("no-sve"\)\s*\)\s*\)/ b

# Filter out lines that are not function definitions.
# Skip preprocessor directives, control flow, typedefs.
/^\s*(#|if|for|while|switch|do|else|case|typedef)\b/ b

# Skip lines ending in a semicolon (declarations, statements, struct/enum/union defs).
/;\s*$/ b

# A function definition must have `(...) {`. Skip any line that does not match this pattern.
# This correctly ignores struct/union/enum definitions like `struct T {` which lack `()`.
/\)[^;]*\{/!b

# If a line passes all filters, it is a function definition that needs the attribute.
# Prepend the attribute on a new line.
s/^/__attribute__((target("no-sve")))\n/
' "$file"