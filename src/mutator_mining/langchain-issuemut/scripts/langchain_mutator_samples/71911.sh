#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# Removes typeof() around an expression
sed -i -E "s/typeof\(([^\)]*)\)/\1/" "$file"