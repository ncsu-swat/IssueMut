#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all the unsigned long variables
matches=$(grep -noE 'long ([a-zA-Z_][a-zA-Z0-9_]*)' "$file" | \
sed -E 's/long ([a-zA-Z_][a-zA-Z0-9_]*)/\1/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  # echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract line and column from the random match
line=$(echo "$random_match" | cut -d: -f1)
long_var=$(echo "$random_match" | cut -d: -f2)

sed -i -E "$line!s/([^a-zA-Z0-9_])$long_var([^a-zA-Z0-9_])/\1($long_var \& ~0xFUL)\2/" "$file"