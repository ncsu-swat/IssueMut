#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(([a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*:)+)[[:space:]]*;/\1 {}/g' "$file"