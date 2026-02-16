#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(for\s*\(\s*)\s*\bint\b(\s+[^;]+;)/\1char\2/' "$file"