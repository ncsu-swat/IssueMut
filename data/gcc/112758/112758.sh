#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The script is broken into several parts to handle various cases robustly.
# 1. Handle 'volatile' on a line by itself. This C syntax applies the qualifier
#    to the declaration on the next line. We match a line containing only
#    'volatile', append the next line ('N'), and then remove the 'volatile'
#    line including its trailing newline.
# 2. Remove the 'volatile' keyword where it appears inline. Using word
#    boundaries (\b) ensures we don't affect identifiers containing "volatile".
#    This step may leave behind extra whitespace.
# 3. Clean up whitespace. First, collapse any sequence of two or more
#    whitespace characters into a single space.
# 4. Clean up whitespace at the beginning of the line that may have been
#    left by removing 'volatile' from the start of a declaration.
sed -i -E \
    -e '/^[[:space:]]*\bvolatile\b[[:space:]]*$/{ N; s/^[[:space:]]*\bvolatile\b[[:space:]]*\n//; }' \
    -e 's/\bvolatile\b//g' \
    -e 's/[[:space:]]{2,}/ /g' \
    -e 's/^[[:space:]]+//' \
    "$file"