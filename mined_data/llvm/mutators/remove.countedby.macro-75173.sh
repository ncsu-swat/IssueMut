#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# counted_by to delete
countBys2=$(grep -noE "#define __counted_by\([a-zA-Z_][a-zA-Z0-9_]*\)" "$file")

if [ -z "$countBys2" ]; then
  echo "No matching patterns found."
  exit 0
fi

# random_match2=$(echo "$countBys2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
firstElement=$(echo "$countBys2" | head -n 1)

line2=$(echo "$firstElement" | cut -d: -f1)

sed -i -E "$line2 s/#define __counted_by\(([a-zA-Z_][a-zA-Z0-9_]*)\)//" "$file"


# counted_by to add attribute to
countBys=$(grep -noE "#define __counted_by\([a-zA-Z_][a-zA-Z0-9_]*\)" "$file")

if [ -z "$countBys" ]; then
  echo "No matching patterns found."
  exit 0
fi

random_match1=$(echo "$countBys" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line1=$(echo "$random_match1" | cut -d: -f1)

sed -i -E "$line1 s/#define __counted_by\(([a-zA-Z_][a-zA-Z0-9_]*)\)/#define __counted_by\(\1\) __attribute__\(\(__counted_by__\(\1\)\)\)/" "$file"