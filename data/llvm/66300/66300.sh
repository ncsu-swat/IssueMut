#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Replaced any fixed array size with an empty bracket
sed -i -E 's/\[[0-9]+\]/\[\]/g' "$file"
