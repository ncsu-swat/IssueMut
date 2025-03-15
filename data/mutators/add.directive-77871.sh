#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

nums=$(grep -oE "if \(.*[^a-zA-Z0-9_]*[0-9]+[^a-zA-Z0-9_]*.*\)" "$file" | \
sed -E "s/if \(.*[^a-zA-Z0-9_]*([0-9]+)[^a-zA-Z0-9_]*.*\)/\1/") 

if [ -z "$nums" ]; then
  echo "No matching patterns found."
  exit 0
fi

num=$(echo "$nums" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

sed -i -E "1 i\#define D $num" "$file"
sed -i -E "s/([^a-zA-Z0-9_])$num([^a-zA-Z0-9_])/\1D\2/g" "$file"