#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
    -e 's/\(\s*\*\s*\(\s*volatile\s+.*\s*\*\s*\)\s*&\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*\)/\1/g' \
    -e 's/\*\s*\(\s*volatile\s+.*\s*\*\s*\)\s*&\s*([a-zA-Z_][a-zA-Z0-9_]*)/\1/g' \
    "$file"