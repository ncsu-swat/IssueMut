#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Random function
matches=$(grep -noE '([a-zA-Z_]\w*)(( [a-zA-Z_]\w*)+)\s*\(([^)]*)\)\s*\{' "$file")

if [ -z "$matches" ]; then
    echo "No matching patterns found."
    exit 0
fi

random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$random_match" | cut -d: -f1)

sed -i -E "${line}s/([a-zA-Z_]\w*)(( [a-zA-Z_]\w*)+)\s*\(([^)]*)\)\s*\{/__attribute__((weak)) \1\2(\4) {/" "$file"


# Random variable
matches=$(grep -noE '([a-zA-Z_]\w*)(( [a-zA-Z_]\w*)+)\s*\=' "$file")

if [ -z "$matches" ]; then
    echo "No matching patterns found."
    exit 0
fi

random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$random_match" | cut -d: -f1)

sed -i -E "${line}s/([a-zA-Z_]\w*)(( [a-zA-Z_]\w*)+)\s*\=/__attribute__((weak)) \1\2 =/" "$file"