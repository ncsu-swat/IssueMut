#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# Use a temporary file to avoid issues with sed -i on some platforms
tmpfile=$(mktemp)

sed -E '
# Find the start of an __attribute__ block
/__attribute__[[:space:]]*\(\(/ {
    # Create a label for joining multi-line attributes
    :join_lines
    # If the pattern space does not contain the closing "))", it is a multi-line attribute
    /\)\)/! {
        # Append the next line, if not the last line
        $!N
        # Branch back to join_lines to check again
        b join_lines
    }

    # Only proceed if the attribute block contains "target("
    /(__)?target(__)?[[:space:]]*\(/ {
        # Create a label for looping to remove multiple target attributes
        :remove_target
        # Case 1: Remove target attribute followed by a comma and optional whitespace
        s/(__)?target(__)?[[:space:]]*\("[^"]*"\)[[:space:]]*,[[:space:]]*//; t remove_target
        # Case 2: Remove target attribute preceded by a comma and optional whitespace
        s/,[[:space:]]*(__)?target(__)?[[:space:]]*\("[^"]*"\)//; t remove_target
        # Case 3: Remove target attribute when it is the only one inside the parentheses
        s/(__)?target(__)?[[:space:]]*\("[^"]*"\)//; t remove_target

        # After removing target(s), if the attribute list becomes empty,
        # remove the entire __attribute__((...)) construct.
        # This handles cases that result in __attribute__(()) or __attribute__(( )).
        # It preserves any other code on the same line.
        s/[[:space:]]*__attribute__[[:space:]]*\(\([[:space:]]*\)\)[[:space:]]*//

        # If the entire line (or joined block) becomes empty after removal, delete it.
        /^[[:space:]]*$/d
    }
}
' "$file" > "$tmpfile" && mv "$tmpfile" "$file"