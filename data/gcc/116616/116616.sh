#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^[[:space:]]*case[[:space:]]+0[[:space:]]*:/ {
    :a
    /\n[[:space:]]*(case[[:space:]]+.*:|default[[:space:]]*:)/b end
    $b end
    N
    ba
:end
    /\n/!d
    s/.*\n//
}' "$file"