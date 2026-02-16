#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The goal is to toggle the 'noipa' attribute.
# If 'noipa' is present, remove it.
# If 'noipa' is not present, add it.
# This script handles attributes on a single line.

sed -i -E '
# Find lines that look like they contain a full __attribute__((...)) block
/__attribute__\s*\(\(.*\)\)/ {
    # If "noipa" is already present, remove it
    /\bnoipa\b/ {
        # Case 1: Handles "..., noipa" and "..., noipa, ..."
        s/, *noipa\b//
        # Case 2: Handles "noipa, ..."
        s/\bnoipa, *//
        # Case 3: Handles "noipa" as the only attribute
        s/\bnoipa//
        b
    }

    # If "noipa" is not present, add it
    # First, try adding it assuming there are other attributes
    s/(\)\))/, noipa))/

    # If the attribute list was empty, the line now contains ((, noipa)).
    # This second substitution corrects it to ((noipa)).
    s/\(\(, noipa\)\)/((noipa))/
}
' "$file"