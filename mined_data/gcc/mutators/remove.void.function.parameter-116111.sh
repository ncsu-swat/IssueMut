#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all occurrences of "(void)"
matches=$(grep -noE '\(void\)' "$file")

# Check if matches are found
if [ -n"$matches" ]; then
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  # Extract line and column from the random match
  line_number=$(echo "$matches" | cut -d: -f1)

  # Use sed to remove the selected pattern
  sed -i -E "${line_number}s/\(void\)/\(\)/" "$file"
fi

# Find all occurrences of "return 0;"
matches=$(grep -noE 'return [0-9]+;' "$file")

# Check if matches are found
if [ -n"$matches" ]; then
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  # Extract line and column from the random match
  line_number=$(echo "$matches" | cut -d: -f1)

  # Use sed to remove the selected pattern
  sed -i -E "${line_number}s/return [0-9]+;//" "$file"
fi