#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E 's/(\*)[[:space:]]*([^[:space:]=]+)[[:space:]]*=[[:space:]]*(\*)[[:space:]]*(\([^)]*volatile[^)]*\))([[:space:]]*)([^;]+);/\3\4\5\2 = \1\6;/g' "$file"