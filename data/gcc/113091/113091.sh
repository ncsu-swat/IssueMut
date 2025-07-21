#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/\(\(int\)(.*?)([[:space:]]*-[[:space:]]*)\(int\)(.*?)\)/(\1\2\3)/g' "$file"