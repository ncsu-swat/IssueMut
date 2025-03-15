#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

matches=$(grep -oE 'int [a-zA-Z_][a-zA-Z0-9_]* = \(int\)[a-zA-Z_][a-zA-Z0-9_]*;' "$file" | \
sed -E 's/int ([a-zA-Z_][a-zA-Z0-9_]*) = \(int\)([a-zA-Z_][a-zA-Z0-9_]*);/\1,\2/')

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

temp=$(echo "$random_match" | cut -d',' -f1)
var=$(echo "$random_match" | cut -d',' -f2)

sed -i -E "/int ${temp} = \(int\)${var};/d" "$file"

sed -i -E "s/([^a-zA-Z0-9_])$temp([^a-zA-Z0-9_])/\1$var\2/g" "$file"