#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

FILE="$1"
SEED=$2

sed -i -E 's/\(int\)//g' "$FILE"

sed -i -E '/^\s*int\s+[a-zA-Z_][a-zA-Z0-9_]*\s*=.*;/{
  :loop
  N
  s/\n\s*int\s+/,\n/g
  t loop
  s/;\s*,\n/, /g  # Remove the first semicolon after "int ...;"
}' "$FILE"

#### Randomly pick one
# Find all occurrences of return 0 statements
matches=$(grep -noE 'return\s+0;' "$FILE")

int_matches=$(grep -noE 'int' "$FILE")

# If no matches are found, exit
if [[ -z "$matches" && -z "$unsigned_matches" ]]; then
  echo "No matching patterns found."
  exit 0
fi

if [ -n "$matches" ]; then
    # Convert matches to an array and randomly pick one
    random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

    # Extract line and column from the random match
    line=$(echo "$random_match" | cut -d: -f1)

    sed -i -E "${line}s/return\s+0;//" "$FILE"
fi

if [ -n "$int_matches" ]; then
    # Convert matches to an array and randomly pick one
    random_match=$(echo "$int_matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

    # Extract line and column from the random match
    line=$(echo "$random_match" | cut -d: -f1)

    sed -i -E "${line}s/int/unsigned/g" "$FILE"
fi