#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Replace u__WB → uwb
sed -i -E "s/([0-9]+)u__WB/\1uwb/g" "$file"

# Replace __WB → __uwb
matches=$(grep -noE '([0-9]+)__WB' "$file")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$rand_match" | cut -d: -f1)

sed -i -E "${line} s/([0-9]+)__WB/\1__uwb/g" "$file"

# Replace __WB → wb
matches=$(grep -noE '([0-9]+)__WB' "$file")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$rand_match" | cut -d: -f1)

sed -i -E "${line} s/([0-9]+)__WB/\1wb/g" "$file"

# Replace __WB → __wb
matches=$(grep -noE '([0-9]+)__WB' "$file")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$rand_match" | cut -d: -f1)

sed -i -E "${line} s/([0-9]+)__WB/\1__wb/g" "$file"
