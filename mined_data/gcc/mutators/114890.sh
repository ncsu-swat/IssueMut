#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(vpaddq?_[a-zA-Z0-9_]+\s*\()\s*(.*?)\s*,\s*(.*?)\s*(\))/\1\3, \2\4/g' "$file"