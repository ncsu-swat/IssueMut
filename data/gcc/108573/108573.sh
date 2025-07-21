#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E '
/^[[:space:]]*volatile\s+.*\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*;/ {
  N
  s/^[[:space:]]*volatile\s+.*\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*;\s*\n([[:space:]]*)\2\s*(([+*\/%&|^<>-]|<<|>>)=)\s*(.*)\s*(<<|>>)\s*\b\1\b([^;]*);/\3\2 \4 \6 \7 \2\8;/
}' "$file"