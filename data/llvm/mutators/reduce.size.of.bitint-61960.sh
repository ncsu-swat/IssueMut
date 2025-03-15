#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find BitInt declaration
matches=$(grep -noE "_BitInt\(([0-9]+)\) [a-zA-Z_][a-zA-Z0-9_]*;" "$file" | \
sed -E 's/_BitInt\(([0-9]+)\) [a-zA-Z_][a-zA-Z0-9_]*;/\1'/)

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Randomly select a declaration and save its line and original size
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$random_match" | cut -d: -f1)
size=$(echo "$random_match" | cut -d: -f2)

# new size = original size / 2 + 1
newSize=$((size / 2 + 1))

# Replace the line to have the new size 
sed -i -E "${line}s/_BitInt\([0-9]+\) ([a-zA-Z_][a-zA-Z0-9_]*);/_BitInt\(${newSize}\) \1;/" "$file"