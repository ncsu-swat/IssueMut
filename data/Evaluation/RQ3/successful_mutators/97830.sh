#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Remove 'static'
sed -i -E 's/^[[:space:]]*static[[:space:]]+//' "$file"
