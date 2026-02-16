#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

VECT_TYPE=$(sed -n -E \
    -e 's/.*typedef.* ([a-zA-Z0-9_]+)\s*__attribute__.*/\1/p' \
    -e 's/.*typedef.* ([a-zA-Z0-9_]+);/\1/p' "$file" | head -n 1)

if [ -n "$VECT_TYPE" ]; then
    sed -i -E "s/~(\([^)]+\))/($VECT_TYPE)\1 == 0/g" "$file"
fi