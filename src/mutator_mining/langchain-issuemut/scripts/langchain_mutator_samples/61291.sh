#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Change typedef from double to long double
sed -i -E "s/typedef double ([a-zA-Z_][a-zA-Z0-9_]*);/typedef long double \1;/" "$file"