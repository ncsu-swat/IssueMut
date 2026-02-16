#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(\b__builtin_bswap16\s*\(\s*)\(\s*(unsigned\s+short|short\s+unsigned)\s*\)\s*/\1/g' "$file"