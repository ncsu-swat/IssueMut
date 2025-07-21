#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^[^\t ].*,.*;[[:space:]]*$/ {
    # Exclude function prototypes/definitions
    /\(.*\)/b

    # If the second variable is already volatile, do nothing
    /^[^,]+,[[:space:]]*volatile/b

    # Otherwise, add the volatile qualifier to the second variable
    s/^([^,]+,)[[:space:]]*/\1 volatile /
}
' "$file"