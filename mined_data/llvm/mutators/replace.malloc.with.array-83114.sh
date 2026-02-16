#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all mallocs
matches=$(grep -noE '[a-zA-Z_][a-zA-Z0-9_]* \*[a-zA-Z_][a-zA-Z0-9_]* = malloc\([0-9]+ \* sizeof\([a-zA-Z_][a-zA-Z0-9_]*\)\);' "$file" | \
sed -E 's/[a-zA-Z_][a-zA-Z0-9_]* \*([a-zA-Z_][a-zA-Z0-9_]*) = malloc\(([0-9]+) \* sizeof\([a-zA-Z_][a-zA-Z0-9_]*\)\);/\1/')

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Randomly select a malloc, save its line number and variable name
rand_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$rand_match" | cut -d: -f1)
name=$(echo "$rand_match" | cut -d: -f2)

# In the selected line, replace it with an array declaration
sed -i -E "${line} s/([a-zA-Z_][a-zA-Z0-9_]*) \*([a-zA-Z_][a-zA-Z0-9_]*) = malloc\(([0-9]+) \* sizeof\([a-zA-Z_][a-zA-Z0-9_]*\)\);/\1 \2\[\3\];/" "$file"

# Delete the free statement
sed -i -E "s/free\($name\);//" "$file"

# Find the cases where the variable is called
matches2=$(grep -noE "$name" "$file")

if [ -z "$matches2" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Choose a random line and add [0] after it
rand_match2=$(echo "$matches2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line2=$(echo "$rand_match2" | cut -d: -f1)

sed -i -E "${line2} s/$name/\&$name\[0\]/" "$file"

