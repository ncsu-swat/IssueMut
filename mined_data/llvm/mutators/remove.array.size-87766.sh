#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -E -i 's/([a-zA-Z_]\w*)\s+([a-zA-Z_]\w*)\s*\[\s*([0-9]+)\s*\]\s*;/\1 \2[];/' $file