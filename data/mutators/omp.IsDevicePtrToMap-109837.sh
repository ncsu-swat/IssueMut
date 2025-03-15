#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E 's/firstprivate\s*\(\s*([a-zA-Z0-9_][a-zA-Z0-9_]*)\s*\)/map(to:\1)/' "$file"
sed -i -E 's/(firstprivate\s*\(.*),\s*([a-zA-Z0-9_][a-zA-Z0-9_]*)\s*\)/\1\) map(to:\2)/' "$file"
