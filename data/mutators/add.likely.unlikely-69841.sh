#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# A method to add likely
ifs1=$(grep -noE "if \(.*\)$" "$file")

if [ -z "$ifs1" ]; then
  echo "No matching patterns found."
  exit 0
fi

if1=$(echo "$ifs1" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line1=$(echo "$if1" | cut -d: -f1)

sed -i -E "$line1 s/(if \(.*\))/\1 \[\[likely\]\]/" "$file"


# A method to add unlikely
ifs2=$(grep -noE "if \(.*\)$" "$file")

if [ -z "$ifs2" ]; then
  echo "No matching patterns found."
  exit 0
fi

if2=$(echo "$ifs2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line2=$(echo "$if2" | cut -d: -f1)

sed -i -E "$line2 s/(if \(.*\))/\1 \[\[unlikely\]\]/" "$file"