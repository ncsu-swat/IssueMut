#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all the variables in switch statements
matches=$(grep -oE 'switch \(([a-zA-Z_][a-zA-Z0-9_]*)\)' "$file" | \
sed -E 's/switch \(([a-zA-Z_][a-zA-Z0-9_]*)\)/\1/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
switch_var=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

initialization=$(grep -oE "[a-zA-Z_][a-zA-Z0-9_]* $switch_var = (.*);" "$file" | \
sed -E "s/[a-zA-Z_][a-zA-Z0-9_]* $switch_var = (.*);/\1/")

if [ -z "$initialization" ]; then
  echo "No initialization found."
  exit 1
fi

sed -i -E "/[a-zA-Z_][a-zA-Z0-9_]* $switch_var = (.*);/d" "$file"

sed -i -E "s/switch \($switch_var\)/switch \($initialization\)/" "$file"