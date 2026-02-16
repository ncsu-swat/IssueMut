#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

sed -i -E "s/__builtin_clz[l]?[l]?\(([a-zA-Z_][a-zA-Z0-9_]*)\)/__builtin_clzg(\1)/g" "$file"