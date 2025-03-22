#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED="$2"

structNames=$(grep -oE 'struct [a-zA-Z_][a-zA-Z0-9_]*' "$file" | \
sed -E 's/struct ([a-zA-Z_][a-zA-Z0-9_]*)/\1/')

# If no matches are found, exit
if [ -z "$structNames" ]; then
  echo "No matching patterns found."
  exit 0
fi

structName=$(echo "$structNames" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

sed -i -E "s/${structName} [a-zA-Z_][a-zA-Z0-9_]*;/${structName}\(\);/g" "$file"