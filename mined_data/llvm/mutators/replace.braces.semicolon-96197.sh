#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -E -i 's/__attribute__\(\(([^)]*)\)\)\)\s*([a-zA-Z_]\w*)(( [a-zA-Z_]\w*)+)\s*\(([^)]*)\)\s*\{\}/__attribute__((\1))) \2\4(\5);/' $file