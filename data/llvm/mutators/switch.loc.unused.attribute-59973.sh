#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

#### Randomly pick one
# Find all occurrences of __attribute__((unused))
matches_1=$(grep -noE '^(__attribute__\(\([^(]*unused[^)]*\)\)) ([^;]*)' "$file")

matches_2=$(grep -noE '(.*) (__attribute__\(\([^(]*unused[^)]*\)\))' "$file")

# Check if any candidates exist
if [ -n "$matches_1" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches_1" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  line=$(echo "$random_match" | cut -d: -f1)
  sed -i -E "${line}s/(__attribute__\(\([^(]*unused[^)]*\)\)) ([^;]*)/\2 \1/" "$file"
fi

# Check if any candidates exist
if [ -n "$matches_2" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches_2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  line=$(echo "$random_match" | cut -d: -f1)
  sed -i -E "${line}s/(.*) (__attribute__\(\([^(]*unused[^)]*\)\))/\2 \1/" "$file"
fi
