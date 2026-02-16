#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

shortVars=$(grep -noE "short [a-zA-Z_][a-zA-Z0-9_]* = 0;" "$file" | \
sed -E 's/short ([a-zA-Z_][a-zA-Z0-9_]*) = 0;/\1/')

if [ -z "$shortVars" ]; then
  echo "No matching patterns found."
  exit 0
fi

random_match1=$(echo "$shortVars" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line1=$(echo "$random_match1" | cut -d: -f1)
shortVar=$(echo "$random_match1" | cut -d: -f2)

sed -i -E "${line1}d" "$file"

calls=$(grep -noE "[^a-zA-Z0-9_]${shortVar} = " "$file")

if [ -z "$calls" ]; then
  echo "No matching patterns found."
  exit 0
fi

call=$(echo "$calls" | head -n 1)

line2=$(echo "$call" | cut -d: -f1)

sed -i -E "${line2}s/[^a-zA-Z0-9_]${shortVar}[^a-zA-Z0-9_]/ short ${shortVar} /" "$file"