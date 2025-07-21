#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Add constexpr to struct variable declaration
sed -i -E 's/struct ([a-zA-Z_]\w*) ([a-zA-Z_]\w*)/constexpr struct \1 \2/' "$file"
