#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E '/if \(1\)/d' "$file"
sed -i -E 's/goto (.*);/asm goto("" : : : : \1);/' "$file"
