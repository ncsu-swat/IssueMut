#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

declarMatches=$(grep -noE 'int [a-zA-Z_][a-zA-Z0-9_]* = [a-zA-Z_][a-zA-Z0-9_]*;' "$file")

if [ -z "$declarMatches" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_declar_match=$(echo "$declarMatches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

declarLine=$(echo "$rand_declar_match" | cut -d: -f1)
declaration=$(echo "$rand_declar_match" | cut -d: -f2)

sed -i -E "${declarLine}d" "$file"

gotoMatches=$(grep -noE '^[a-zA-Z_][a-zA-Z0-9_]*\s*:' "$file")

if [ -z "$gotoMatches" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_goto_match=$(echo "$gotoMatches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

gotoLine=$(echo "$rand_goto_match" | cut -d: -f1)

sed -i -E "${gotoLine}a\ ${declaration}" "$file"