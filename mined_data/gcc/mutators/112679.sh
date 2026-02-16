#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E -e 's/unsigned _BitInt\(([0-9]+)\) ([a-zA-Z_][a-zA-Z0-9_]*) = (0x[a-zA-Z0-9_]*);/return \3;/' -e '/return \(float\)([a-zA-Z_][a-zA-Z0-9_]*)/d' "$file"