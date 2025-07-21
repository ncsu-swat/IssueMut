#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E \
    -e '/\bconst\b/b' \
    -e '/^[[:space:]]*(if|while|switch|return|case|for)\b/b' \
    -e '/^[[:space:]]*\S+.*\s+\S+\s*=/!b' \
    -e 's/\s*=\s*(\{[^}]*\}|\([^)]*\)|[^,;]+)//g' \
    "$file"