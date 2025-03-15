#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

matches=$(grep -noE 'return .*;' "$file" | grep -vE 'return 0;')

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

echo "$matches"

random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$random_match" | cut -d: -f1)

sed -i -E "${line}s/return .*/return 0;/" "$file"