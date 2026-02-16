#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E ':a; N; $!ba; s/(if\s*\([^)]+\))\s*\{(([^{}]|\{[^{}]*\})*)\}/\1\2/g' "$file"