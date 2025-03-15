#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Use sed to remove __attribute__ from function declarations
sed -i -E '/\(.*\).*__attribute__\(\(.*\)\).*;/d' "$file"