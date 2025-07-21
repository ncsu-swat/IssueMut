#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Use hold space as a "done" flag. If it is not empty, we have already acted.
x; /./ { x; b }; x

# If a pragma is found first, set the done flag (by copying the line to hold space)
# and then branch to the end (do not process the include rule). This prevents
# re-wrapping a file that already has these pragmas. The check is expanded
# to include pop_options for more robust detection.
/^[[:space:]]*#pragma GCC (push_options|optimize|pop_options)/ {
    h
    b
}

# If a valid #include directive is found first, wrap it.
# The address regex is improved to start with a # to avoid matching commented-out includes.
/^[[:space:]]*#[[:space:]]*include/ {
    # The substitution command captures indentation and the rest of the line.
    # It then rebuilds the block with the pragmas, preserving indentation.
    s@^([[:space:]]*)(#.*)@\1#pragma GCC push_options\n\1#pragma GCC optimize ("-O0")\n\1\2\n\1#pragma GCC pop_options@
    # Set the done flag (by copying the new multi-line pattern space to hold space)
    # so that no subsequent lines are processed.
    h
}
' "$file"