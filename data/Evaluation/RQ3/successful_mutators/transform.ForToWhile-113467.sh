#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

sed -i -E 's/([a-zA-Z_][a-zA-Z0-9_]*)\s*\[.*\]/\*\1++/' "$file"

#### Randomly pick one
# Find all occurrences of for statements
matches=$(grep -noE 'for\s*\(.*([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*1;\s*\1\s*<\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*;\s*\1\s*\+\+\s*\)' "$file")

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Convert matches to an array and randomly pick one
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract line and column from the random match
line=$(echo "$random_match" | cut -d: -f1)

sed -i -E "${line}s/for\s*\(.*([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*1;\s*\1\s*<\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*;\s*\1\s*\+\+\s*\)/while (--\2)/" "$file"