#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all the function declarations
matches=$(grep -oE '[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\((.*), (.*)\);' "$file" | \
sed -E 's/[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\((.*), (.*)\);/\1/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
function=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

sed -i -E "s/([a-zA-Z_][a-zA-Z0-9_]*) $function\((.*), (.*)\);/\1 $function(\2; \3, \2);/" "$file"

sed -i -E "s/$function\(([^ ]*), ([^ ]*)\);/$function(\2, \1);/" "$file"
