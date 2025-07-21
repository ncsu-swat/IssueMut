#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2


enums=$(grep -oE 'enum [a-zA-Z_][a-zA-Z0-9_]* \{.*\};' "$file" | \
sed -E "s/(enum [a-zA-Z_][a-zA-Z0-9_]*) \{.*\};/\1/")

if [ -z "$enums" ]; then
  echo "No matching patterns found."
  exit 0
fi

enum=$(echo "$enums" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

sed -i -E "s/unsigned int/$enum/g" "$file"