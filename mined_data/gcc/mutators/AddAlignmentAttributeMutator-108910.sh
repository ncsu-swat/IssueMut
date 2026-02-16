#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all the unsigned long variables
matches=$(grep -noE 'float\s\*([a-zA-Z_])' "$file")

# If no matches are found, exit
if [ -z "$matches" ]; then
  # echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract line and column from the random match
line=$(echo "$random_match" | cut -d: -f1)

sed -i -E "${line}s/float\s\*([a-zA-Z_])/float *__attribute__((aligned(64))) \1/" "$file"
