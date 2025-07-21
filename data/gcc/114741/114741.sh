#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '/^[[:space:]]*#[[:space:]]*pragma[[:space:]]+GCC[[:space:]]+target\b/d' "$file"