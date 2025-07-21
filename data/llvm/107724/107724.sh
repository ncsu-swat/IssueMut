#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Random #include directive
matches=$(grep -noE '#include' "$file")

if [ -z "$matches" ]; then
    echo "No matching patterns found."
    exit 0
fi

random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$random_match" | cut -d: -f1)

# Replace #include directive with a #embed directive
sed -i -E "${line}s/#include/#embed/" "$file"
