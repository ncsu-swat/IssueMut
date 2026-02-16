#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/long double/b
/\blong( long)?\b[^=]*=/ {
    # Rule 1: Handle cases where the dereferenced expression is parenthesized, e.g., (int)(*p)
    # The backreference \1 captures the parenthesized expression itself.
    s/\(int\)[[:space:]]*(\(([^)]*\*[^)]*)\))/\1/g;

    # Rule 2: Handle cases where the dereference is not parenthesized, e.g., (int)*p or (int) *(p+1)
    # This is simpler, just removing the cast before the dereference operator.
    s/\(int\)[[:space:]]*\*/\*/g;
}
' "$file"