#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

sed -i -E 's/([a-zA-Z_][a-zA-Z0-9_]*) alignas\(([0-9]+)\);/alignas\(\2\) \1;/' "$file"
