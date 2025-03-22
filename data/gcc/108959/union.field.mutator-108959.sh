#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E 's/^\s*([a-zA-Z_][a-zA-Z0-9_]*[^a-zA-Z_]+)([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*(.*)\.[a-zA-Z_][a-zA-Z0-9_]*\s*;/\1\2 = \(\1\)\3;/' "$file"
sed -i -E 's/return\s*0;//' "$file"
sed -i -E 's/return\s*(.*)\((.*)\);/\1(\2);/' "$file"
