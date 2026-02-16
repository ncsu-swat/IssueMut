#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i '/^#undef \([a-zA-Z_][a-zA-Z0-9_]*\)/ { :a; N; /\\$/ ba; d }' "$file"