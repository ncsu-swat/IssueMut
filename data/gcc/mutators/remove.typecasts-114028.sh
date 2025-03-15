#!/bin/bash

# Check if a file is provided as the first argument
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <filename> <seed>"
  exit 1
fi

file=$1
SEED=$2

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "Error: File '$file' not found!"
  exit 1
fi

# Remove all the typecasts of int, short, and long!!!!
sed -i -E "s/\(\s*(int|short|long)\s*\)//g" "$file"

#### Randomly remove 0 initialization
# Find all occurrences of 0 intialization
matches=$(grep -noE '([a-zA-Z0-9_]+)\s*=\s*0([^0-9])' "$file")

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Convert matches to an array and randomly pick one
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract line and column from the random match
line=$(echo "$random_match" | cut -d: -f1)

sed -i -E "${line}s/([a-zA-Z0-9_]+)\s*=\s*0([^0-9])/\1\2/" "$file"
