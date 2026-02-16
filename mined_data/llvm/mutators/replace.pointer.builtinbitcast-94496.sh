#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -E -i 's/\*\(const\s+([a-zA-Z_]\w*)\s*\*\)\s*\(\s*const\s+void\s*\*\)\s*([a-zA-Z_]\w*)/__builtin_bit_cast(\1, \2)/' $file