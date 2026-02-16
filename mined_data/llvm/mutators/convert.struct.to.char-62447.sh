#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Read in the entire struct and make it one line
structWhole=$(grep -znoE "struct \{.*([a-zA-Z_][a-zA-Z0-9_]*) [a-zA-Z_][a-zA-Z0-9_]*;.*\} ([a-zA-Z_][a-zA-Z0-9_]*);" "$file" | \
tr '\0' '\n' | tr -d '\n' | sed -E "s/struct\s*\{\s*([a-zA-Z_][a-zA-Z0-9_]*)\s+[a-zA-Z_][a-zA-Z0-9_]*;\s*\}\s*([a-zA-Z_][a-zA-Z0-9_]*);/\1 \2;/") 

if [ -n "$structWhole" ]; then
  random_match1=$(echo "$structWhole" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

  line=$(echo "$random_match1" | cut -d: -f1)
  replacement=$(echo "$random_match1" | cut -d: -f2)

  line2=$((line + 1))
  line3=$((line2 + 1))

  # Replace the first line and delete the rest of the lines
  sed -i -E "${line} s/struct \{/$replacement/" "$file"
  sed -i -E "${line2} s/[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*;//" "$file"
  sed -i -E "${line3} s/\} [a-zA-Z_][a-zA-Z0-9_]*;//" "$file"
fi


# Add an extra parenthesis to all declarations
sed -i -E 's/([a-zA-Z_][a-zA-Z0-9_]*)\[\(/\1\[\(\(/g' "$file"

# Find all sizeof()
parentheses=$(grep -noE "sizeof\([a-zA-Z_][a-zA-Z0-9_\.]*\)" "$file")

if [ -n "$parentheses" ]; then
  # Select a random sizeof statement
  random_match2=$(echo "$parentheses" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  line2=$(echo "$random_match2" | cut -d: -f1)
  
  # Add an extra parenthesis to the end of the selected sizeof statement
  sed -i -E "${line2} s/sizeof\(([a-zA-Z_][a-zA-Z0-9_\.]*)\)/sizeof\(\1\)\)/" "$file"
fi