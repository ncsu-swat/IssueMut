#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"
temp_file=$(mktemp)

sed -E 's/(\(\s*(_Float16|__fp16)\s*\))\s*\(\s*(float|double|long double)\s*\)/\1/g' "$file" > "$temp_file" && mv "$temp_file" "$file"