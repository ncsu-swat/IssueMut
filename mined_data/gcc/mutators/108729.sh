#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

awk '
BEGIN {
    level = 0
    # state[level] == 1 means print, 0 means do not print
    state[0] = 1
}

# Match #if, #ifdef, #ifndef.
# The logic is the same for all: enter a new nesting level.
# The new level is printable only if the parent level was.
# We assume the condition is true, so we keep the parent state.
/^[[:space:]]*#if([[:space:]]|$)/ || /^[[:space:]]*#ifdef([[:space:]]|$)/ || /^[[:space:]]*#ifndef([[:space:]]|$)/ {
    level++
    state[level] = state[level-1]
    next
}

# Match #else, #elif.
# If the parent level was printable, the #if was "true",
# so this alternative branch must be "false" (not printed).
/^[[:space:]]*#else([[:space:]]|$)/ || /^[[:space:]]*#elif([[:space:]]|$)/ {
    if (state[level-1] == 1) {
        state[level] = 0
    }
    next
}

# Match #endif.
/^[[:space:]]*#endif([[:space:]]|$)/ {
    level--
    next
}

# Print lines that are in a "printable" state.
state[level] == 1 {
    print
}
' "$file" > "$file.tmp" && mv "$file.tmp" "$file"