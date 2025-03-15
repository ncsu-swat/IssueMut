#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

sed -i -E 's/(unsigned [a-zA-Z_][a-zA-Z0-9_]*) = 0;/\1;/g' "$file"


matches1=$(grep -noE '[a-zA-Z_][a-zA-Z0-9_]* = \(int \*\)calloc\([0-9]+, sizeof\(int\)\);' "$file")

if [ -z "$matches1" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match1=$(echo "$matches1" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line1=$(echo "$rand_match1" | cut -d: -f1)
sed -i -E "${line1} s/[a-zA-Z_][a-zA-Z0-9_]* = \(int \*\)calloc\([0-9]+, sizeof\(int\)\);//" "$file"


matches2=$(grep -noE 'free\([a-zA-Z_][a-zA-Z0-9_]*\);' "$file")

if [ -z "$matches2" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match2=$(echo "$matches2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line2=$(echo "$rand_match2" | cut -d: -f1)
sed -i -E "${line2} s/free\([a-zA-Z_][a-zA-Z0-9_]*\);//" "$file"


matches3=$(grep -noE 'return 0;' "$file")

if [ -z "$matches3" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match3=$(echo "$matches3" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line3=$(echo "$rand_match3" | cut -d: -f1)
sed -i -E "${line3} s/return 0;//" "$file"