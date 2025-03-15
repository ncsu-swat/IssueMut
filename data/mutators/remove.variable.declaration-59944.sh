#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

#### Randomly pick one
# Find all occurrences of address of variable
matches=$(grep -oE '\&([a-zA-Z_][a-zA-Z0-9_]*)' "$file" | \
sed -E 's/\&([a-zA-Z_][a-zA-Z0-9_]*)/\1/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Convert matches to an array and randomly pick one
varible=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')


# Find the variable declaration
matches=$(grep -noE "([a-zA-Z_][a-zA-Z0-9_]* )*[a-zA-Z_][a-zA-Z0-9_]* $varible( = (.*))?;" "$file")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

line=$(echo "$matches" | head -n 1 | cut -d: -f1)

sed -i -E "${line}s/([a-zA-Z_][a-zA-Z0-9_]* )*[a-zA-Z_][a-zA-Z0-9_]* $varible( = (.*))?;//" "$file"
