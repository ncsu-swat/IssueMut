#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Remove (double) casts while keeping the variable unchanged. The \1 
# replaces everything matched with just the variable name (removing (double)).
sed -i -E 's/\(double\) *([a-zA-Z_][a-zA-Z0-9_]*)/\1/g' "$file"