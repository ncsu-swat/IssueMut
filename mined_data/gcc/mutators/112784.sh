#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/__builtin_memcmp/ {
    :a
    s/(sizeof\s*\()(.+)\s*->\s*[a-zA-Z_][a-zA-Z0-9_]*(\[[^]]*\])*\s*\)/\1*\2)/; t a
    s/(sizeof\s*\()(.+)\s*\.\s*[a-zA-Z_][a-zA-Z0-9_]*(\[[^]]*\])*\s*\)/\1\2)/; t a
}' "$file"