#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED="$2"

# Find all occurrences of #pragma omp
matches=$(grep -n "#pragma" "$file")

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No #pragma directives found."
  exit 0
fi

# Convert matches to an array and randomly pick one based on the seed
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract line number from the random match
line=$(echo "$random_match" | cut -d: -f1)

# Delete the selected pragma line
sed -i "${line}d" "$file"

# echo "Deleted pragma at line $line: $(echo "$random_match" | cut -d: -f2-)"