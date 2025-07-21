#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# State machine to enter/exit a function scope
/\)[[:space:]]*\{/ {
  h; s/.*/in_func/; x
  b
}

/^[[:space:]]*}/ {
  h; s/.*//; x
  b
}

# Gate: only operate on the first suitable line within a function
x
/in_func$/! { x; b }
x

# Main logic block to find and modify a variable declaration
{
    # Filter out lines that are not likely to be simple variable declarations
    /^[[:space:]]*(#|\/\/|\/\*|if|while|for|switch|return|case|default|do|else|\}|typedef|using|namespace)/b
    /;\s*$/!b

    # Use hold space to test properties of the line without modifying it yet
    h

    # Heuristics applied to a copy of the line to check if it is a declaration
    # Remove initializer part
    s/[[:space:]]*=.*//

    # Reject function calls, e.g. foo(bar);
    /\(/ { g; b }

    # Reject member access, e.g. foo.bar; or p->bar;
    /->|\./ { g; b }

    # After stripping, trim whitespace
    s/^[[:space:]]+//; s/[[:space:]]+$//

    # A declaration should have multiple words (e.g., "int i") or be a pointer
    # declaration without spaces (e.g., "int*p").
    # An expression like "i++;" or a single-identifier statement "foo;" would have
    # neither a space nor a star.
    # This rejects single-word statements, while accepting multi-word declarations
    # and pointer declarations.
    /[[:space:]]/! {
        /\*/! { g; b }
    }

    # If all checks pass, restore the original line from hold space
    g

    # Add "volatile" if not already present.
    /volatile/b

    s/^([[:space:]]*)/\1volatile /

    # Mark this function as processed to only modify the first declaration
    x
    s/in_func/in_func_done/
    x
}
' "$file"